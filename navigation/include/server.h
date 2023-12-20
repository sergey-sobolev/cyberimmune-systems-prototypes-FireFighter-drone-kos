#pragma once

#include "Navigation.edl.h"

#include "navigation_coordinates.h"
#include <coresrv/sl/sl_api.h>

class Server
{
public:
    Server();
    ~Server() = default;
    int Run();

private:
    ffd_Navigation_entity_req m_req {}; 
    ffd_Navigation_entity_res m_res {}; 
    nk_arena m_reqArena;
    nk_arena m_resArena;

    char m_reqBuffer[ffd_Navigation_entity_req_arena_size];
    char m_resBuffer[ffd_Navigation_entity_res_arena_size];
};

