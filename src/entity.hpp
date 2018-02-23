/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>

namespace apollo {

    typedef uint32_t EIndex;
    typedef uint32_t EGeneration;

    static constexpr const EGeneration NULL_GEN = 0;

    struct Entity {
        const EIndex index;
        const EGeneration generation;

        Entity(EIndex index, EGeneration generation) :
                index(index),
                generation(generation)
        {}

        bool operator<(const Entity& other) const {
            if (index < other.index) {
                return true;
            }
            else if(index == other.index) {
                return generation < other.generation;
            }
            else {
                return false;
            }
        }
    };
}