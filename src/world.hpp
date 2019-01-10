/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "entity_manager.hpp"
#include "family.hpp"
#include "storage.hpp"
#include "types.hpp"

namespace apollo {


    class World {
    private:
        std::unordered_set<Entity, EntityHash> entities_, entities_created_, entities_modified_, entities_recycled_;
        EntityManager entity_manager_;
        std::vector<std::pair<Family, std::shared_ptr<std::unordered_set<Entity, EntityHash>>>> families_;
        std::unordered_map<ResourceType, std::shared_ptr<void>> resources_;
        std::unordered_map<ComponentType, std::shared_ptr<GenericStorage>> storages_;

    public:
        World() :
            entities_(),
            entities_created_(),
            entities_modified_(),
            entities_recycled_(),
            entity_manager_(),
            families_(),
            resources_(),
            storages_()
        {}
        ~World() {}

        //TODO 12/20/18: add entity creation/destruction
        //TODO 12/20/18: add family list maintenance

        Entity create_entity() {
            auto entity = entity_manager_.create_entity();
            entities_created_.insert(entity);
            return entity;
        }

        void recycle_entity(Entity entity) {
            entities_recycled_.insert(entity);
        }

        template <typename C>
        bool add_component(Entity entity, C&& component) {
            auto type = Types::component_type<C>();
            if (storages_.count(type) == 0) {
                return false;
            }
            auto storage = std::static_pointer_cast<Storage<C>>(storages_[type]);
            auto result = storage->add_for(entity, component);
            if (result) {
                entities_modified_.insert(entity);
            }
            return result;
        }

        void maintain() {
            for (auto entity : entities_recycled_) {
                for (auto iter = entities_.begin(); iter != entities_.end(); iter++) {
                    if (entity == *iter) {
                        entities_.erase(iter);
                        break;
                    }
                }
                for (auto storage : storages_) {
                    storage.second->remove_for(entity);
                }
            }

            for (auto entity : entities_created_) {
                entities_.insert(entity);
            }

            // update families

        }

        template <class C, class S>
        bool register_component() {
            static_assert(std::is_base_of<Storage<C>, S>().value, "Type S must be a Storage for C!");

            auto type = Types::component_type<C>();
            if(storages_.count(type) > 0) {
                return false;
            }
            else {
                storages_[type] = std::static_pointer_cast<GenericStorage>(std::make_shared<S>());
                return true;
            }
        }

        template <class R>
        bool register_resource(const R& initial_value) {
            auto type = Types::resource_type<R>();
            if(resources_.count(type) > 0) {
                return false;
            }
            else {
                resources_[type] = std::static_pointer_cast<void>(std::make_shared<R>());
                return true;
            }
        }

        FamilyID register_family(const Family& family) {
            auto family_entities = std::make_shared<std::unordered_set<Entity, EntityHash>>();
            for (auto entity : entities_) {
                auto bits = bits_for(entity);
                if (family.matches(bits)) {
                    family_entities->insert(entity);
                }
            }
            FamilyID id = families_.size();
            families_.push_back(std::make_pair(Family(family), family_entities));

            return id;
        }

    private:

        std::vector<bool> bits_for(const Entity& entity) {
            auto bits = std::vector<bool>();

            for (auto storage_pair : storages_) {
                auto generic_storage = std::static_pointer_cast<GenericStorage>(storage_pair.second);
                if (generic_storage->has_for(entity)) {
                    set_vector_bit(bits, static_cast<size_t>(storage_pair.first));
                }
            }

            return bits;
        }
    };

}
