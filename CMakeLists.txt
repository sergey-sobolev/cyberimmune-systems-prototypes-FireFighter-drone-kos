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
nk_build_edl_files (aggregation_edl 
    NK_MODULE "ffd" 
    EDL "resources/edl/Aggregation.edl")

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

nk_build_edl_files (klog_storage_edl_files
    NK_MODULE "ffd"
    EDL "resources/edl/KlogStorageEntity.edl")

add_subdirectory (aggregation)
add_subdirectory (navigation)
add_subdirectory (situation)
add_subdirectory (klog_storage)
add_subdirectory (einit)
