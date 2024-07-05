cmake_minimum_required(VERSION 3.10)
project(calculator)

# Set the minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/include)

# Include subdirectories
add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME CalculatorTest COMMAND test_calculator)
