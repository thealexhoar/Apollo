/*
CREATED: 26/09/17
NOTES: 
*/

#pragma once

#include "world.hpp"

namespace apollo {
    class World;

    class Dispatcher {
    public:
        virtual void dispatch(World& world) = 0;
    };

}