#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include <list>
#include <vector>

class cLista {
 public:
    cLista();
    void add( int type, Vec2f loc );
    void draw();
};

