//
// Created by alex on 22/02/18.
//

#pragma once

#include "../src/system.hpp"

using namespace apollo;

class TestSystemA : public System {
private:
    static const ResourceSubscription _subscription = ResourceSubscription()
        .add_read_component(1);

    TestSystemA() : System(_subscription) {

    }
};