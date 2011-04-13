#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class simpleTreeApp : public AppBasic {
  public:
    void setup();
    void branche(float x, float y, float s, float a);
    void mouseDown( MouseEvent event );
    void update();
    void draw();
    void prepamResettings( Settings *settings );

    int mReset;
    Vec2f nextTarget;
};

void simpleTreeApp::prepamResettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
	settings->setFrameRate( 60.0f );
}

void simpleTreeApp::setup()
{
  Rand::randomize();
  gl::enableAlphaBlending();
  gl::clear( Color( 0.898f, 0.831f, 0.604f ) );
  mReset = 0;
}

void simpleTreeApp::branche(float x, float y, float s, float a) 
{
  gl::color( Color( 0.1f, 0.1f, 0.1f ) );
  glLineWidth( s*0.05 );
  a += toRadians( Rand::randFloat( -7, 7 ) );
  float newx = x+cos(a)*s;
  float newy = y+sin(a)*s;
  gl::drawLine( Vec2f(x, y), Vec2f(newx, newy) );
  nextTarget = Vec2f( getWindowWidth()/2, getWindowHeight()/3 );

  // printf("(s:%f a:%f) %f,%f -> %f,%f\n", s, a, x, y, newx, newy);
  if(s > 3) {
    branche(newx, newy, s*Rand::randFloat(0.5, 0.7), a-toRadians(Rand::randFloat(12, 17)));
    branche(newx, newy, s*Rand::randFloat(0.5, 0.7), a+toRadians(Rand::randFloat(12, 17)));
  }
}

void simpleTreeApp::mouseDown( MouseEvent event )
{
  mReset = 0;
  nextTarget = Vec2f(event.getPos().x, getWindowHeight() - event.getPos().y);
}

void simpleTreeApp::update()
{
}

void simpleTreeApp::draw()
{
  gl::color( ColorA( 0.898f, 0.831f, 0.604f, 0.01f ) ); 
  gl::drawSolidRect( getWindowBounds() );

  if(mReset == 0) {
    branche( nextTarget.x, getWindowHeight(), 
        nextTarget.y, toRadians( 270.0 ) );
    mReset = 1;
  }
}

CINDER_APP_BASIC( simpleTreeApp, RendererGl )
