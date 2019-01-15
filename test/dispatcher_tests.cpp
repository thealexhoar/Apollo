//
// Created by alex on 29/12/18.
//


//TODO: test Dispatcher + DispatcherBuilder

#include "catch/catch.hpp"
#include "../src/apollo.hpp"

using namespace apollo;
static constexpr const char* tag = "[dispatcher]";

class VectorPushSystem : public System {
public:
    int value;
    VectorPushSystem(int value) : value(value) {}
    void update(World& world) override {
        auto vector = world.get_resource<std::vector<int>>();
        vector.push_back(value);
    }
};

TEST_CASE("Can build a dispatcher", tag) {
    auto dispatcher0 = DispatcherBuilder<int>().build();
    auto dispatcher1 = DispatcherBuilder<int>()
        .with_system(std::make_shared<VectorPushSystem>(0), 0, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(1), 1, std::vector<int> {0})
        .with_system(std::make_shared<VectorPushSystem>(2), 2, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(3), 3, std::vector<int> {1, 2})
        .build();
}

TEST_CASE("Cannot build a dispatcher with missing dependencies", tag) {

    REQUIRE_THROWS(DispatcherBuilder<int>()
                       .with_system(std::make_shared<VectorPushSystem>(0), 0, std::vector<int>{})
                       .with_system(std::make_shared<VectorPushSystem>(1), 1, std::vector<int>{0})
                       .with_system(std::make_shared<VectorPushSystem>(2), 2, std::vector<int>{})
                       .with_system(std::make_shared<VectorPushSystem>(3), 3, std::vector<int>{1, 2, 5})
                       .build());
}

TEST_CASE("Cannot build a dispatcher with circular dependencies", tag) {

    REQUIRE_THROWS(DispatcherBuilder<int>()
                       .with_system(std::make_shared<VectorPushSystem>(0), 0, std::vector<int>{1})
                       .with_system(std::make_shared<VectorPushSystem>(1), 1, std::vector<int>{0})
                       .with_system(std::make_shared<VectorPushSystem>(2), 2, std::vector<int>{})
                       .build());
}

TEST_CASE("Can dispatch in order", tag) {
    auto world = World();
    world.register_resource(std::vector<int>());

    auto dispatcher0 = DispatcherBuilder<int>().build();

    auto dispatcher1 = DispatcherBuilder<int>()
        .with_system(std::make_shared<VectorPushSystem>(0), 0, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(1), 1, std::vector<int> {0})
        .with_system(std::make_shared<VectorPushSystem>(2), 2, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(3), 3, std::vector<int> {1, 2})
        .build();


    auto dispatcher2 = DispatcherBuilder<int>()
        .with_system(std::make_shared<VectorPushSystem>(0), 0, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(1), 1, std::vector<int> {0})
        .with_system(std::make_shared<VectorPushSystem>(2), 2, std::vector<int> {})
        .with_system(std::make_shared<VectorPushSystem>(3), 3, std::vector<int> {1, 2})
        .build();

    dispatcher0.dispatch(world);
    REQUIRE(world.get_resource<std::vector<int>>().size() == 0);
    dispatcher1.dispatch(world);
    REQUIRE(world.get_resource<std::vector<int>>().size() == 0);

}

