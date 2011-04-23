#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "DrawingInstruction.h"
#include "cLista.h"
#include "cinder/Rand.h"

#define DE 3
using namespace ci;
using namespace ci::app;
using namespace std;

class schizzoApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void city();

	CLista instructions;
    int el0;
    Vec2f pen;
    bool hasSetup;

  protected:
     void retth(int sx, int sy, int ex, int ey);
     void rettv(int sx, int sy, int ex, int ey);

};

void schizzoApp::prepareSettings( Settings *settings )
{
  settings->setWindowSize( 800, 400 );
  // settings->setFrameRate(setFrameRate 60.0f );
  // settings->setFullScreen( false );
}

void schizzoApp::setup()
{
  gl::enableAlphaBlending();
  gl::clear( Color( 1.0, 1.0, 1.0) );
  glEnable(GL_LINE_SMOOTH);

  gl::color( ColorA( 0.0f, 0.0f, 0.0f, 0.7f ) ); 
  glLineWidth( 0.4 * 3 );

  el0 = 0;
  pen = Vec2f( 0, 0 );
  hasSetup = false;
}

void schizzoApp::draw()
{
  int t=0;
  int atATime = 3; // how many to draw per draw() (def 5)
  while((t++ < atATime) && (el0 < instructions.size())) {
    pen = instructions.draw(pen, el0);
    el0++;
  }
}

void schizzoApp::mouseDown( MouseEvent event )
{
}

void schizzoApp::update()
{
  if(!hasSetup) {
    // gl::translate( Vec2f(0, getWindowHeight()) );
    // gl::drawLine( Vec2f(0, 0), Vec2f(getWindowWidth(), getWindowHeight()) );
    // gl::drawLine( Vec2f(0, getWindowHeight() - 50), 
    //               Vec2f(getWindowWidth(), getWindowHeight() - 50) );
    hasSetup = true;
    city();
  }


}

void schizzoApp::city() 
{
  int by = getWindowHeight() - 50;
  retth(0, by, getWindowWidth(), getWindowHeight());
  rettv(0, by, getWindowWidth(), getWindowHeight());
}

// ------------------------------------------------------------
// Filled rectangle with vertical lines // rettangolo pieno a righe verticali
void schizzoApp::rettv(int sx, int sy, int ex, int ey) {
  instructions.add(DI_MOVE_TO, sx, sy);
  for (int i=sx; i<ex; i+=DE) {
    instructions.add(DI_LINE_TO, i, sy);
    instructions.add(DI_LINE_TO, i, ey);
  }
}

// ------------------------------------------------------------
// Rectangle filled with horizontal stripes // rettangolo pieno a righe orizzontali
void schizzoApp::retth(int sx, int sy, int ex, int ey) {
  instructions.add(DI_MOVE_TO, sx, sy);
  for (int i=sy; i<ey; i+=DE) {
    instructions.add(DI_LINE_TO, sx, i);
    instructions.add(DI_LINE_TO, ex, i);
  }
}

CINDER_APP_BASIC( schizzoApp, RendererGl )
