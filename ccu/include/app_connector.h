#pragma once

#include <AggregationCoordinates.idl.h>
#include <CommunicationOutside.idl.h>
#include <ExtinguishingActions.idl.h>
#include <MovementActions.idl.h>
#include <SituationActions.idl.h>

#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

#include <memory>

class AppConnector// :
    //public ipc::IEAICActionsReader,
    //public ipc::ICCUActionsReader
{
public:
    AppConnector() = default;

    // Open IPC connection
    bool ConnectToAggregation();
    bool ConnectToCommunication();
    bool ConnectToExtinguishing();
    bool ConnectToMovement();
    bool ConnectToSituation();

    bool GetAggregation();
    bool StartedAtCommunication(rtl_uint32_t _task);
    bool StartActionExtinguishing();
    bool StopActionExtinguishing();
    bool MoveToMovement(rtl_uint32_t _task);
    bool ActionInProgressSituation();

private:
    NkKosTransport m_transport;
    ffd_AggregationCoordinates_proxy m_aggregationCoordinatesProxy;
    ffd_CommunicationOutside_proxy m_communicationOutsideProxy;
    ffd_ExtinguishingActions_proxy m_extinguishingActionsProxy;
    ffd_MovementActions_proxy m_movementActionsProxy;
    ffd_SituationActions_proxy m_situationActionsProxy;
};

using AppConnectorPtr = std::shared_ptr<AppConnector>;
