#include "app_connector.h"
#include "connections.h"

#include <rtl/string.h>

#include <iostream>

bool AppConnector::Connect()
{
    auto handle = ServiceLocatorConnect(connections::Navigation);
    if (handle == INVALID_HANDLE)
    {
        std::cerr
            << connections::Aggregation
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Navigation;

        return false;
    }
    NkKosTransport_Init(&m_navigationTransport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "NavigationCoordinates.coordinates");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::Aggregation
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "NavigationCoordinates.coordinates" //ControlConnectionPoint
                      << std::endl;
            return false;
        }
        ffd_NavigationCoordinates_proxy_init(&m_navigationCoordinatesProxy, &m_navigationTransport.base, riid);
    }

    return true;
}

bool AppConnector::Get()
{
    ffd_NavigationCoordinates_Get_req req {};
    ffd_NavigationCoordinates_Get_res res {};
    auto code = ffd_NavigationCoordinates_Get(
        &m_navigationCoordinatesProxy.base, &req, NULL, &res, NULL);
    if (code == NK_EOK)
    {
        //result = response.result; TODO: save coordinates
        std::cerr << connections::Aggregation << " -> " << connections::Navigation
                << ": coordinates(), result: " << (int)res.coordinates << std::endl;

    }

    return code == NK_EOK;
}

