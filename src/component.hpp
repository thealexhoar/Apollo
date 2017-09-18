/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

namespace apollo {

    class Component {
    public:
        virtual ~Component() = 0;
    protected:
        Component();
    };

}