#pragma once

namespace connections {


constexpr const char* Aggregation = "aggregation";

// eaic -> (aggregation) : 18. get_coordinates
// aggregation --> (eaic) : 19. coordinates with val
// ccu -> (aggregation) : 9. get_coordinates
// synchronous
constexpr const char* AggregationGetCoordinates =
  "ffd.Aggregation.get_coordinates";

constexpr const char* CCU = "ccu";

// fmac --> (ccu) : 4. execute at val
// asynchronous
constexpr const char* CCUExecute =
  "ffd.CCU.execute";

// movement --> (ccu) : 13. done at val
// synchronous
constexpr const char* CCUDone =
  "ffd.CCU.done";


constexpr const char* Communication = "communication";

// (fps) --> (communication) : 1. start at val\n(via http)
// asynchronous
constexpr const char* CommunicationStart =
  "ffd.Communication.start";

// ccu --> (communication) : 30. started at val
// asynchronous
constexpr const char* CommunicationStarted =
  "ffd.Communication.started";

// fmac --> (communication) : not_authentic_task val
// synchronous
constexpr const char* CommunicationNotAuthenticTask =
  "ffd.Communication.not_authentic_task";


constexpr const char* Extinguishing = "extinguishing";

// eaic --> (extinguishing) : 21. start_action
// ccu --> (extinguishing) : 14. start_action
// asynchronous
constexpr const char* ExtinguishingStartAction =
  "ffd.Extinguishing.start_action";

// ccu --> (extinguishing) : 27. stop_action
// asynchronous
constexpr const char* ExtinguishingStopAction =
  "ffd.Extinguishing.stop_action";


constexpr const char* EAIC = "eaic";

// fmac --> (eaic) : 3. execute at val
// synchronous
constexpr const char* EAICExecute =
  "ffd.EAIC.execute";

// extinguishing --> (eaic) : 15. confirm_action
// synchronous
constexpr const char* EAICConfirmAction =
  "ffd.EAIC.confirm_action";

// extinguishing --> (eaic) : 28. stop_action
// synchronous
constexpr const char* EAICStopAction =
  "ffd.EAIC.stop_action";


constexpr const char* FMAC = "fmac";

// communication --> (fmac) : 2. start at val
constexpr const char* FMACStart =
  "ffd.FMAC.start";


constexpr const char* Movement = "movement";
// ccu --> (movement) : 11. move to val
// asynchronous

constexpr const char* MovementMove =
  "ffd.Movement.move";


constexpr const char* Navigation = "navigation";

// aggregation --> (navigation) : 5. 16. get_coordinates
// navigation --> (aggregation) : 6. 17. coordinates with val
// synchronous
constexpr const char* NavigationGetCoordinates =
  "ffd.Navigation.get_coordinates";


constexpr const char* Situation = "situation";

// ccu --> (situation) : 22. is_action_running
// situation --> (ccu) : 23. action_is_running
// synchronous
constexpr const char* SituationIsActionRunning =
  "ffd.Situation.is_action_running";


} // namespace connections
