
#include "aggregation_coordinates.h"
#include "app_connector.h"

#include "server.h"
#include <connections.h>
#include <iostream>
#include <memory>
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
    connector->Get();
    std::this_thread::sleep_for(1s);
  }
}

int
main(void)
{
  std::cerr << connections::Aggregation << ": started" << std::endl;

  auto appCon = std::make_shared<AppConnector>();
  if (!appCon->Connect()) {
    std::cerr << "appCon->Connect failed" << std::endl;
  }
  std::thread s(Run, appCon);
  s.detach();
  Server server;
  auto retCode = server.Run(appCon);

  std::cerr << connections::Aggregation << ": stoped. Exit code = " << retCode
            << std::endl;

  return retCode;
}
