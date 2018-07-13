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

        bool operator==(const Entity& other) const {
            return index == other.index && generation == other.generation;
        }
    };

    struct EntityHash
    {
        std::size_t operator()(Entity const& e) const noexcept
        {
            auto h1 = static_cast<std::size_t>(e.index);
            auto h2 = static_cast<std::size_t>(e.generation);
            return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
        }
    };
}