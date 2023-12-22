#pragma once

#include "i_navigationcoordinatesreader.h"

#include <NavigationCoordinates.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector :
    public ipc::INavigationCoordinatesReader
{
public:
    AppConnector() = default;

    // Open IPC connection
    bool Connect();

    // Navigation
    bool Get() override;

private:
    NkKosTransport m_transport;
    ffd_NavigationCoordinates_proxy m_navigationCoordinatesProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
