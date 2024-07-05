# Set the minimum C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB SOURCES "*.cpp")

# Create the test executable
add_executable(test_calculator ${SOURCES})

# Link the calculator library
target_link_libraries(test_calculator calculator)
