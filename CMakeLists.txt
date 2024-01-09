cmake_minimum_required (VERSION 3.12)
project (firefighter_drone)

# Initialize CMake library for KasperskyOS SDK.
include (platform)
initialize_platform (FORCE_STATIC)

# Tools for using NK parser.
include (platform/nk)

# klog
find_package (klog REQUIRED)
include_directories (${klog_INCLUDE})

# klog_storage_entity
find_package (klog_storage REQUIRED)
include_directories (${klog_storage_INCLUDE})

find_package(kss REQUIRED)

find_package(vfs REQUIRED)
include_directories (${vfs_INCLUDE})

find_package (precompiled_vfs REQUIRED)
include_directories (${precompiled_vfs_INCLUDE})

# dhcp implementation
find_package (rump REQUIRED COMPONENTS DHCPCD_ENTITY)
include_directories (${rump_INCLUDE})

if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm|aarch64")
    # This command will find the BSP package components
    # (BSP_HW_ENTITY, BSP_QEMU_ENTITY and BSP_CLIENT_LIB)
    find_package (bsp REQUIRED)
    include_directories (${bsp_INCLUDE})
endif ()

# Add a package with the GPIO client library.
find_package (gpio REQUIRED COMPONENTS CLIENT_LIB ENTITY)
include_directories (${gpio_INCLUDE})

option(ROOTFS_SDCARD "Use SD card to mount root filesystem" OFF)
message(STATUS "Use SD card to mount root filesystem - ${ROOTFS_SDCARD}")

# Include the directory with the generated config header files.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Include the directory with header files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/resources/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Recommended compiler flags against vulnerabilities.
set(VULN_LDFLAGS "\
    -Wl,-z,noexecstack \
    -Wl,-z,separate-code \
    -Wl,-z,now")
set(VULN_COMPILER_FLAGS "\
    -Wall -Wextra -Wconversion \
    -fPIE -pie -D_FORTIFY_SOURCE=2 -O2 \
    -fstack-protector-strong -fstack-clash-protection \
    -mbranch-protection=standard \
    -Wsign-conversion -Wformat=2 -Wformat-security -Werror=format-security \
    -fsanitize=undefined -fsanitize-undefined-trap-on-error")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${VULN_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${VULN_COMPILER_FLAGS}")

# Aggregation
nk_build_idl_files (aggregation_idl 
    NK_MODULE "ffd" 
    IDL "resources/idl/AggregationCoordinates.idl")
nk_build_cdl_files (aggregation_cdl
    IDL_TARGET aggregation_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/AggregationCoordinates.cdl")
nk_build_edl_files (aggregation_edl
    CDL_TARGET aggregation_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Aggregation.edl")

# CCU
nk_build_idl_files (ccu_idl
    NK_MODULE "ffd"
    IDL "resources/idl/CCUActions.idl")
nk_build_cdl_files (ccu_cdl
    IDL_TARGET ccu_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/CCUActions.cdl")
nk_build_edl_files (ccu_edl
    CDL_TARGET ccu_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/CCU.edl")

# Communication
nk_build_idl_files (communication_idl
    NK_MODULE "ffd"
    IDL "resources/idl/CommunicationOutside.idl")
nk_build_cdl_files (communication_cdl
    IDL_TARGET communication_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/CommunicationOutside.cdl")
nk_build_edl_files (communication_edl
    CDL_TARGET communication_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Communication.edl")

# Extinguishing
nk_build_idl_files (extinguishing_idl
    NK_MODULE "ffd"
    IDL "resources/idl/ExtinguishingActions.idl")
nk_build_cdl_files (extinguishing_cdl
    IDL_TARGET extinguishing_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/ExtinguishingActions.cdl")
nk_build_edl_files (extinguishing_edl
    CDL_TARGET extinguishing_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Extinguishing.edl")

# EAIC
nk_build_idl_files (eaic_idl
    NK_MODULE "ffd"
    IDL "resources/idl/EAICActions.idl")
nk_build_cdl_files (eaic_cdl
    IDL_TARGET eaic_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/EAICActions.cdl")
nk_build_edl_files (eaic_edl
    CDL_TARGET eaic_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/EAIC.edl")

# FMAC
nk_build_idl_files (fmac_idl
    NK_MODULE "ffd"
    IDL "resources/idl/FMACActions.idl")
nk_build_cdl_files (fmac_cdl
    IDL_TARGET fmac_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/FMACActions.cdl")
nk_build_edl_files (fmac_edl
    CDL_TARGET fmac_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/FMAC.edl")

# Movement
nk_build_idl_files (movement_idl
    NK_MODULE "ffd"
    IDL "resources/idl/MovementActions.idl")
nk_build_cdl_files (movement_cdl
    IDL_TARGET movement_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/MovementActions.cdl")
nk_build_edl_files (movement_edl
    CDL_TARGET movement_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Movement.edl")

# Navigation
nk_build_idl_files (navigation_idl
    NK_MODULE "ffd"
    IDL "resources/idl/NavigationCoordinates.idl")
nk_build_cdl_files (navigation_cdl
    IDL_TARGET navigation_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/NavigationCoordinates.cdl")
nk_build_edl_files (navigation_edl
    CDL_TARGET navigation_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Navigation.edl")

# Situation
nk_build_idl_files (situation_idl
    NK_MODULE "ffd"
    IDL "resources/idl/SituationActions.idl")
nk_build_cdl_files (situation_cdl
    IDL_TARGET situation_idl
    NK_MODULE "ffd"
    CDL "resources/cdl/SituationActions.cdl")
nk_build_edl_files (situation_edl
    CDL_TARGET situation_cdl
    NK_MODULE "ffd"
    EDL "resources/edl/Situation.edl")

# KLog
nk_build_edl_files (klog_edl_files
    NK_MODULE "ffd"
    EDL "resources/edl/KlogEntity.edl")

# Klog storage
nk_build_edl_files (klog_storage_edl_files
    NK_MODULE "ffd"
    EDL "resources/edl/KlogStorageEntity.edl")

# fps is a web server which runs separate
add_custom_target(fps COMMAND make fps
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fps
)
add_subdirectory (aggregation)
add_subdirectory (ccu)
add_subdirectory (communication)
add_subdirectory (extinguishing)
add_subdirectory (eaic)
add_subdirectory (fmac)
add_subdirectory (movement)
add_subdirectory (navigation)
add_subdirectory (situation)
add_subdirectory (klog_storage)
add_subdirectory (einit)
