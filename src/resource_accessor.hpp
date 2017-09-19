/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <map>

#include "component_storage.hpp"
#include "types.hpp"

namespace apollo {

    class ResourceAccessor {
    private:
        std::map<ComponentType, ComponentStorage const*> _read_components;
        std::map<ComponentType, ComponentStorage*> _write_components;
        std::map<ResourceType, void const*> _read_resources;
        std::map<ResourceType, void*> _write_resources;

    public:

        
    };

}