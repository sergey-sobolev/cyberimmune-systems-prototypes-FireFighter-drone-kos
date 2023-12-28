#include "server.h"

#include "app_connector.h"
#include "ccu_actions.h"
#include <connections.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

void
Run(AppConnectorPtr connector)
{
    using namespace std::chrono_literals;

  while (1) {
    if (connector->started) {
        connector->StartedAtCommunication(connector->task);
        connector->started = false;
    }
    std::this_thread::sleep_for(10s);
  }
}

int main(void)
{
    std::cerr << connections::CCU << ": started" << std::endl;

    auto appCon = std::make_shared<AppConnector>();
    if (!appCon->ConnectToAggregation()) {
      std::cerr << connections::CCU << ": appCon->Connect to Aggregation failed" << std::endl;
    }
    if (!appCon->ConnectToCommunication()) {
      std::cerr << connections::CCU << ": appCon->Connect to Communication failed" << std::endl;
    }
    if (!appCon->ConnectToExtinguishing()) {
      std::cerr << connections::CCU << ": appCon->Connect to Extinguishing failed" << std::endl;
    }
    if (!appCon->ConnectToMovement()) {
      std::cerr << connections::CCU << ": appCon->Connect to Movement failed" << std::endl;
    }
    if (!appCon->ConnectToSituation()) {
      std::cerr << connections::CCU << ": appCon->Connect to Situation failed" << std::endl;
    }

    std::thread s(Run, appCon);
    s.detach();
    Server server;
    auto retCode = server.Run(appCon);

    std::cerr << connections::CCU << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
