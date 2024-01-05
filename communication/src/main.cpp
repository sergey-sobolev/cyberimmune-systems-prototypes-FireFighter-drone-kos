
#include "apihandler.h"
#include "app_connector.h"
#include "communication_outside.h"
#include "helper.h"

#include "server.h"
#include <CivetServer.h>
#include <chrono>
#include <connections.h>
#include <iostream>
#include <kos_net.h>
#include <memory>
#include <string>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

namespace consts {
constexpr const char* ApiUri = "/api";
constexpr const char* Port = "8081";
constexpr const char* DocumentRoot = "/romfs";
}

void
RunAPI(AppConnectorPtr connector)
{
  mg_init_library(0);

  std::vector<std::string> cppOptions = { "listening_ports", consts::Port };
  CivetServer server(cppOptions);
  APIHandler hApi(connector);
  server.addHandler(consts::ApiUri, hApi);
  std::cout << connections::Communication
            << " WebServer started on port: " << consts::Port << std::endl;

  while (1) {
    // connector->StartAt();
    std::this_thread::sleep_for(1s);
  }

  mg_exit_library();
}

int
main(void)
{
  std::cerr << connections::Communication << ": started" << std::endl;

  if (!wait_for_network()) {
    std::cerr << connections::Communication
              << ": Error: Wait for a network failed!" << std::endl;
    return EXIT_FAILURE;
  } else {
    std::cout << connections::Communication << ": Network is accessible!"
              << std::endl;
  }

  if (!helper::mountFolder("romfs", consts::DocumentRoot)) {
    std::cerr << connections::Communication
              << ": Error: Unable to mount folders!" << std::endl;
  } else {
    std::cout << connections::Communication << ": Mount of romfs is successful!"
              << std::endl;
  }

  auto appCon = std::make_shared<AppConnector>();
  if (!appCon->ConnectToFMAC()) {
    std::cerr << "appCon->Connect failed" << std::endl;
  }

  std::thread s(RunAPI, appCon);
  s.detach();
  Server server;
  auto retCode = server.Run(appCon);

  std::cerr << connections::Communication << ": stoped. Exit code = " << retCode
            << std::endl;

  return retCode;
}
