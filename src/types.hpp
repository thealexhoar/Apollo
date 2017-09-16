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

    class TypeManager {
    private:
        ComponentType _component_type_counter = 0;
        ResourceType _resource_type_counter = 0;
        std::map<size_t, ComponentType> _component_types;
        std::map<size_t, ResourceType> _resource_types;


    public:
        TypeManager();
        ~TypeManager();

        ComponentType get_component_type(const std::type_info& type_info);

        template <class T>
        ComponentType get_component_type() {
            return get_component_type(typeid(T));
        }

        ResourceType get_resource_type(const std::type_info& type_info);

        template <class T>
        ResourceType get_resource_type() {
            return get_resource_type(typeid(T));
        }

    };

}