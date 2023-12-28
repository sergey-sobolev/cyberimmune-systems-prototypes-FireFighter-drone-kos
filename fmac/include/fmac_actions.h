#pragma once

#include "app_connector.h"
#include <FMAC.edl.h>
#include <iostream>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class FMACActionsHandler : ffd_FMACActions_ops
{
    public:
        static ffd_FMACActions *
        CreateImpl(AppConnectorPtr connector);

        void StartAt(rtl_uint32_t task);

        FMACActionsHandler() = delete;
        ~FMACActionsHandler() = default;

        AppConnectorPtr appCon;


    private:
        FMACActionsHandler(AppConnectorPtr connector);

        };
