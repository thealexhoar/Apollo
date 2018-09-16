//
// Created by alex on 22/02/18.
//

#pragma once

#include "../src/system.hpp"

using namespace apollo;

class TestSystemA : public System {
private:
    TestSystemA() : System(ResourceSubscription()) {

    }
};