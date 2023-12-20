#include "server.h"

#include "aggregation_coordinates.h"
#include <connections.h>
#include <iostream>

#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    std::cerr << connections::Aggregation << ": started" << std::endl;

    Server server;
    auto retCode = server.Run();

    std::cerr << connections::Aggregation << ": stoped. Exit code = " << retCode
           << std::endl;

    return retCode;
}
