#pragma once

#include "EAIC.edl.h"
#include "app_connector.h"
#include "eaic_actions.h"
#include <coresrv/sl/sl_api.h>

class Server
{
public:
  Server();
  ~Server() = default;
  int Run(AppConnectorPtr connector);

private:
  ffd_EAIC_entity_req m_req{};
  ffd_EAIC_entity_res m_res{};
  nk_arena m_reqArena;
  nk_arena m_resArena;

  char m_reqBuffer[ffd_EAIC_entity_req_arena_size];
  char m_resBuffer[ffd_EAIC_entity_res_arena_size];
};
