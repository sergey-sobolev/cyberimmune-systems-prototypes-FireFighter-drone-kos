#pragma once

#include <Situation.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class SituationActionsHandler : ffd_SituationActions_ops
{
public:
  static ffd_SituationActions* CreateImpl();
  rtl_uint32_t Actions();

  // SituationActionsHandler() = delete;
  ~SituationActionsHandler() = default;

  // private:
  // SituationActionsHandler(rtl_uint32_t Actions);
};
