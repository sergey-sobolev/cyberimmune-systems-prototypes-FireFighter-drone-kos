#pragma once

#include <Extinguishing.edl.h>
#include <chrono>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>
#include <thread>

class ExtinguishingActionsHandler : ffd_ExtinguishingActions_ops
{
public:
  static ffd_ExtinguishingActions* CreateImpl();
  void StartAction();
  void StopAction();
  void ProceedAction();

  // ExtinguishingActionsHandler() = delete;
  ~ExtinguishingActionsHandler() = default;

  // private:
  //     ExtinguishingActionsHandler();
};
