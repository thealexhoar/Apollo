#pragma once

//simplified single-import header
// TODO: fully populate

#include "dispatcher.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "map_storage.hpp"
#include "null_storage.hpp"
#include "resource_accessor.hpp"
#include "resource_subscription.hpp"
#include "sequential_dispatcher.hpp"
#include "storage.hpp"
#include "system.hpp"
#include "types.hpp"
#include "vec_storage.hpp"
#include "world.hpp"



#define NUM_ARGS(...)  (sizeof((int[]){1, __VA_ARGS__})/sizeof(int) - 1)

#define TEST(...) { \
    printf("NUM ARGS IS %d\n", NUM_ARGS(__VA_ARGS__)); \
}

