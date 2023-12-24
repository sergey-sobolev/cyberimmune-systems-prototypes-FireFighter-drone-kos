#include "helper.h"

#include <connections.h>
#include <filesystem>
#include <iostream>

#include <errno.h>
#include <string.h>
#include <sys/mount.h>
#include <unistd.h>

namespace helper {
int mountFolder(const std::string &source, const std::string &path)
{
    std::filesystem::path folderPath(path);

    std::error_code ec {};
    std::filesystem::create_directory(folderPath, ec);
    if (ec)
    {
        std::cerr << connections::Communication << ": Error: Failed to create \"" << path
                  << "\" directory: " << ec.message() << std::endl;
        return false;
    }

    if (mount(source.c_str(), path.c_str(), source.c_str(), 0, "") != 0)
    {
        std::cerr << connections::Communication << ": Failed to mount " << source << " to "
                  << path << " (error " << errno << ": " << strerror(errno)
                  << ")" << std::endl;
        return false;
    }

    return true;
}
} // namespace helper
