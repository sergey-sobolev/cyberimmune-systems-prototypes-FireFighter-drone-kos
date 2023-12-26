#pragma once

#include <memory>
#include <coresrv/sl/sl_api.h>

namespace ipc {
struct IEAICActionsReader
{
    virtual ~IEAICActionsReader() = default;

    virtual bool StartActionAt(rtl_uint32_t task) = 0;
};

using IEAICActionsReaderPtr = std::shared_ptr<IEAICActionsReader>;

} // namespace ipc
