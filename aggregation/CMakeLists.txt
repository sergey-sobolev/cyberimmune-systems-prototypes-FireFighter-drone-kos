cmake_minimum_required(VERSION 3.5)

include (platform/nk)

project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -pthread -Wunused-parameter")

set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

file (
    GLOB CPP_SRC
    ${SRC_DIR}/*.cpp)

add_executable (
    Aggregation
    ${CPP_SRC})

add_dependencies (
    Aggregation
    navigation_idl
    aggregation_edl)

target_include_directories (
    Aggregation
    PRIVATE ${INCLUDE_DIR})

target_link_libraries (
    Aggregation
    ${CMAKE_THREAD_LIBS_INIT})

set_target_properties (Aggregation PROPERTIES LINK_FLAGS ${VULN_LDFLAGS})
