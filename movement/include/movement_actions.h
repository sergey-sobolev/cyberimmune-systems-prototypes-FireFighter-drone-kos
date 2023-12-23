#pragma once

#include <thread>
#include <chrono>
#include <Movement.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class MovementActionsHandler : ffd_MovementActions_ops
{
    public:
        static ffd_MovementActions *CreateImpl();
        void MoveTo(rtl_uint32_t task);

        //MovementActionsHandler() = delete;
        ~MovementActionsHandler() = default;

    //private:
    //    MovementActionsHandler(rtl_uint32_t task);
};
