#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include <list>
#include <vector>
#include "DrawingInstruction.h"

class CLista {
 public:
    CLista();
    void add( int type, ci::Vec2f loc );
    void add( di_t instruction );
    void draw(int frame);
    int size();
	std::vector<di_t> instructions;
};

