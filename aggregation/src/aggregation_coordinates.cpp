#include "aggregation_coordinates.h"
#include <connections.h>
#include <iostream>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <assert.h>

struct AggregationCoordinatesHandlerImpl : ffd_AggregationCoordinates_ops
{
  AggregationCoordinatesHandler* handler = nullptr;
};

static nk_err_t
GetImpl(struct ffd_AggregationCoordinates* self,
        __rtl_unused const ffd_AggregationCoordinates_Get_req* req,
        __rtl_unused const nk_arena* req_arena,
        ffd_AggregationCoordinates_Get_res* res,
        __rtl_unused nk_arena* res_arena)
{
  AggregationCoordinatesHandlerImpl* impl =
    (AggregationCoordinatesHandlerImpl*)self;
  res->coordinates = impl->handler->Coordinates();
  return NK_EOK;
}

ffd_AggregationCoordinates*
AggregationCoordinatesHandler::CreateImpl(rtl_uint32_t coordinates)
{
  static AggregationCoordinatesHandler position(coordinates);
  static AggregationCoordinatesHandlerImpl ops = {};
  static ffd_AggregationCoordinates impl = { .ops = &ops };

  ops.Get = GetImpl;
  ops.handler = &position;

  return &impl;
}

AggregationCoordinatesHandler::AggregationCoordinatesHandler(
  rtl_uint32_t coordinates)
{
}

rtl_uint32_t
AggregationCoordinatesHandler::Coordinates()
{
  return 123;
}
