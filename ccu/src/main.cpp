#include <connections.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <ffd/AggregationCoordinates.idl.h>

#include <assert.h>

const static std::string me = connections::CCU;

int
main(void)
{
  NkKosTransport transport;
  struct ffd_AggregationCoordinates_proxy proxy;
  int i;

  std::cerr << me << ": started" << std::endl;

  Handle handle = ServiceLocatorConnect(connections::Aggregation);
  assert(handle != INVALID_HANDLE);

  NkKosTransport_Init(&transport, handle, NK_NULL, 0);

  nk_iid_t riid =
    ServiceLocatorGetRiid(handle, "AggregationCoordinates.coordinates");
  assert(riid != INVALID_RIID);

  ffd_AggregationCoordinates_proxy_init(&proxy, &transport.base, riid);

  ffd_AggregationCoordinates_Get_req req;
  ffd_AggregationCoordinates_Get_res res;

  while (true) {
    if (ffd_AggregationCoordinates_Get(&proxy.base, &req, NULL, &res, NULL) ==
        rcOk) {
      std::cerr << me << " -> " << connections::Aggregation
                << ": coordinates(), result: " << (int)res.coordinates << std::endl;
    } else {
      std::cerr << "Failed to call ffd.AggregationCoordinates.coordinates()"
                << std::endl;
    }
    sleep(1);
  }
  std::cerr << me << ": stopped" << std::endl;

  return EXIT_SUCCESS;
}
