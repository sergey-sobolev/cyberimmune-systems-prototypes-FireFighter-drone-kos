#include "situation_actions.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>


#include <assert.h>

struct SituationActionsHandlerImpl : ffd_SituationActions_ops
{
    SituationActionsHandler *handler = nullptr;
};

static nk_err_t
ActionInProgressImpl(struct ffd_SituationActions* self,
         __rtl_unused const ffd_SituationActions_ActionInProgress_req* req,
         __rtl_unused const nk_arena* req_arena,
         ffd_SituationActions_ActionInProgress_res* res,
         __rtl_unused nk_arena* res_arena)
{
  SituationActionsHandlerImpl* impl = (SituationActionsHandlerImpl*)self;
  //res->actions = impl->handler->Actions();
  return NK_EOK;
}

ffd_SituationActions *SituationActionsHandler::CreateImpl()
{
    //static SituationActionsHandler position();
    static SituationActionsHandlerImpl ops = {};
    static ffd_SituationActions impl = {.ops = &ops};

    ops.ActionInProgress = ActionInProgressImpl;
    //ops.handler = &position;

  return &impl;
}

//SituationActionsHandler::SituationActionsHandler()
//{}

rtl_uint32_t SituationActionsHandler::Actions()
{
    return 123;
}
