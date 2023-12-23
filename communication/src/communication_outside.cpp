#include "communication_outside.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

struct CommunicationOutsideHandlerImpl : ffd_CommunicationOutside_ops
{
    CommunicationOutsideHandler *handler = nullptr;
};

static nk_err_t
StartedAtImpl(struct ffd_CommunicationOutside* self,
         __rtl_unused const ffd_CommunicationOutside_StartedAt_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_CommunicationOutside_StartedAt_res* res,
         __rtl_unused nk_arena* res_arena)
{
  CommunicationOutsideHandlerImpl* impl = (CommunicationOutsideHandlerImpl*)self;
  //res->coordinates = impl->handler->Coordinates();
  return NK_EOK;
}

ffd_CommunicationOutside *CommunicationOutsideHandler::CreateImpl()
{
    //static CommunicationOutsideHandler _handler;
    static CommunicationOutsideHandlerImpl ops = {};
    static ffd_CommunicationOutside impl = {.ops = &ops};

    ops.StartedAt = StartedAtImpl;
    //ops.handler = &_handler;

  return &impl;
}

//CommunicationOutsideHandler::CommunicationOutsideHandler()
//{}

//rtl_uint32_t CommunicationOutsideHandler::Outside()
//{
//    return 123;
//}
