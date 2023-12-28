#pragma once

#include "app_connector.h"
#include <EAIC.edl.h>
#include <iostream>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class EAICActionsHandler : ffd_EAICActions_ops
{
    public:
        static ffd_EAICActions *CreateImpl(AppConnectorPtr connector);
        void StartActionAt(rtl_uint32_t task);
        void ConfirmAction();
        void StopAction();

        EAICActionsHandler() = delete;
        ~EAICActionsHandler() = default;

    private:
        EAICActionsHandler(AppConnectorPtr connector);
    private:
        AppConnectorPtr appCon;
};
