cmake_minimum_required(VERSION 3.2)
project(influxdb-api-main)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
add_compile_options("-O3")

# set(Boost_USE_STATIC_LIBS ON)
# find_package(Boost COMPONENTS regex system thread)
# find_package(Threads)

add_subdirectory(thirdparty/cpp-netlib)
add_subdirectory(thirdparty/cppformat)
add_subdirectory(thirdparty/influxdb-api)

include_directories(${influxdb-api_INCLUDE_DIRS})
add_executable(influxdb-api-test
    main.cpp
)

target_link_libraries(influxdb-api-test
    influxdb-api
)