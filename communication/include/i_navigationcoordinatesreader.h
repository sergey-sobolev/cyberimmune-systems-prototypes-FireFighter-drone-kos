#pragma once

#include <memory>

namespace ipc {
struct IFMACActionsReader
{
    virtual ~IFMACActionsReader() = default;

    virtual bool StartAt() = 0; // value string
};

using IFMACActionsReaderPtr = std::shared_ptr<IFMACActionsReader>;

} // namespace ipc
