#include "cLista.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "DrawingInstruction.h"

using namespace ci;

CLista::CLista()
{
}

void CLista::add(di_t instruction)
{
  instructions.push_back(instruction);
}

void CLista::add(int type, Vec2f loc)
{
  di_t di = DIMake(type, loc);
  add(di);
}

void CLista::draw(int frame)
{
  di_t i = instructions[frame]; 
  switch(i.kind) {
    case 0:
      gl::drawLine( Vec2f(0, 0), i.loc);
      break;
  }
}

int CLista::size() 
{
   return instructions.size(); 
}
