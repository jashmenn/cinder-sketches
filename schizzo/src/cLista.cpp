#include "cLista.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "DrawingInstruction.h"
#include "cinder/Rect.h"

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

Vec2f CLista::draw(Vec2f pen, int frame)
{
  di_t i = instructions[frame]; 
  switch(i.kind) {
    case DI_MOVE_TO:
      pen = i.loc;
      break;
    case DI_LINE_TO:
      gl::drawLine( pen, i.loc );
      pen = i.loc;
      break;
    case DI_RECT_TO:
      gl::color( ColorA( 0.0f, 0.0f, 0.0f, 1.0f ) ); 
      gl::drawSolidRect( Rectf( pen, i.loc ) );
      break;
  }
  return pen;
}

int CLista::size() 
{
   return instructions.size(); 
}
