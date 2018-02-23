//
// Created by alex on 25/01/18.
//

#pragma once

#include "../src/apollo.hpp"

using namespace apollo;

class TestComponent4 {
public:
    int x;
    TestComponent4(int x) : x(x) {}
};

class TestComponent8 {
public:
    int x, y;
    TestComponent8(int x, int y) : x(x), y(y) {}
};