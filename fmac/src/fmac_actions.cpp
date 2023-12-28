#include "fmac_actions.h"
#include <connections.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

struct FMACActionsHandlerImpl : ffd_FMACActions_ops
{
  FMACActionsHandler* handler;
};

static nk_err_t
StartAtImpl(struct ffd_FMACActions* self,
            const ffd_FMACActions_StartAt_req* req,
            __rtl_unused const nk_arena* req_arena,
            ffd_FMACActions_StartAt_res* res,
            __rtl_unused nk_arena* res_arena)
{
  unsigned int authenticated_task = 1;
  auto impl = self != nullptr
                ? static_cast<const FMACActionsHandlerImpl*>(self->ops)
                : nullptr;
  if (impl == nullptr) {
    return NK_ENOENT;
  }

  std::cerr << connections::FMAC << ": Started StartAt(" << req->task << ")"
            << std::endl;
  if (req->task == authenticated_task) {
    impl->handler->StartAt(req->task);
    std::cerr << connections::FMAC << ": Stopped StartAt" << std::endl;
    res->result = 1;
  } else {
    res->result = 0;
  }
  return NK_EOK;
}

ffd_FMACActions*
FMACActionsHandler::CreateImpl(AppConnectorPtr connector)
{
  static FMACActionsHandler _handler(connector);
  static FMACActionsHandlerImpl ops = {};
  static ffd_FMACActions impl = { .ops = &ops };

  ops.StartAt = StartAtImpl;
  ops.handler = &_handler;

  return &impl;
}

FMACActionsHandler::FMACActionsHandler(AppConnectorPtr connector)
  : appCon(connector)
{
}

void
FMACActionsHandler::StartAt(rtl_uint32_t task)
{
  // eaic
  std::cerr << connections::FMAC << " StartActionAtEAIC ready to START"
            << std::endl;
  appCon->StartActionAtEAIC(task);
  std::cerr << connections::FMAC << " StartActionAtEAIC is DONE" << std::endl;
  // ccu
  std::cerr << connections::FMAC << " StartActionAtCCU ready to START"
            << std::endl;
  appCon->StartActionAtCCU(task);
  std::cerr << connections::FMAC << " StartActionAtCCU is DONE" << std::endl;
}
