#pragma once

#include <Aggregation.edl.h>
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

class AggregationCoordinatesHandler : ffd_AggregationCoordinates_ops
{
public:
  static ffd_AggregationCoordinates* CreateImpl(rtl_uint32_t coordinates);
  rtl_uint32_t Coordinates();

  AggregationCoordinatesHandler() = delete;
  ~AggregationCoordinatesHandler() = default;

private:
  AggregationCoordinatesHandler(rtl_uint32_t coordinates);
};
