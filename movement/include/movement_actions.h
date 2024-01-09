#pragma once

#include <Movement.edl.h>
#include <chrono>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>
#include <thread>

class MovementActionsHandler : ffd_MovementActions_ops
{
public:
  static ffd_MovementActions* CreateImpl();
  void MoveTo(rtl_uint32_t task);

  // MovementActionsHandler() = delete;
  ~MovementActionsHandler() = default;

  // private:
  //     MovementActionsHandler(rtl_uint32_t task);
};
