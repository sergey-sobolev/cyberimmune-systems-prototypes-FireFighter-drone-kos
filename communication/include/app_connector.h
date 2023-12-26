#pragma once

#include "i_fmacactionsreader.h"

#include <FMACActions.idl.h>
#include "HTTPRequest.h"
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector :
    public ipc::IFMACActionsReader
{
public:
    AppConnector() = default;

    // Open IPC connection
    bool ConnectToFMAC();

    // FMAC
    bool StartAt(rtl_uint32_t task) override;

private:
    NkKosTransport m_transport;
    ffd_FMACActions_proxy m_fmacActionsProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
