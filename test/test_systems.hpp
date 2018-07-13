//
// Created by alex on 22/02/18.
//

#pragma once

#include "../src/system.hpp"

using namespace apollo;

class TestSystemA : public System {
private:
    static const ResourceSubscription _subscription = ResourceSubscription()
            .with_read_storage(1);

    TestSystemA() : System(_subscription) {

    }
};