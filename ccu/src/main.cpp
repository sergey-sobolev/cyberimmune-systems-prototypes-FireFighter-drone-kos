#include "server.h"

#include "app_connector.h"
#include "gpio_connector.h"
#include "ccu_actions.h"
#include <chrono>
#include <connections.h>
#include <iostream>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>

void
Run(AppConnectorPtr appCon)
{
  using namespace std::chrono_literals;

  auto gpioCon = std::make_shared<GPIOConnector>();

  auto gpioInitialized = gpioCon->Init();
  while (1) {
    if (appCon->started) {
      if (gpioInitialized) {
          gpioCon->Enable16();
      }
      // aggregation
      appCon->GetAggregation();
      // movement
      appCon->MoveToMovement(appCon->task);
      if (gpioInitialized) {
          gpioCon->Enable25();
      }
      // extinguishing start
      appCon->StartActionExtinguishing();
      // situation
      appCon->ActionInProgressSituation();
      // extinguishing stop
      appCon->StopActionExtinguishing();
      if (gpioInitialized) {
          gpioCon->Disable25();
      }
      // communication started
      appCon->StartedAtCommunication(appCon->task);
      if (gpioInitialized) {
          gpioCon->Disable16();
      }
      appCon->started = false;
    }
    std::this_thread::sleep_for(10s);
  }
  gpioCon->Close();
}

int
main(void)
{
  std::cerr << connections::CCU << ": started" << std::endl;

  auto appCon = std::make_shared<AppConnector>();
  if (!appCon->ConnectToAggregation()) {
    std::cerr << connections::CCU << ": appCon->Connect to Aggregation failed"
              << std::endl;
  }
  if (!appCon->ConnectToCommunication()) {
    std::cerr << connections::CCU << ": appCon->Connect to Communication failed"
              << std::endl;
  }
  if (!appCon->ConnectToExtinguishing()) {
    std::cerr << connections::CCU << ": appCon->Connect to Extinguishing failed"
              << std::endl;
  }
  if (!appCon->ConnectToMovement()) {
    std::cerr << connections::CCU << ": appCon->Connect to Movement failed"
              << std::endl;
  }
  if (!appCon->ConnectToSituation()) {
    std::cerr << connections::CCU << ": appCon->Connect to Situation failed"
              << std::endl;
  }

  std::thread s(Run, appCon);
  s.detach();
  Server server;
  auto retCode = server.Run(appCon);

  std::cerr << connections::CCU << ": stoped. Exit code = " << retCode
            << std::endl;

  return retCode;
}
