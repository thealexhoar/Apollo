//
// Created by alex on 18/12/18.
//
#pragma once

#include <algorithm>
#include <vector>

namespace apollo {

    static void set_vector_bit(std::vector<bool>& vec, size_t val) {
        if (vec.size() <= val) {
            vec.resize(val + 1, false);
        }
        vec[val] = true;
    }

    // Checks other against master
    // Returns true if, for every true value in master,
    //   other must be true at the same index
    // in bitwise terms: master & other == master
    static bool vector_check_all(const std::vector<bool>& master, const std::vector<bool>& other) {
        if (master.size() > other.size()) {
            return false;
        }
        for (auto i = 0; i < master.size(); i++) {
            if (master[i] && !other[i]) {
                return false;
            }
        }
        return true;
    }

    // Checks other against master
    // Returns true if, for at least one true valye in master,
    //   other is true at the same index
    // in bitwise terms: master | other > 0
    static bool vector_check_one(const std::vector<bool>& master, const std::vector<bool>& other) {
        auto min_size = std::min(master.size(), other.size());
        for (auto i = 0; i < min_size; i++) {
            if (master[i] && other[i]) {
                return true;
            }
        }
        return false;
    }

}