/*
CREATED: 22/09/17
NOTES: 
*/

#include "resource_accessor.hpp"

namespace apollo {

    ResourceAccessor::ResourceAccessor(TypeManager& type_manager) :
            _read_components(),
            _write_components(),
            _read_resources(),
            _write_resources(),
            _type_manager(type_manager)
    {}

    template <class T>
    T const* ResourceAccessor::read_component(const Entity& entity) {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_read_components.count(type) > 0) {
            return reinterpret_cast<T const*>(_read_components[type]->get_for(entity));
        }
        else {
            return NULL;
        }
    }

    template <class T>
    T* ResourceAccessor::write_component(const Entity& entity) {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_write_components.count(type) > 0) {
            return reinterpret_cast<T*>(_write_components[type]->get_for(entity));
        }
        else {
            return NULL;
        }
    }

    template <class T>
    T const* ResourceAccessor::read_component_data() {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_read_components.count(type) > 0) {
            return reinterpret_cast<T const*>(_read_components[type]->get_data());
        }
        else {
            return NULL;
        }

    }

    template <class T>
    T* ResourceAccessor::write_component_data() {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_write_components.count(type) > 0) {
            return reinterpret_cast<T*>(_write_components[type]->get_data());
        }
        else {
            return NULL;
        }
    }

    template <class T>
    T const* ResourceAccessor::read_resource() {
        ResourceType type = _type_manager.get_resource_type<T>();
        if (_read_resources.count(type) > 0) {
            return _read_resources[type]->get<T>();
        }
        else {
            return NULL;
        }
    }

    template <class T>
    T* ResourceAccessor::write_resource() {
        ResourceType type = _type_manager.get_resource_type<T>();
        if (_write_resources.count(type) > 0) {
            return _read_resources[type]->get<T>();
        }
        else {
            return NULL;
        }
    }
}