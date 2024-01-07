#include "ccu_actions.h"
#include <connections.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <assert.h>

struct CCUActionsHandlerImpl : ffd_CCUActions_ops
{
  CCUActionsHandler* handler = nullptr;
};

static nk_err_t
StartActionAtImpl(struct ffd_CCUActions* self,
                  const ffd_CCUActions_StartActionAt_req* req,
                  __rtl_unused const nk_arena* req_arena,
                  ffd_CCUActions_StartActionAt_res* res,
                  __rtl_unused nk_arena* res_arena)
{
  auto impl = self != nullptr
                ? static_cast<const CCUActionsHandlerImpl*>(self->ops)
                : nullptr;
  if (impl == nullptr) {
    return NK_ENOENT;
  }

  std::cerr << connections::CCU << ": Started StartActionAt(" << (int)req->task
            << ")" << std::endl;

  impl->handler->StartActionAt(req->task);

  std::cerr << connections::CCU << ": Stopped  StartActionAt" << std::endl;
  return NK_EOK;
}

static nk_err_t
StartedAtImpl(struct ffd_CCUActions* self,
              const ffd_CCUActions_StartedAt_req* req,
              __rtl_unused const nk_arena* req_arena,
              ffd_CCUActions_StartedAt_res* res,
              __rtl_unused nk_arena* res_arena)
{
  auto impl = self != nullptr
                ? static_cast<const CCUActionsHandlerImpl*>(self->ops)
                : nullptr;
  if (impl == nullptr) {
    return NK_ENOENT;
  }

  std::cerr << connections::CCU << ": Started StartAt(" << req->task << ")"
            << std::endl;

  impl->handler->StartedAt(req->task);

  std::cerr << connections::CCU << ": Stopped  StartedAt" << std::endl;
  return NK_EOK;
}

ffd_CCUActions*
CCUActionsHandler::CreateImpl(AppConnectorPtr connector)
{
  static CCUActionsHandler _handler(connector);
  static CCUActionsHandlerImpl ops = {};
  static ffd_CCUActions impl = { .ops = &ops };

  ops.StartActionAt = StartActionAtImpl;
  ops.StartedAt = StartedAtImpl;
  ops.handler = &_handler;

  return &impl;
}

CCUActionsHandler::CCUActionsHandler(AppConnectorPtr connector)
  : appCon(connector)
{
}

void
CCUActionsHandler::StartActionAt(rtl_uint32_t _task)
{
  appCon->started = true;
  appCon->task = _task;
}

void
CCUActionsHandler::StartedAt(rtl_uint32_t _task)
{
  appCon->StartedAtCommunication(_task);
}
