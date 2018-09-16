cmake_minimum_required(VERSION 3.8)
project(apollo)

set(CMAKE_CXX_STANDARD 11)

# Prevents cmake from following symbolic links using GLOB
cmake_policy(SET CMP0009 NEW)

set(SOURCE_FILES
        src/world.cpp
        src/system.cpp
        src/sequential_dispatcher.cpp
        src/types.cpp src/family.cpp)

set(HEADER_FILES
        src/apollo.hpp
        src/dispatcher.hpp
        src/entity.hpp
        src/entity_manager.hpp
        src/map_storage.hpp
        src/null_storage.hpp
        src/resource_accessor.hpp
        src/resource_subscription.hpp
        src/sequential_dispatcher.hpp
        src/storage.hpp
        src/system.hpp
        src/types.hpp
        src/vec_storage.hpp
        src/world.hpp src/family.hpp)

set(CATCH_FILE test/catch/catch.hpp)

set(TEST_FILES
        test/apollo_tests.cpp
        test/test_components.hpp
        test/map_storage_test.cpp
        test/test_systems.hpp)

# Output Library
add_library(apollo STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(apollo_test ${CATCH_FILE} ${TEST_FILES})

target_link_libraries(apollo_test apollo)
