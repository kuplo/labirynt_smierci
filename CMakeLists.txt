cmake_minimum_required(VERSION 3.10)

# set the project name
project(LabirynthOfDeath VERSION 1.1)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(source)

target_include_directories(LabirynthCore PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/headers"
                          )
                          
  add_executable(LabirynthOfDeath ${PROJECT_SOURCE_DIR}/game.cpp)
  
  target_link_libraries(LabirynthOfDeath PUBLIC LabirynthCore)