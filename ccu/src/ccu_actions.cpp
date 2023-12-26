#include "ccu_actions.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

struct CCUActionsHandlerImpl : ffd_CCUActions_ops
{
    CCUActionsHandler *handler = nullptr;
};

static nk_err_t
StartActionAtImpl(struct ffd_CCUActions* self,
         const ffd_CCUActions_StartActionAt_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_CCUActions_StartActionAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  unsigned int authenticated_task = 1;
  CCUActionsHandlerImpl* impl = (CCUActionsHandlerImpl*)self;
  std::cerr << connections::CCU
      << ": Started StartActionAt(" << req->task << ")" << std::endl;
  if (req->task == authenticated_task) {

    //impl->handler->StartActionAt(req->task);

    std::cerr << connections::CCU
      << ": Stopped  StartActionAt" << std::endl;
      //res->result = 1;
  } else {
      //res->result = 0;
  }
  return NK_EOK;
}

static nk_err_t
StartedAtImpl(struct ffd_CCUActions* self,
         const ffd_CCUActions_StartedAt_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_CCUActions_StartedAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  unsigned int authenticated_task = 1;
  CCUActionsHandlerImpl* impl = (CCUActionsHandlerImpl*)self;
  std::cerr << connections::CCU
      << ": Started StartAt(" << req->task << ")" << std::endl;
  if (req->task == authenticated_task) {

    //impl->handler->StartAt(req->task);

    std::cerr << connections::CCU
      << ": Stopped  StartedAt" << std::endl;
      //res->result = 1;
  } else {
      //res->result = 0;
  }
  return NK_EOK;
}

ffd_CCUActions *CCUActionsHandler::CreateImpl(AppConnectorPtr connector)
{
    static CCUActionsHandler _handler(connector);
    static CCUActionsHandlerImpl ops = {};
    static ffd_CCUActions impl = {.ops = &ops};

    ops.StartActionAt = StartActionAtImpl;
    ops.StartedAt = StartedAtImpl;
    ops.handler = &_handler;

  return &impl;
}

CCUActionsHandler::CCUActionsHandler(
        AppConnectorPtr connector)
    : appCon(connector)
{}

void CCUActionsHandler::StartedAt(rtl_uint32_t task)
{
    // eaic
    //appCon->StartActionAtEAIC(task);
    // ccu
    //appCon->StartActionAtCCU(task);
    std::cerr << "StartedAt" << std::endl;
}
