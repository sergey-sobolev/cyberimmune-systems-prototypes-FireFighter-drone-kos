#pragma once

#include <FMAC.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class FMACActionsHandler : ffd_FMACActions_ops
{
    public:
        static ffd_FMACActions *CreateImpl();
        void StartAt();

        //FMACActionsHandler() = delete;
        ~FMACActionsHandler() = default;

    //private:
        //FMACActionsHandler();
};
