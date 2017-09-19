/*
CREATED: 19/09/17
NOTES: 
*/
#include "component_map.hpp"
namespace apollo {

    ComponentMap::ComponentMap(size_t size) :
            ComponentStorage(),
            _component_size(size)
    {}

    ComponentMap:: ~ComponentMap() {
        for (auto i = _data_lookup.begin(); i != _data_lookup.end(); i++) {
            uint8_t* bytes = reinterpret_cast<uint8_t*>(i->second);
            delete[] bytes;
        }
    }

    template <class T>
    ComponentMap ComponentMap::new_for_type() {
        return ComponentMap(sizeof(T));
    }

    bool ComponentMap::add_for(const Entity& entity, const Component& component) {
        if (_data_lookup.count(entity) > 0) {
            return false; //entity already has a component stored!
        }

        uint8_t* target = new uint8_t[_component_size];
        uint8_t const* source = reinterpret_cast<uint8_t const*>(&component);
        for (size_t i = 0; i < _component_size; i++) {
            target[i] = source[i];
        }
        _data_lookup[entity] = reinterpret_cast<Component*>(target);
        return true;
    }

    bool ComponentMap::remove_for(const Entity& entity) {
        if (_data_lookup.count(entity) > 0) {
            return false; //entity doesn't have a component stored
        }
        uint8_t* bytes = reinterpret_cast<uint8_t*>(_data_lookup[entity]);
        delete[] bytes;
        _data_lookup.erase(entity);
        return true;
    }
}