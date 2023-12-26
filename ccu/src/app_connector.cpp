#include "app_connector.h"
#include "connections.h"

#include <rtl/string.h>

#include <iostream>

bool AppConnector::ConnectToAggregation()
{
    auto handle = ServiceLocatorConnect(connections::Aggregation);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::CCU
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Aggregation;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "AggregationCoordinates.coordinates");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::CCU
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "AggregationCoordinates.coordinates"
                      << std::endl;
            return false;
        }
        ffd_AggregationCoordinates_proxy_init(&m_aggregationCoordinatesProxy, &m_transport.base, riid);
    }

    return true;
}

bool AppConnector::ConnectToCommunication()
{
    auto handle = ServiceLocatorConnect(connections::Communication);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::CCU
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Communication;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "CommunicationOutside.startedat");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::CCU
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "CommunicationOutside.startedat"
                      << std::endl;
            return false;
        }
        ffd_CommunicationOutside_proxy_init(&m_communicationOutsideProxy, &m_transport.base, riid);
    }

    return true;
}

bool AppConnector::ConnectToExtinguishing()
{
    auto handle = ServiceLocatorConnect(connections::Extinguishing);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::CCU
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Extinguishing;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "ExtinguishingActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::CCU
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "ExtinguishingActions.actions"
                      << std::endl;
            return false;
        }
        ffd_ExtinguishingActions_proxy_init(&m_extinguishingActionsProxy, &m_transport.base, riid);
    }

    return true;
}

bool AppConnector::ConnectToMovement()
{
    auto handle = ServiceLocatorConnect(connections::Movement);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::CCU
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Movement;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "MovementActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::CCU
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "MovementActions.actions"
                      << std::endl;
            return false;
        }
        ffd_MovementActions_proxy_init(&m_movementActionsProxy, &m_transport.base, riid);
    }

    return true;
}

bool AppConnector::ConnectToSituation()
{
    auto handle = ServiceLocatorConnect(connections::Situation);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::CCU
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Situation;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "SituationActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::CCU
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "SituationActions.actions"
                      << std::endl;
            return false;
        }
        ffd_SituationActions_proxy_init(&m_situationActionsProxy, &m_transport.base, riid);
    }

    return true;
}

bool AppConnector::GetAggregation()
{
    ffd_AggregationCoordinates_Get_req req {};
    ffd_AggregationCoordinates_Get_res res {};
    auto code = ffd_AggregationCoordinates_Get(
        &m_aggregationCoordinatesProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Aggregation
                << ": Get()" << std::endl;

    } else {
         std::cerr << connections::CCU << " -> " << connections::Aggregation
                << ": Get() - FAILED" << std::endl;
    }
    // res->result coordinates
    return code == NK_EOK;
}

bool AppConnector::StartedAtCommunication(rtl_uint32_t _task)
{
    ffd_CommunicationOutside_StartedAt_req req {};
    ffd_CommunicationOutside_StartedAt_res res {};
    req.task = _task;
    auto code = ffd_CommunicationOutside_StartedAt(
        &m_communicationOutsideProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Communication
                << ": StartAt()" << std::endl;

    } else {
         std::cerr << connections::CCU << " -> " << connections::Communication
                << ": StartAt() - FAILED" << std::endl;
    }
    // res->result 0=false if communication -> fps is failed
    return code == NK_EOK;
}

bool AppConnector::StartActionExtinguishing()
{
    ffd_ExtinguishingActions_StartAction_req req {};
    ffd_ExtinguishingActions_StartAction_res res {};
    auto code = ffd_ExtinguishingActions_StartAction(
        &m_extinguishingActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Extinguishing
                << ": StartActionAt()" << std::endl;

    } else {
         std::cerr << connections::CCU << " -> " << connections::Extinguishing
                << ": StartActionAt() - FAILED" << std::endl;
    }
    return code == NK_EOK;
}

bool AppConnector::StopActionExtinguishing()
{
    ffd_ExtinguishingActions_StopAction_req req {};
    ffd_ExtinguishingActions_StopAction_res res {};
    auto code = ffd_ExtinguishingActions_StopAction(
        &m_extinguishingActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Extinguishing
                << ": StopActionAt()" << std::endl;

    } else {
         std::cerr << connections::CCU << " -> " << connections::Extinguishing
                << ": StopActionAt() - FAILED" << std::endl;
    }
    return code == NK_EOK;
}

bool AppConnector::MoveToMovement(rtl_uint32_t _task)
{
    ffd_MovementActions_MoveTo_req req {};
    ffd_MovementActions_MoveTo_res res {};
    req.task = _task;
    auto code = ffd_MovementActions_MoveTo(
        &m_movementActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Movement
                << ": MoveTo()" << std::endl;

    } else {
        std::cerr << connections::CCU << " -> " << connections::Movement
                << ": MoveTo() - FAILED" << std::endl;
    }
    return code == NK_EOK;
}

bool AppConnector::ActionInProgressSituation()
{
    ffd_SituationActions_ActionInProgress_req req {};
    ffd_SituationActions_ActionInProgress_res res {};
    auto code = ffd_SituationActions_ActionInProgress(
        &m_situationActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::CCU << " -> " << connections::Situation
                << ": ActionInProgress()" << std::endl;

    } else {
        std::cerr << connections::CCU << " -> " << connections::Situation
                << ": ActionInProgress() - FAILED" << std::endl;
    }
    // res->result result is allways true atm
    return code == NK_EOK;
}


