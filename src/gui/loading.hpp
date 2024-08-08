#ifndef LOADING_HPP
#define LOADING_HPP

#include <raylib.h>

class Loading {
    public:
        Loading();
        ~Loading();
        void draw();
        void update();
        int next();

    private:
        int progress;
};

#endif