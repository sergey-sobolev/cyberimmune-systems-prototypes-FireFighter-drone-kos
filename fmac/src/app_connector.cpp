#include "app_connector.h"
#include "connections.h"

#include <rtl/string.h>

#include <iostream>

bool AppConnector::ConnectToEAIC()
{
    auto handle = ServiceLocatorConnect(connections::EAIC);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::FMAC
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::EAIC;

        return false;
    }
    NkKosTransport_Init(&m_eaicTransport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "EAICActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::FMAC
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "EAICActions.actions"
                      << std::endl;
            return false;
        }
        ffd_EAICActions_proxy_init(&m_eaicActionsProxy, &m_eaicTransport.base, riid);
    }

    return true;
}

bool AppConnector::ConnectToCCU()
{
    auto handle = ServiceLocatorConnect(connections::CCU);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::FMAC
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::CCU;

        return false;
    }
    NkKosTransport_Init(&m_ccuTransport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "CCUActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::FMAC
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "CCUActions.actions"
                      << std::endl;
            return false;
        }
        ffd_CCUActions_proxy_init(&m_ccuActionsProxy, &m_ccuTransport.base, riid);
    }

    return true;
}

bool AppConnector::StartActionAtEAIC(rtl_uint32_t _task)
{
    ffd_EAICActions_StartActionAt_req req {};
    ffd_EAICActions_StartActionAt_res res {};
    req.task = _task;
    std::cerr << "AppConnector::StartActionAtEAIC" << std::endl;
    auto code = ffd_EAICActions_StartActionAt(
        &m_eaicActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::FMAC << " -> " << connections::EAIC
                << ": StartActionAt()" << std::endl;

    } else {
         std::cerr << connections::FMAC << " -> " << connections::EAIC
                << ": StartActionAt() - FAILED" << std::endl;
    }
    return code == NK_EOK;
}

bool AppConnector::StartActionAtCCU(rtl_uint32_t _task)
{
    ffd_CCUActions_StartActionAt_req req {};
    ffd_CCUActions_StartActionAt_res res {};
    req.task = _task;
    auto code = ffd_CCUActions_StartActionAt(
        &m_ccuActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::FMAC << " -> " << connections::CCU
                << ": AppConnector::StartActionAt()" << std::endl;

    } else {
         std::cerr << connections::FMAC << " -> " << connections::CCU
                << ": AppConnector::StartActionAt() - FAILED" << std::endl;
    }

    return code == NK_EOK;
}

