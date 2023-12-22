#pragma once

#include "i_navigationcoordinatesreader.h"

#include <FMACActions.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector :
    public ipc::IFMACActionsReader
{
public:
    AppConnector() = default;

    // Open IPC connection
    bool FMACConnect();

    // Navigation
    bool StartAt() override; //TODO: string value

private:
    NkKosTransport m_transport;
    ffd_FMACActions_proxy m_fmacActionsProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
