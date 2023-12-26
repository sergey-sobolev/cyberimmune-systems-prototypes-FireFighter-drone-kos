#include "server.h"

#include "app_connector.h"
#include "fmac_actions.h"
#include <connections.h>
#include <iostream>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    std::cerr << connections::FMAC << ": started" << std::endl;

    auto appCon = std::make_shared<AppConnector>();
    if (!appCon->ConnectToCCU()) {
      std::cerr << connections::FMAC << ": appCon->Connect to CCU failed" << std::endl;
    }
    if (!appCon->ConnectToEAIC()) {
      std::cerr << connections::FMAC << ": appCon->Connect to EAIC failed" << std::endl;
    }

    Server server;
    auto retCode = server.Run(appCon);

    std::cerr << connections::FMAC << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
