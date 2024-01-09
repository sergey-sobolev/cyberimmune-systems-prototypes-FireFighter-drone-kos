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
    Navigation
    ${CPP_SRC})

add_dependencies (
    Navigation
    navigation_edl)

target_include_directories (
    Navigation
    PRIVATE ${INCLUDE_DIR}
    PUBLIC  ${PROJECT_INC})

target_link_libraries (
    Navigation
    ${CMAKE_THREAD_LIBS_INIT})

set_target_properties (Navigation PROPERTIES LINK_FLAGS ${VULN_LDFLAGS})
