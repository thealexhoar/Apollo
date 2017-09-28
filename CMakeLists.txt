cmake_minimum_required(VERSION 3.8)
project(apollo)

set(CMAKE_CXX_STANDARD 11)

# Prevents cmake from following symbolic links using GLOB
cmake_policy( SET CMP0009 NEW)

set(SOURCE_FILES
        src/component_array.cpp
        src/world.cpp
        src/resource_accessor.cpp
        src/system.cpp
        src/types.cpp
        src/dispatcher.cpp)

set(HEADER_FILES
        src/apollo.hpp
        src/component.hpp
        src/component_array.hpp
        src/entity.hpp
        src/resource_accessor.hpp
        src/resource_subscription.hpp
        src/resource_wrapper.hpp
        src/system.hpp
        src/types.hpp
        src/world.hpp
        src/dispatcher.hpp)

set(CATCH_FILE test/catch/catch.hpp)

set(TEST_FILES
        test/apollo_tests.cpp
)

# Output Library
add_library(apollo STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(apollo_test ${CATCH_FILE} ${TEST_FILES})

target_link_libraries(apollo_test apollo)
