//
// Created by alex on 18/02/18.
//

#pragma once

#include <type_traits>
#include <unordered_map>

#include "storage.hpp"
#include "apollo.hpp"

namespace apollo {
    template<class C>
    class MapStorageReadIterator;

    template<class C>
    class MapStorageWriteIterator;


    template<class C>
    class MapStorage : public Storage<C> {
        friend class MapStorageReadIterator<C>;

        friend class MapStorageWriteIterator<C>;

    private:
        std::unordered_map<EIndex, C> _data;
        std::set<Entity> _entities;

    public:

        MapStorage() : _data(), _entities() {}


        bool add_for(const Entity& entity, const C& component) override {
            const C &datum = static_cast<const C &>(component);
            if (_data.count(entity.index) > 0) {
                return false;
            } else {
                _data.insert(std::make_pair(entity.index, datum));
                _entities.insert(entity);
                return true;
            }
        }

        C& get_for(const Entity& entity) override {
            return _data.at(entity.index);
        }

        const C& get_for(const Entity& entity) const override {
            return _data.at(entity.index);
        }

        std::shared_ptr<ReadIterator<C>> get_read_iterator() const override {
            auto ptr = std::make_shared<MapStorageReadIterator<C>>(*this);
            return std::static_pointer_cast<ReadIterator<C>>(ptr);
        }

        std::shared_ptr<WriteIterator<C>> get_write_iterator() override {
            auto ptr = std::make_shared<MapStorageWriteIterator<C>>(*this);
            return std::static_pointer_cast<WriteIterator<C>>(ptr);
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

    template<class C>
    class MapStorageReadIterator : public ReadIterator<C> {
    private:
        const MapStorage<C> &_map_storage;
        std::_Rb_tree_const_iterator<Entity> _iter;
        bool _complete = false;

    public:
        MapStorageReadIterator(const MapStorage<C> &map_storage) :
                _map_storage(map_storage) {
            _iter = map_storage._entities.cbegin();
        }

        const C& get() const override {
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

    template<class C>
    class MapStorageWriteIterator : public WriteIterator<C> {
    private:
        MapStorage<C> &_map_storage;
        std::_Rb_tree_const_iterator<Entity> _iter;
        bool _complete = false;
    public:
        MapStorageWriteIterator(MapStorage<C> &map_storage) :
                _map_storage(map_storage) {
            _iter = _map_storage._entities.begin();
        }

        C& get() const override {
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

