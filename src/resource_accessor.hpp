/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <map>
#include "types.hpp"

namespace apollo {

    class ResourceAccessor {
    private:
        std::map<ComponentType, ComponentType> _read_components;
        std::map<ComponentType, ComponentType> _write_components;
        std::map<ResourceType, ResourceType> _read_resources;
        std::map<ResourceType, ResourceType> _write_resources;

        
    };

}