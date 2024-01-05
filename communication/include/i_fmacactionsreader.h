#pragma once

#include <coresrv/sl/sl_api.h>
#include <memory>

namespace ipc {
struct IFMACActionsReader
{
  virtual ~IFMACActionsReader() = default;

  virtual bool StartAt(rtl_uint32_t task) = 0;
};

using IFMACActionsReaderPtr = std::shared_ptr<IFMACActionsReader>;

} // namespace ipc
