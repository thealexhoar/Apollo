/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once


namespace apollo {
    class World;

    class System {

    public:
        virtual void update(World& world) = 0;
    };

}