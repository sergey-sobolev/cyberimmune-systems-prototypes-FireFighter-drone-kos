#include "eaic_actions.h"
#include <connections.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


struct EAICActionsHandlerImpl : ffd_EAICActions_ops
{
    EAICActionsHandler *handler = nullptr;
};

static nk_err_t
StartActionAtImpl(struct ffd_EAICActions* self,
         const ffd_EAICActions_StartActionAt_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_EAICActions_StartActionAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  unsigned int authenticated_task = 1;
  std::cerr << connections::EAIC
      << ": Started StartActionAt(" << req->task << ")" << std::endl;

   auto impl = self != nullptr
                 ? static_cast<const EAICActionsHandlerImpl*>(self->ops)
                 : nullptr;
   if (impl == nullptr) {
     return NK_ENOENT;
   }
    //impl->handler->StartActionAt(req->task);

    std::cerr << connections::EAIC
      << ": Stopped  StartActionAt" << std::endl;
  return NK_EOK;
}

static nk_err_t
ConfirmActionImpl(struct ffd_EAICActions* self,
         const ffd_EAICActions_ConfirmAction_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_EAICActions_ConfirmAction_res* res,
         __rtl_unused nk_arena* res_arena)
{
  EAICActionsHandlerImpl* impl = (EAICActionsHandlerImpl*)self;
  std::cerr << connections::EAIC
      << ": Started ConfirmAction" << std::endl;
  //if (req->task == authenticated_task) {

    //impl->handler->StartAt(req->task);

    std::cerr << connections::EAIC
      << ": Stopped  ConfirmAction" << std::endl;
      //res->result = 1;
  //} else {
      //res->result = 0;
  //}
  return NK_EOK;
}

static nk_err_t
StopActionImpl(struct ffd_EAICActions* self,
         const ffd_EAICActions_StopAction_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_EAICActions_StopAction_res* res,
         __rtl_unused nk_arena* res_arena)
{
  EAICActionsHandlerImpl* impl = (EAICActionsHandlerImpl*)self;
  std::cerr << connections::EAIC
      << ": Started StopAction" << std::endl;
  //if (req->task == authenticated_task) {

    //impl->handler->StartAt(req->task);

    std::cerr << connections::EAIC
      << ": Stopped  StopAction" << std::endl;
      //res->result = 1;
  //} else {
      //res->result = 0;
  //}
  return NK_EOK;
}


ffd_EAICActions *EAICActionsHandler::CreateImpl(AppConnectorPtr connector)
{
    static EAICActionsHandler _handler(connector);
    static EAICActionsHandlerImpl ops = {};
    static ffd_EAICActions impl = {.ops = &ops};

    ops.StartActionAt = StartActionAtImpl;
    ops.ConfirmAction = ConfirmActionImpl;
    ops.StopAction = StopActionImpl;
    ops.handler = &_handler;

  return &impl;
}

EAICActionsHandler::EAICActionsHandler(
        AppConnectorPtr connector)
    : appCon(connector)
{}

//void EAICActionsHandler::StartedAt(rtl_uint32_t task)
//{
    // eaic
    //appCon->StartActionAtEAIC(task);
    // eaic
    //appCon->StartActionAtEAIC(task);
    //std::cerr << "StartedAt" << std::endl;
//}
