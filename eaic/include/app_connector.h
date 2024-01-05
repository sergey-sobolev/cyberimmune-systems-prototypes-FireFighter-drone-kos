#pragma once

#include <AggregationCoordinates.idl.h>
#include <CommunicationOutside.idl.h>
#include <ExtinguishingActions.idl.h>
#include <MovementActions.idl.h>
#include <SituationActions.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector // :
                   // public ipc::IEAICActionsReader,
                   // public ipc::IEAICActionsReader
{
public:
  AppConnector() = default;

  // Open IPC connection
  bool ConnectToAggregation();

  bool GetAggregation();

private:
  NkKosTransport m_aggregationTransport;
  ffd_AggregationCoordinates_proxy m_aggregationCoordinatesProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
