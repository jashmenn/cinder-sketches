#pragma once
#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include <vector>

struct DrawingInstruction {
  int kind;
  ci::Vec2f loc;
};
typedef DrawingInstruction di_t; 

inline DrawingInstruction DIMake(int kind, ci::Vec2f loc)
{
    DrawingInstruction p; p.kind = kind; p.loc = loc; return p;
}

inline DrawingInstruction DIMakef(int kind, float x, float y)
{
    DrawingInstruction p; ci::Vec2f loc = ci::Vec2f( x, y ); p.kind = kind; p.loc = loc; return p;
}
