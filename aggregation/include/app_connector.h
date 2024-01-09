#pragma once

#include <NavigationCoordinates.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector
{
public:
  AppConnector() = default;

  // Open IPC connection
  bool Connect();

  // Navigation
  bool Get();

private:
  NkKosTransport m_navigationTransport;
  ffd_NavigationCoordinates_proxy m_navigationCoordinatesProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
