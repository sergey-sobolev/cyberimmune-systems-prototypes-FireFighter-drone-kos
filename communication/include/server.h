#pragma once

#include "Communication.edl.h"
#include "app_connector.h"
#include "communication_outside.h"
#include <coresrv/sl/sl_api.h>

class Server
{
public:
  Server();
  ~Server() = default;
  int Run(AppConnectorPtr connector);

private:
  ffd_Communication_entity_req m_req{};
  ffd_Communication_entity_res m_res{};
  nk_arena m_reqArena;
  nk_arena m_resArena;

  char m_reqBuffer[ffd_Communication_entity_req_arena_size];
  char m_resBuffer[ffd_Communication_entity_res_arena_size];
};
