cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Add source files
add_executable(server src/main.cpp src/ServerNetwork.cpp)

# Include header files
target_include_directories(server PRIVATE lib)

# Link against Winsock2 library (Windows)
target_link_libraries(server ws2_32)