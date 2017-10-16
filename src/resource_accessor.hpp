/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <unordered_map>

#include "component_array.hpp"
#include "resource_wrapper.hpp"
#include "types.hpp"

namespace apollo {

    //Worlds "create" ResourceAccessors, so best to forward declare here
    class ComponentArray;
    class World;

    class ResourceAccessor {
        friend class World;

    private:
        //TODO 9/26/17: add Dispatcher as a friend class
        std::unordered_map<ComponentType, ComponentArray const*> _read_components;
        std::unordered_map<ComponentType, ComponentArray*> _write_components;
        std::unordered_map<ResourceType, ResourceWrapper const*> _read_resources;
        std::unordered_map<ResourceType, ResourceWrapper*> _write_resources;

        TypeManager& _type_manager;

    private:
        ResourceAccessor(TypeManager& type_manager);

    public:
        template <class T>
        T const* read_component(const Entity& entity);

        template <class T>
        T* write_component(const Entity& entity);

        template <class T>
        T const* read_component_data();

        template <class T>
        T* write_component_data();

        template <class T>
        T const* read_resource();

        template <class T>
        T* write_resource();
        
    };

}