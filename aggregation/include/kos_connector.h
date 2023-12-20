#pragma once

#include "i_navigationcoordinatesreader.h" //"i_controlreader.h"

#include <NavigationCoordinates.idl.h> //<ILoginControl.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class KosConnector :
    public ipc::INavigationCoordinatesReader
{
public:
    KosConnector() = default;

    // Open IPC connection
    bool Connect();

    // Navigation
    bool Get() override;

private:
    NkKosTransport m_transport;
    ffd_NavigationCoordinates_proxy m_navigationCoordinatesProxy; //ILoginControl_proxy m_loginControlProxy;
};

using KosConnectorPtr = std::shared_ptr<KosConnector>;
