#pragma once

#include <memory>

namespace ipc {
struct INavigationCoordinatesReader
{
    virtual ~INavigationCoordinatesReader() = default;

    virtual bool Get() = 0;
};

using INavigationCoordinatesReaderPtr = std::shared_ptr<INavigationCoordinatesReader>;

} // namespace ipc
