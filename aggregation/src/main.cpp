
#include "aggregation_coordinates.h"
#include "kos_connector.h"

#include "server.h"
#include <connections.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

void
Run(KosConnectorPtr connector)
{
    using namespace std::chrono_literals;

  while (1) {
    connector->Get();
    std::this_thread::sleep_for(1s);
  }
}

int
main(void)
{
  std::cerr << connections::Aggregation << ": started" << std::endl;

  auto kosCon = std::make_shared<KosConnector>();
  if (!kosCon->Connect()) {
    std::cerr << "kosCon->Connect failed" << std::endl;
  }
  std::thread s(Run, kosCon);
  s.detach();
  Server server;
  auto retCode = server.Run(kosCon);

  std::cerr << connections::Aggregation << ": stoped. Exit code = " << retCode
            << std::endl;

  return retCode;
}
