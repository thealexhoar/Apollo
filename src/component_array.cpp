/*
CREATED: 17/09/17
NOTES: 
*/

#include "component_array.hpp"

namespace apollo {
    ComponentArray::ComponentArray(size_t initial_capacity, size_t size) :
            _bytes(initial_capacity * size),
            _comparison(NULL),
            _component_size(size),
            _current_size(0),
            _data_lookup(),
            _reverse_data_lookup()
    {}

    ComponentArray::ComponentArray(
            size_t initial_capacity,
            size_t size,
            int (*comparison)(Component*, Component*)
    ) :
            _bytes(initial_capacity * size),
            _comparison(comparison),
            _component_size(size),
            _current_size(0),
            _data_lookup(),
            _reverse_data_lookup()
    {}

    ComponentArray::~ComponentArray() {}

    template<class T>
    ComponentArray* ComponentArray::new_for_type(size_t initial_capacity) {
        return new ComponentArray(initial_capacity, sizeof(T));
    }

    template <class T>
    ComponentArray* ComponentArray::new_for_type(
            size_t initial_capacity,
            int (*comparison)(Component*, Component*)
    ) {
        return new ComponentArray(initial_capacity, sizeof(T), comparison);
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
        _reverse_data_lookup[reinterpret_cast<Component*>(target)] = entity;
        return true;
    }

    bool ComponentArray::remove_for(const Entity& entity) {
        if (_data_lookup.count(entity) > 0) {
            return false; //entity doesn't have a component stored
        }

        //copy final element in array (source) to deleted element's location (target)
        //and clear final element
        uint8_t* target = reinterpret_cast<uint8_t*>(_data_lookup[entity]);
        uint8_t* source = &(_bytes.at(_current_size * _component_size));
        for (size_t i = 0; i < _component_size; i++) {
            target[i] = source[i];
            source[i] = 0;
        }

        _current_size--;
        _data_lookup.erase(entity);

        //then modify the lookup table
        //point the previously final element's entity towards the new location
        Entity moved = _reverse_data_lookup[reinterpret_cast<Component*>(source)];
        _reverse_data_lookup.erase(reinterpret_cast<Component*>(source));
        _data_lookup[moved] = reinterpret_cast<Component*>(target);
        _reverse_data_lookup[reinterpret_cast<Component*>(target)] = moved;

        return true;
    }

    void ComponentArray::sort() {
        //allows for non-sorted component arrays
        if(_comparison == NULL) {
            return;
        }

        uint8_t* data = _bytes.data();

        for (size_t i = 2; i < _current_size; i++) {
            for (size_t k = i; k > 1; k--) {
                Component* c1 = reinterpret_cast<Component*>(data + k * _component_size);
                Component* c2 = reinterpret_cast<Component*>(data + (k - 1) * _component_size);
                if (_comparison(c1, c2) < 0) {
                    swap(c1, c2);
                }
                else {
                    break;
                }
            }
        }
    }

    void ComponentArray::swap(Component* c1, Component* c2) {
        uint8_t* b1 = reinterpret_cast<uint8_t*>(c1);
        uint8_t* b2 = reinterpret_cast<uint8_t*>(c2);

        //swap the raw bytes
        for (size_t i = 0; i < _component_size; i++) {
            uint8_t temp = *(b1 + i);
            *(b1 + i) = *(b2 + i);
            *(b2 + i) = temp;
        }

        //modify the lookup indices
        Entity e1 = _reverse_data_lookup[c1];
        Entity e2 = _reverse_data_lookup[c2];

        _reverse_data_lookup[c1] = e2;
        _reverse_data_lookup[c2] = e1;

        _data_lookup[e1] = c2;
        _data_lookup[e2] = c1;
    }
}

