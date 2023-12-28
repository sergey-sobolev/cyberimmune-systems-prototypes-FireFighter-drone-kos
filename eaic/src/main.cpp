#include "server.h"

#include "app_connector.h"
#include "eaic_actions.h"
#include <connections.h>
#include <iostream>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    std::cerr << connections::EAIC << ": started" << std::endl;

    auto appCon = std::make_shared<AppConnector>();
    if (!appCon->ConnectToAggregation()) {
      std::cerr << connections::EAIC << ": appCon->Connect to Aggregation failed" << std::endl;
    }

    Server server;
    auto retCode = server.Run(appCon);

    std::cerr << connections::EAIC << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
