#pragma once

#include "Movement.edl.h"

#include "movement_actions.h"
#include <coresrv/sl/sl_api.h>

class Server
{
public:
  Server();
  ~Server() = default;
  int Run();

private:
  ffd_Movement_entity_req m_req{};
  ffd_Movement_entity_res m_res{};
  nk_arena m_reqArena;
  nk_arena m_resArena;

  char m_reqBuffer[ffd_Movement_entity_req_arena_size];
  char m_resBuffer[ffd_Movement_entity_res_arena_size];
};
