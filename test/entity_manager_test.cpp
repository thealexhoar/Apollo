//
// Created by alex on 18/12/18.
//

#include "catch/catch.hpp"
#include "../src/apollo.hpp"

using namespace apollo;
static constexpr const char* tag = "[entity_manager]";

TEST_CASE("EntityManager constructs properly", tag) {
    EntityManager entity_manager = EntityManager();

    REQUIRE(entity_manager.next_index() == 0);
    REQUIRE(entity_manager.currently_recycled() == 0);
}

TEST_CASE("EntityManager can create new entities", tag) {
    EntityManager entity_manager = EntityManager();

    auto entity_0 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 1);
    REQUIRE(entity_0.generation == 1);
    REQUIRE(entity_0.index == 0);
    REQUIRE(entity_manager.currently_recycled() == 0);

    auto entity_1 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 2);
    REQUIRE(entity_1.generation == 1);
    REQUIRE(entity_1.index == 1);
    REQUIRE(entity_manager.currently_recycled() == 0);

    auto entity_2 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_2.generation == 1);
    REQUIRE(entity_2.index == 2);
    REQUIRE(entity_manager.currently_recycled() == 0);
}

TEST_CASE("EntityManager can recycle existing entities", tag) {
    EntityManager entity_manager = EntityManager();

    auto entity_0 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 1);
    REQUIRE(entity_0.generation == 1);
    REQUIRE(entity_0.index == 0);
    REQUIRE(entity_manager.currently_recycled() == 0);

    auto entity_1 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 2);
    REQUIRE(entity_1.generation == 1);
    REQUIRE(entity_1.index == 1);
    REQUIRE(entity_manager.currently_recycled() == 0);

    entity_manager.recycle_entity(entity_0);
    REQUIRE(entity_manager.next_index() == 2);
    REQUIRE(entity_manager.currently_recycled() == 1);

    auto entity_2 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 2);
    REQUIRE(entity_manager.currently_recycled() == 0);
    REQUIRE(entity_2.generation == 2);
    REQUIRE(entity_2.index == 0);

    auto entity_3 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_manager.currently_recycled() == 0);
    REQUIRE(entity_3.generation == 1);
    REQUIRE(entity_3.index == 2);

    entity_manager.recycle_entity(entity_2);
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_manager.currently_recycled() == 1);

    entity_manager.recycle_entity(entity_3);
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_manager.currently_recycled() == 2);

    auto entity_4 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_manager.currently_recycled() == 1);
    REQUIRE(entity_4.generation == 2);
    REQUIRE(entity_4.index == 2);

    auto entity_5 = entity_manager.create_entity();
    REQUIRE(entity_manager.next_index() == 3);
    REQUIRE(entity_manager.currently_recycled() == 0);
    REQUIRE(entity_5.generation == 3);
    REQUIRE(entity_5.index == 0);
}