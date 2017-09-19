/*
CREATED: 17/09/17
NOTES: 
*/

#include "component_array.hpp"

namespace apollo {
    ComponentArray::ComponentArray(size_t initial_capacity, size_t size) :
            ComponentStorage(),
            _bytes(initial_capacity * size),
            _component_size(size),
            _current_size(0)
    {}

    ComponentArray::~ComponentArray() {}

    template<class T>
    ComponentArray ComponentArray::new_for_type(size_t initial_capacity) {
        return ComponentArray(initial_capacity, sizeof(T));
    }

    bool ComponentArray::add_for(const Entity& entity, const Component& component) {
        if (_data_lookup.count(entity) > 0) {
            return false; //entity already has a component stored!
        }
        if (_current_size == _bytes.size()) {
            _bytes.resize(_bytes.size() * 2, 0); //double the size of source array
        }
        uint8_t* target = &(_bytes.at(_current_size * _component_size));
        uint8_t const* source = reinterpret_cast<uint8_t const*>(&component);
        for (size_t i = 0; i < _component_size; i++) {
            target[i] = source[i];
        }
        _current_size++;
        _data_lookup[entity] = reinterpret_cast<Component*>(target);
        return true;
    }

    bool ComponentArray::remove_for(const Entity& entity) {
        if (_data_lookup.count(entity) > 0) {
            return false; //entity doesn't have a component stored
        }
    }
}

