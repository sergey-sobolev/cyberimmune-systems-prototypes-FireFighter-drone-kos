#pragma once

#include <Navigation.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class NavigationCoordinatesHandler : ffd_NavigationCoordinates_ops
{
    public:
        static ffd_NavigationCoordinates *CreateImpl(rtl_uint32_t coordinates);
        rtl_uint32_t Coordinates();

        NavigationCoordinatesHandler() = delete;
        ~NavigationCoordinatesHandler() = default;

    private:
        NavigationCoordinatesHandler(rtl_uint32_t coordinates);
};
