//
// Created by alex on 29/05/18.
//
#include "resource_accessor.hpp"

namespace apollo {
    ResourceAccessor::ResourceAccessor(World& world) :
        read_resources_(),
        read_storages_(),
        write_resources_(),
        write_storages_(),
        world_(world)
    {}

    ResourceAccessor::~ResourceAccessor() {
        for (auto iter = read_resources_.begin(); iter != read_resources_.end(); ++iter) {
            world_.resource_locks_[iter->first].release_from_read();
        }
        for (auto iter = read_storages_.begin(); iter != read_storages_.end(); ++iter) {
            world_.storage_locks_[iter->first].release_from_read();
        }
        for (auto iter = write_resources_.begin(); iter != write_resources_.end(); ++iter) {
            world_.resource_locks_[iter->first].release_from_write();
        }
        for (auto iter = write_storages_.begin(); iter != write_storages_.end(); ++iter) {
            world_.storage_locks_[iter->first].release_from_write();
        }
    }
}