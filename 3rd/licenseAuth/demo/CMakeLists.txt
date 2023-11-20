cmake_minimum_required(VERSION 2.6)

project(testLiblicenseAuth)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INSTALL_RPATH "./")

set(CMAKE_C_FLAGS "-O3 -Wall -Werror -Wno-deprecated-declarations -fpic -fPIC -D_LARGEFILE64_SOURCE")
set(CMAKE_CXX_FLAGS " -std=c++11 -O3 -Werror -Wall -Wno-deprecated-declarations -fpic -fPIC -D_LARGEFILE64_SOURCE")

find_library(LICENSE_LIB licenseAuth ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

file (GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}  
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )
        
target_link_libraries(${PROJECT_NAME}
        ${LICENSE_LIB}
        glog
        )

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin/usr/local/vas/)

