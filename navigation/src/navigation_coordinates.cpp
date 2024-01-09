#include "navigation_coordinates.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <assert.h>

struct NavigationCoordinatesHandlerImpl : ffd_NavigationCoordinates_ops
{
  NavigationCoordinatesHandler* handler = nullptr;
};

static nk_err_t
GetImpl(struct ffd_NavigationCoordinates* self,
        __rtl_unused const ffd_NavigationCoordinates_Get_req* req,
        __rtl_unused const nk_arena* req_arena,
        ffd_NavigationCoordinates_Get_res* res,
        __rtl_unused nk_arena* res_arena)
{
  NavigationCoordinatesHandlerImpl* impl =
    (NavigationCoordinatesHandlerImpl*)self;
  res->coordinates = impl->handler->Coordinates();
  return NK_EOK;
}

ffd_NavigationCoordinates*
NavigationCoordinatesHandler::CreateImpl(rtl_uint32_t coordinates)
{
  static NavigationCoordinatesHandler position(coordinates);
  static NavigationCoordinatesHandlerImpl ops = {};
  static ffd_NavigationCoordinates impl = { .ops = &ops };

  ops.Get = GetImpl;
  ops.handler = &position;

  return &impl;
}

NavigationCoordinatesHandler::NavigationCoordinatesHandler(
  rtl_uint32_t coordinates)
{
}

rtl_uint32_t
NavigationCoordinatesHandler::Coordinates()
{
  return 123;
}
