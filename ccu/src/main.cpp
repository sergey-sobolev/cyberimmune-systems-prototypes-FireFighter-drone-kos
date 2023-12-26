#include "server.h"

#include "app_connector.h"
#include "ccu_actions.h"
#include <connections.h>
#include <iostream>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

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

    Server server;
    auto retCode = server.Run(appCon);

    std::cerr << connections::CCU << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
