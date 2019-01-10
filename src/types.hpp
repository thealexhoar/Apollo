/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <map>
#include <typeinfo>
#include <vector>

namespace apollo {
    typedef int32_t ComponentType;
    typedef int32_t ResourceType;

    class Types {
    private:
        static ComponentType component_type_counter() {
            static ComponentType counter = 0;
            return counter++;
        }
        static ResourceType resource_type_counter() {
            static ResourceType counter = 0;
            return counter++;
        }

    public:
        template <class C>
        static ComponentType component_type() {
            static const ComponentType type = component_type_counter();
            return type;
        }

        template <class R>
        static ResourceType resource_type() {
            static const ResourceType type = resource_type_counter();
            return type;
        }
    };


    //ComponentType Types::_component_type_counter = 0;
    //ResourceType Types::_resource_type_counter = 0;
}