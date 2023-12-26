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
         ffd_FMACActions_StartAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  unsigned int authenticated_task = 1;
  FMACActionsHandlerImpl* impl = (FMACActionsHandlerImpl*)self;
  std::cerr << connections::FMAC
      << ": Started StartAt(" << req->task << ")" << std::endl;
  if (req->task == authenticated_task) {
    impl->handler->StartAt();
    std::cerr << connections::FMAC
      << ": Stopped  StartAt" << std::endl;
      res->result = 1;
  } else {
      res->result = 0;
  }
  return NK_EOK;
}

ffd_FMACActions *FMACActionsHandler::CreateImpl()
{
    static FMACActionsHandler _handler;
    static FMACActionsHandlerImpl ops = {};
    static ffd_FMACActions impl = {.ops = &ops};

    ops.StartAt = StartAtImpl;
    ops.handler = &_handler;

  return &impl;
}

//FMACActionsHandler::FMACActionsHandler(rtl_uint32_t coordinates)
//{}

void FMACActionsHandler::StartAt()
{
    //fmac takes 5 seconds
    // ccu
    // eaic
    std::cerr << "StartAt" << std::endl;
    //std::this_thread::sleep_for(5s);
}
