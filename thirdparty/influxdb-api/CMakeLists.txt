
project(influxdb-api)

set(CMAKE_CXX_STANDARD 14)

find_package(cppnetlib)
include_directories(${CMAKE_SOURCE_DIR})
include_directories ( ${CPPNETLIB_INCLUDE_DIRS} )
add_library(${PROJECT_NAME}
    command/create.hpp
    command/drop.hpp
    command/insert.hpp
    command/query.hpp
    command.hpp
    api.cpp
    api.hpp
    measurement/tag.hpp
    measurement/field.hpp
    measurement.cpp
    measurement.hpp
)

target_link_libraries(${PROJECT_NAME}
    cppnetlib-client-connections
    cppnetlib-uri
    cppformat
    pthread
)

set(${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
install(FILES ${PROJECT_NAME} DESTINATION lib)