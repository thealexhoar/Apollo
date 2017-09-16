cmake_minimum_required(VERSION 3.8)
project(apollo)



# Prevents cmake from following symbolic links using GLOB
cmake_policy( SET CMP0009 NEW)

set(SOURCE_FILES

)

set(HEADER_FILES
        src/apollo.hpp
        src/world.cpp src/world.hpp src/system.hpp src/system.cpp src/resource_subscription.hpp src/types.hpp src/types.cpp)

# Output Library
add_library(Apollo STATIC ${SOURCE_FILES} ${HEADER_FILES})
