#cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S src .

# only for cmake --version >= 3.0.0
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 17)

# project name
project(template VERSION 0.1.0)

# creates the variable EXEC and sets it to
set(EXEC main)

include(CTest)
enable_testing()

# I../includes
include_directories(include)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_target(run
    COMMAND ${EXEC}
    DEPENDS ${EXEC}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
