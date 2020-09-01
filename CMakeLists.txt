cmake_minimum_required(VERSION 3.10)

# set the project name
project(LabirynthOfDeath VERSION 1.1)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(source)
add_subdirectory(TerminalIO/sources)

include_directories(${PROJECT_SOURCE_DIR}/headers)
add_executable(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR}/game.cpp)

target_link_libraries(${PROJECT_NAME} LabirynthCore TerminalIO)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/tiles ${CMAKE_BINARY_DIR}/tiles)