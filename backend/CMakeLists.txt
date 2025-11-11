cmake_minimum_required(VERSION 3.15)
project(chatbot_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Drogon CONFIG REQUIRED)
find_package(JsonCpp CONFIG REQUIRED)

# Add executable
add_executable(chatbot
    src/main.cpp
    src/file_io.cpp
)

# Link libraries
target_include_directories(chatbot PRIVATE 
    ${CMAKE_SOURCE_DIR}/logs/include
)

target_link_libraries(chatbot PRIVATE
    Drogon::Drogon
    JsonCpp::JsonCpp
)