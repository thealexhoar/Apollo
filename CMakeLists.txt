cmake_minimum_required(VERSION 3.8)
project(apollo)



# Prevents cmake from following symbolic links using GLOB
cmake_policy( SET CMP0009 NEW)

set(SOURCE_FILES
        src/world.cpp
        src/system.cpp
        src/types.cpp
        src/component_array.cpp)

set(HEADER_FILES
        src/apollo.hpp
        src/component.hpp
        src/component_array.hpp
        src/entity.hpp
        src/resource_accessor.hpp
        src/resource_subscription.hpp
        src/system.hpp
        src/types.hpp
        src/world.hpp
)

# Output Library
add_library(Apollo STATIC ${SOURCE_FILES} ${HEADER_FILES})
