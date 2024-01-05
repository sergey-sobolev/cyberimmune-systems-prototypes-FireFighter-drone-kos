#include "server.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include "eaic_actions.h"
#include <EAIC.edl.h>
#include <connections.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <assert.h>

Server::Server()
  : m_reqArena(
      NK_ARENA_INITIALIZER(m_reqBuffer, m_reqBuffer + sizeof(m_reqBuffer)))
  , m_resArena(
      NK_ARENA_INITIALIZER(m_resBuffer, m_resBuffer + sizeof(m_resBuffer)))
{
}

int
Server::Run(AppConnectorPtr connector)
{
  ServiceId iid;
  NkKosTransport transport;

  auto handleClients = ServiceLocatorRegister(connections::EAIC, NULL, 0, &iid);
  if (handleClients == INVALID_HANDLE) {
    std::cerr
      << connections::EAIC
      << "Error: can`t establish static IPC connection! Connection name: "
      << connections::EAIC << std::endl;
    return EXIT_FAILURE;
  }

  // Initialize transport to clients.
  NkKosTransport_Init(&transport, handleClients, NK_NULL, 0);

  ffd_EAICActions_component component;
  ffd_EAICActions_component_init(&component,
                                 EAICActionsHandler::CreateImpl(connector));

  ffd_EAIC_entity entity;
  ffd_EAIC_entity_init(&entity, &component);

  // Main cycle: requests execution.
  while (true) {
    nk_req_reset(&m_req);
    nk_arena_reset(&m_reqArena);
    nk_req_reset(&m_res);
    nk_arena_reset(&m_resArena);

    if (auto resCode =
          nk_transport_recv(&transport.base, &m_req.base_, &m_reqArena);
        resCode == NK_EOK)
      ffd_EAIC_entity_dispatch(
        &entity, &m_req.base_, &m_reqArena, &m_res.base_, &m_resArena);
    else
      std::cerr << connections::EAIC
                << "Error: nk_transport_recv is not OK. Error code = "
                << resCode << std::endl;

    if (auto resCode =
          nk_transport_reply(&transport.base, &m_res.base_, &m_resArena);
        resCode != NK_EOK)
      std::cerr << connections::EAIC
                << "Error: nk_transport_reply is not OK. Error code = "
                << resCode << std::endl;
  }

  return EXIT_SUCCESS;
}
