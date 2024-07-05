# Assuming src/CMakeLists.txt for calculator library
cmake_minimum_required(VERSION 3.22)
project(calculator)

# Set the minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files for the calculator library
file(GLOB SOURCES "*.cpp")

# Create the library
add_library(calculator STATIC ${SOURCES})  # or SHARED if it's a shared library

# Add main executable
add_executable(calculator_main main.cpp)
target_link_libraries(calculator_main calculator)

# Optionally, install the library and headers
install(TARGETS calculator DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/include/calculator/*.h DESTINATION include/calculator)
