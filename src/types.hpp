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
    typedef uint32_t ComponentType;
    typedef uint32_t ResourceType;


    class Types {
    private:
        static ComponentType _component_type_counter;
        static ResourceType _resource_type_counter;

    public:
        template <class T>
        static ComponentType component_type() {
            static const ComponentType type = _component_type_counter++;
            return type;
        }

        template <class T>
        static ResourceType resource_type() {
            static const ResourceType type = _resource_type_counter++;
            return type;
        }
    };


}