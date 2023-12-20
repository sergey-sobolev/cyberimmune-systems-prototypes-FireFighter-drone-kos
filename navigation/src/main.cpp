#include "server.h"

#include "navigation_coordinates.h"
#include <connections.h>
#include <iostream>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    std::cerr << connections::Navigation << ": started" << std::endl;

    Server server;
    auto retCode = server.Run();

    std::cerr << connections::Navigation << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
