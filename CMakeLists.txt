cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("tools/gate/HunterGate.cmake")

HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(dbcs)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(
  Boost
  COMPONENTS
  program_options
  thread
  log
  filesystem
)
find_package(
  Boost
  CONFIG REQUIRED
  program_options
  thread
  log
  log_setup
  filesystem
)
hunter_add_package(rocksdb)
find_package(RocksDB CONFIG REQUIRED)
find_package(Threads)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(kv_storage STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Random.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/DataBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/logs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Globals.cpp
)

target_include_directories(
  kv_storage
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
  kv_storage
  Boost::program_options
  Boost::thread
  Boost::log
  Boost::log_setup
  Boost::filesystem
  RocksDB::rocksdb
)

add_executable(
  tests2
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

target_include_directories(
        tests2
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GTEST_ROOT}/include
)

target_link_libraries(
        tests2
        ${CMAKE_THREAD_LIBS_INIT}
        GTest::gtest
        GTest::main
        kv_storage
)