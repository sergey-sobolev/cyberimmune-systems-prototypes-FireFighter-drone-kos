#pragma once

#include "app_connector.h"
#include <CCU.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>
#include <iostream>

class CCUActionsHandler : ffd_CCUActions_ops
{
public:
  static ffd_CCUActions* CreateImpl(AppConnectorPtr connector);
  void StartActionAt(rtl_uint32_t task);
  void StartedAt(rtl_uint32_t task);

  CCUActionsHandler() = delete;
  ~CCUActionsHandler() = default;

private:
  CCUActionsHandler(AppConnectorPtr connector);

private:
  AppConnectorPtr appCon;
};
