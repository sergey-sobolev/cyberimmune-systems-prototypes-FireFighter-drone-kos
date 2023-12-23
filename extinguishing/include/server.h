#pragma once

#include "Extinguishing.edl.h"

#include "extinguishing_actions.h"
#include <coresrv/sl/sl_api.h>

class Server
{
public:
    Server();
    ~Server() = default;
    int Run();

private:
    ffd_Extinguishing_entity_req m_req {}; 
    ffd_Extinguishing_entity_res m_res {}; 
    nk_arena m_reqArena;
    nk_arena m_resArena;

    char m_reqBuffer[ffd_Extinguishing_entity_req_arena_size];
    char m_resBuffer[ffd_Extinguishing_entity_res_arena_size];
};

