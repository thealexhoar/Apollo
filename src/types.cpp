/*
CREATED: 16/09/17
NOTES: 
*/

#include "types.hpp"

namespace apollo {
    TypeManager::TypeManager() : _component_types(), _resource_types() {}

    TypeManager::~TypeManager() {}

    ComponentType TypeManager::get_component_type(const std::type_info& type_info) {
        auto hash_code = type_info.hash_code();
        if (_component_types.count(hash_code) == 0) {
            _component_types[hash_code] = _component_type_counter++;
        }
        return _component_types[hash_code];
    }

    ResourceType TypeManager::get_resource_type(const std::type_info& type_info) {
        auto hash_code = type_info.hash_code();
        if (_resource_types.count(hash_code) == 0) {
            _resource_types[hash_code] = _resource_type_counter++;
        }
        return _resource_types[hash_code];
    }
}