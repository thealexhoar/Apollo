cmake_minimum_required(VERSION 3.8)
project(apollo)

set(CMAKE_CXX_STANDARD 11)

# Prevents cmake from following symbolic links using GLOB
cmake_policy(SET CMP0009 NEW)

set(HEADER_FILES
        src/apollo.hpp
        src/dispatcher.hpp
        src/entity.hpp
        src/entity_manager.hpp
        src/family.hpp
        src/map_storage.hpp
        src/null_storage.hpp
        src/storage.hpp
        src/system.hpp
        src/types.hpp
        src/vec_storage.hpp
        src/vector_bit_ops.hpp
        src/world.hpp)

set(CATCH_FILE test/catch/catch.hpp)

set(TEST_FILES
        test/apollo_tests.cpp
        test/entity_manager_test.cpp
        test/family_test.cpp
        test/map_storage_test.cpp
        test/test_components.hpp
        test/test_systems.hpp test/dispatcher_tests.cpp test/storage_tests.hpp test/world_tests.cpp test/null_storage_tests.cpp test/vec_storage_tests.cpp)

add_executable(apollo_test ${CATCH_FILE} ${TEST_FILES} ${HEADER_FILES})