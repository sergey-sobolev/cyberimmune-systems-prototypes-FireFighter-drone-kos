#pragma once

#include <memory>
#include <coresrv/sl/sl_api.h>

namespace ipc {
struct IFMACActionsReader
{
    virtual ~IFMACActionsReader() = default;

    virtual bool StartAt(rtl_uint32_t task) = 0;
};

using IFMACActionsReaderPtr = std::shared_ptr<IFMACActionsReader>;

} // namespace ipc
