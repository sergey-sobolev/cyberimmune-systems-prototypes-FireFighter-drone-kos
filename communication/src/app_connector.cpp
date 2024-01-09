#include "app_connector.h"
#include "connections.h"

#include <rtl/string.h>

#include <iostream>

bool
AppConnector::ConnectToFMAC()
{
  auto handle = ServiceLocatorConnect(connections::FMAC);
  if (handle == INVALID_HANDLE) {
    std::cerr
      << connections::Communication << " - "
      << "Error: can`t establish static IPC connection! Connection Name: "
      << connections::FMAC;

    return false;
  }
  NkKosTransport_Init(&m_fmacTransport, handle, NK_NULL, 0);

  {
    nk_iid_t riid = ServiceLocatorGetRiid(handle, connections::FMACService);
    if (riid == INVALID_RIID) {
      std::cerr << connections::Communication << " - "
                << "Error: can`t get runtime implementation ID (RIID) of "
                   "interface '"
                << connections::FMACService << std::endl;
      return false;
    }
    ffd_FMACActions_proxy_init(
      &m_fmacActionsProxy, &m_fmacTransport.base, riid);
  }

  return true;
}

bool
AppConnector::StartAt(rtl_uint32_t _task)
{
  ffd_FMACActions_StartAt_req req{};
  ffd_FMACActions_StartAt_res res{};
  req.task = _task;
  auto code =
    ffd_FMACActions_StartAt(&m_fmacActionsProxy.base, &req, NULL, &res, NULL);
  if (code == NK_EOK) {
    std::cerr << connections::Communication << " -> " << connections::FMAC
              << ": StartAt()" << std::endl;

  } else {
    std::cerr << connections::Communication << " -> " << connections::FMAC
              << ": StartAt() - FAILED" << std::endl;
  }
  if (res.result == 0) { // not authenticated, 0 = false
    return false;
  }
  return code == NK_EOK;
}
