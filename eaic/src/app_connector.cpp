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
            << connections::EAIC
            << " - "
            << "Error: can`t establish static IPC connection! Connection Name: "
            << connections::Aggregation;

        return false;
    }
    NkKosTransport_Init(&m_aggregationTransport, handle, NK_NULL, 0);


    {
        nk_iid_t riid =
            ServiceLocatorGetRiid(handle, "AggregationCoordinates.coordinates");
        if (riid == INVALID_RIID)
        {
            std::cerr << connections::EAIC
                      << " - "
                      << "Error: can`t get runtime implementation ID (RIID) of "
                         "interface '"
                      << "AggregationCoordinates.coordinates"
                      << std::endl;
            return false;
        }
        ffd_AggregationCoordinates_proxy_init(&m_aggregationCoordinatesProxy, &m_aggregationTransport.base, riid);
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
        std::cerr << connections::EAIC << " -> " << connections::Aggregation
                << ": Get()" << std::endl;

    } else {
         std::cerr << connections::EAIC << " -> " << connections::Aggregation
                << ": Get() - FAILED" << std::endl;
    }
    // res->result coordinates
    return code == NK_EOK;
}

