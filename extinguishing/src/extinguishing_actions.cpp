#include "extinguishing_actions.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

using namespace std::chrono_literals;

struct ExtinguishingActionsHandlerImpl : ffd_ExtinguishingActions_ops
{
    ExtinguishingActionsHandler *handler = nullptr;
};

static nk_err_t
StartActionImpl(struct ffd_ExtinguishingActions* self,
         __rtl_unused const ffd_ExtinguishingActions_StartAction_req* req,
         __rtl_unused const nk_arena* req_arena,
         __rtl_unused ffd_ExtinguishingActions_StartAction_res* res,
         __rtl_unused nk_arena* res_arena)
{
   auto impl = self != nullptr
                 ? static_cast<const ExtinguishingActionsHandlerImpl*>(self->ops)
                 : nullptr;
   if (impl == nullptr) {
     return NK_ENOENT;
   }

  std::cerr << connections::Extinguishing
      << ": Started StartAction"  << std::endl;
  impl->handler->StartAction();
  std::cerr << connections::Extinguishing
      << ": Stopped StartAction" << std::endl;

  return NK_EOK;
}

static nk_err_t
StopActionImpl(struct ffd_ExtinguishingActions* self,
         __rtl_unused const ffd_ExtinguishingActions_StopAction_req* req,
         __rtl_unused const nk_arena* req_arena,
         __rtl_unused ffd_ExtinguishingActions_StopAction_res* res,
         __rtl_unused nk_arena* res_arena)
{
    auto impl = self != nullptr
                  ? static_cast<const ExtinguishingActionsHandlerImpl*>(self->ops)
                  : nullptr;
    if (impl == nullptr) {
      return NK_ENOENT;
    }
  std::cerr << connections::Extinguishing
      << ": Started StopAction" << std::endl;
  impl->handler->StopAction();
  std::cerr << connections::Extinguishing
      << ": Stopped StopAction" << std::endl;

  return NK_EOK;
}

ffd_ExtinguishingActions *ExtinguishingActionsHandler::CreateImpl()
{
    static ExtinguishingActionsHandler _handler;
    static ExtinguishingActionsHandlerImpl ops = {};
    static ffd_ExtinguishingActions impl = {.ops = &ops};

    ops.StartAction = StartActionImpl;
    ops.StopAction = StopActionImpl;
    ops.handler = &_handler;

  return &impl;
}

//ExtinguishingActionsHandler::ExtinguishingActionsHandler(rtl_uint32_t coordinates)
//{}
void ExtinguishingActionsHandler::StartAction()
{
    //extinguishing takes 5 seconds
    std::this_thread::sleep_for(5s);
}

void ExtinguishingActionsHandler::StopAction()
{
    //extinguishing takes 5 seconds
    std::this_thread::sleep_for(5s);
}

void ExtinguishingActionsHandler::ProceedAction()
{
    //extinguishing takes 5 seconds
    std::this_thread::sleep_for(5s);
}
