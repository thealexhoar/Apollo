/*
CREATED: 26/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <vector>

namespace apollo {

    class ResourceWrapper {
    private:
        size_t _size;
        std::vector<uint8_t> _data;

        ResourceWrapper(size_t size) :
                _size(size),
                _data(size)
        {}

    public:

        template <class T>
        static ResourceWrapper* new_for_type(const T& resource) {
            ResourceWrapper* output = new ResourceWrapper(sizeof(T));
            uint8_t const* source = reinterpret_cast<uint8_t const*>(&resource);
            for (size_t i = 0; i < output->_size; i++) {
                output->_data.data()[i] = source[i];
            }
            return output;
        }

        template <class T>
        T const* get() const {
            return reinterpret_cast<T const*>(_data.data());
        }

        template <class T>
        T* get() {
            return reinterpret_cast<T*>(_data.data());
        }
    };

}