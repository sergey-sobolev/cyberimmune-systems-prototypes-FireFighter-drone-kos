#pragma once

#include <memory>
#include <coresrv/sl/sl_api.h>

namespace ipc {
struct ICCUActionsReader
{
    virtual ~ICCUActionsReader() = default;

    virtual bool StartActionAtCCU(rtl_uint32_t task) = 0;
};

using ICCUActionsReaderPtr = std::shared_ptr<ICCUActionsReader>;

} // namespace ipc
