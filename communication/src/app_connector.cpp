#include "app_connector.h"
#include "connections.h"

#include <rtl/string.h>

#include <iostream>

bool AppConnector::ConnectToFMAC()
{
    auto handle = ServiceLocatorConnect(connections::FMAC);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::Communication
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::FMAC;

        return false;
    }
    NkKosTransport_Init(&m_transport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "FMACActions.actions");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::Communication
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "FMACActions.actions"
                      << std::endl;
            return false;
        }
        ffd_FMACActions_proxy_init(&m_fmacActionsProxy, &m_transport.base, riid);
    }

    return true;
}


bool AppConnector::StartAt() //TODO: string value
{
    ffd_FMACActions_StartAt_req req {};
    ffd_FMACActions_StartAt_res res {};
    auto code = ffd_FMACActions_StartAt(
        &m_fmacActionsProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        std::cerr << connections::Communication << " -> " << connections::FMAC
                << ": StartAt()" << std::endl;

    }

    return code == NK_EOK;
}

