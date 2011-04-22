#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "DrawingInstruction.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class schizzoApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void schizzoApp::setup()
{
  gl::enableAlphaBlending();
  gl::clear( Color( 1.0, 1.0, 1.0) );
  glEnable(GL_LINE_SMOOTH);

  gl::color( ColorA( 0.0f, 0.0f, 0.0f, 0.7f ) ); 
  glLineWidth( 0.5 * 3 );
  gl::drawLine( Vec2f(0, 0), Vec2f(getWindowWidth(), getWindowHeight()) );
 
}

void schizzoApp::mouseDown( MouseEvent event )
{
}

void schizzoApp::update()
{
}

void schizzoApp::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
}


CINDER_APP_BASIC( schizzoApp, RendererGl )
