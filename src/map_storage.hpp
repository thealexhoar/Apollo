//
// Created by alex on 18/02/18.
//

#pragma once

#include <type_traits>
#include <unordered_map>

#include "storage.hpp"
#include "apollo.hpp"

namespace apollo {
    template<class T>
    class MapStorageReadIterator;

    template<class T>
    class MapStorageWriteIterator;


    template<class T>
    class MapStorage : public Storage<T> {
        friend class MapStorageReadIterator<T>;

        friend class MapStorageWriteIterator<T>;

    private:
        std::unordered_map<EIndex, T> _data;
        std::set<Entity> _entities;

    public:

        MapStorage() : _data(), _entities() {}


        bool add_for(const Entity& entity, const T& component) override {
            const T &datum = static_cast<const T &>(component);
            if (_data.count(entity.index) > 0) {
                return false;
            } else {
                _data.insert(std::make_pair(entity.index, datum));
                _entities.insert(entity);
                return true;
            }
        }

        T& get_for(const Entity& entity) override {
            return _data.at(entity.index);
        }

        const T& get_for(const Entity& entity) const override {
            return _data.at(entity.index);
        }

        std::shared_ptr<ReadIterator<T>> get_read_iterator() const override {
            auto ptr = std::make_shared<MapStorageReadIterator<T>>(*this);
            return std::static_pointer_cast<ReadIterator<T>>(ptr);
        }

        std::shared_ptr<WriteIterator<T>> get_write_iterator() override {
            auto ptr = std::make_shared<MapStorageWriteIterator<T>>(*this);
            return std::static_pointer_cast<WriteIterator<T>>(ptr);
        }

        bool has_for(const Entity &entity) const override {
            return _entities.count(entity) > 0;
        }

        bool remove_for(const Entity &entity) override {
            if (_entities.count(entity) == 0) {
                return false;
            } else {
                _entities.erase(entity);
                _data.erase(entity.index);
                return true;
            }
        }

        void update() override {}
    };

    template<class T>
    class MapStorageReadIterator : public ReadIterator<T> {
    private:
        const MapStorage<T> &_map_storage;
        std::_Rb_tree_const_iterator<Entity> _iter;
        bool _complete = false;

    public:
        MapStorageReadIterator(const MapStorage<T> &map_storage) :
                _map_storage(map_storage) {
            _iter = map_storage._entities.cbegin();
        }

        const T& get() const override {
            return _map_storage._data.at(_iter->index);
        }

        Entity get_entity() const override {
            return *_iter;
        }

        bool iterate() {
            if (!_complete) {
                _iter++;
                if (_iter == _map_storage._entities.cend()) {
                    _complete = true;
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        }
    };

    template<class T>
    class MapStorageWriteIterator : public WriteIterator<T> {
    private:
        MapStorage<T> &_map_storage;
        std::_Rb_tree_const_iterator<Entity> _iter;
        bool _complete = false;
    public:
        MapStorageWriteIterator(MapStorage<T> &map_storage) :
                _map_storage(map_storage) {
            _iter = _map_storage._entities.begin();
        }

        T& get() const override {
            return _map_storage._data.at(_iter->index);
        }

        Entity get_entity() const override {
            return *_iter;
        }

        bool iterate() override {
            if (!_complete) {
                _iter++;
                if (_iter == _map_storage._entities.end()) {
                    _complete = true;
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        }
    };
}

