#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "DrawingInstruction.h"
#include "cLista.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class schizzoApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	CLista instructions;
    int el0;
    Vec2f pen;
};

void schizzoApp::setup()
{
  gl::translate( Vec2f( -getWindowWidth()/2, -getWindowHeight()/2 ) );

  gl::enableAlphaBlending();
  gl::clear( Color( 1.0, 1.0, 1.0) );
  glEnable(GL_LINE_SMOOTH);

  gl::color( ColorA( 0.0f, 0.0f, 0.0f, 0.7f ) ); 
  glLineWidth( 0.5 * 3 );
  gl::drawLine( Vec2f(0, 0), Vec2f(getWindowWidth(), getWindowHeight()) );

  el0 = 0;

  for(int i=0; i<100; i++) {
    di_t di = DIMakef(1, Rand::randFloat(getWindowWidth()), 
                         Rand::randFloat(getWindowHeight())); 
    instructions.add(di); 
  }
}

void schizzoApp::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
  // printf("%d\n", instructions.size());
  if(el0 < instructions.size()) {
    //printf("%d/%d\n", el0, instructions.size());
    pen = instructions.draw(pen, el0);
    el0++;
  }
}

void schizzoApp::mouseDown( MouseEvent event )
{
}

void schizzoApp::update()
{
}


CINDER_APP_BASIC( schizzoApp, RendererGl )
