#include "fmac_actions.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

struct FMACActionsHandlerImpl : ffd_FMACActions_ops
{
    FMACActionsHandler *handler = nullptr;
};

static nk_err_t
StartAtImpl(struct ffd_FMACActions* self,
         const ffd_FMACActions_StartAt_req* req,
         __rtl_unused const nk_arena* req_arena,
         __rtl_unused ffd_FMACActions_StartAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  FMACActionsHandlerImpl* impl = (FMACActionsHandlerImpl*)self;
  std::cout << connections::FMAC
      << ": Started StartAt" << std::endl;
  std::cout << req->task << std::endl;
  impl->handler->StartAt();
  std::cout << connections::FMAC
      << ": Stopped  StartAt" << std::endl;

  return NK_EOK;
}

ffd_FMACActions *FMACActionsHandler::CreateImpl()
{
    //static FMACActionsHandler _handler();
    static FMACActionsHandlerImpl ops = {};
    static ffd_FMACActions impl = {.ops = &ops};

    ops.StartAt = StartAtImpl;
    //ops.handler = &_handler;

  return &impl;
}

//FMACActionsHandler::FMACActionsHandler(rtl_uint32_t coordinates)
//{}

void FMACActionsHandler::StartAt()
{
    //fmac takes 5 seconds
    std::cout << "StartAt" << std::endl;
    //std::this_thread::sleep_for(5s);
}
