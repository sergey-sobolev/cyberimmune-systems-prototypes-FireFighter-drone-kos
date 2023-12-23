#include "movement_actions.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

using namespace std::chrono_literals;

struct MovementActionsHandlerImpl : ffd_MovementActions_ops
{
    MovementActionsHandler *handler = nullptr;
};

static nk_err_t
MoveToImpl(struct ffd_MovementActions* self,
         const ffd_MovementActions_MoveTo_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_MovementActions_MoveTo_res* res,
         __rtl_unused nk_arena* res_arena)
{
  MovementActionsHandlerImpl* impl = (MovementActionsHandlerImpl*)self;
  std::cout << connections::Movement
      << ": Started MoveTo: " << req->task << std::endl;
  impl->handler->MoveTo((int) req->task);
  std::cout << connections::Movement
      << ": Stopped  MoveTo: " << req->task << std::endl;

  return NK_EOK;
}

ffd_MovementActions *MovementActionsHandler::CreateImpl()
{
    static MovementActionsHandler _handler = {};
    static MovementActionsHandlerImpl ops = {};
    static ffd_MovementActions impl = {.ops = &ops};

    ops.MoveTo = MoveToImpl;
    ops.handler = &_handler;

  return &impl;
}

//MovementActionsHandler::MovementActionsHandler()
//{}

void MovementActionsHandler::MoveTo(rtl_uint32_t task)
{
    //movement takes 5 seconds
    std::this_thread::sleep_for(5s);
}
