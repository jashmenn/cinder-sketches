#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class recursiveTreeApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void branch( int depth, float width );

    int mReset;
};

void recursiveTreeApp::setup()
{
  Rand::randomize();
  gl::enableAlphaBlending();
  gl::clear( Color( 0.898f, 0.831f, 0.604f ) );
  glEnable(GL_LINE_SMOOTH);
  mReset = 0;
}

void recursiveTreeApp::mouseDown( MouseEvent event )
{
  printf("mouseDown\n");
  mReset = 0;
//  nextTarget = Vec2f(event.getPos().x, getWindowHeight() - event.getPos().y);

}

void recursiveTreeApp::update()
{
}

void recursiveTreeApp::draw()
{
  gl::color( ColorA( 0.898f, 0.831f, 0.604f, 0.01f ) ); 
  gl::drawSolidRect( getWindowBounds() );

  if(mReset == 0) {
    gl::pushMatrices();
    gl::translate( Vec2f( getWindowWidth()/2, getWindowHeight() ) );
    // gl::clear( Color( 0.898f, 0.831f, 0.604f ) );
    branch(0, 20.0);
    gl::popMatrices();
    mReset = 1;
  }
}

void recursiveTreeApp::branch(int depth, float width) 
{
  gl::color( Color( 0.1f, 0.1f, 0.1f ) );
  glLineWidth( width );
  printf("depth: %d width:%f\n", depth, width);

  if (depth < 10) {
    gl::drawLine( Vec2f(0, 0), Vec2f(0, -getWindowHeight()/3) );

    gl::pushMatrices();
    {
      gl::translate(Vec2f(0, -getWindowHeight()/5));
      gl::rotate(Rand::randFloat(-45.0, 45.0)); 
      gl::scale(Vec3f( 0.7f, 0.7f, 0.7f ));
      branch(depth + 1, width * 0.7);
    }
    gl::popMatrices();

    gl::pushMatrices();
    {
      gl::translate(Vec2f(0, -getWindowHeight()/3));
      gl::rotate(Rand::randFloat(-45.0, 45.0)); 
      gl::scale(Vec3f( 0.7f, 0.7f, 0.7f ));
      branch(depth + 1, width * 0.7);
    }
    gl::popMatrices();

  }
}

CINDER_APP_BASIC( recursiveTreeApp, RendererGl )


// A simple recursive tree
// (c) Alasdair Turner 2007
/* 

void setup()
{
  size(400,400);
  smooth();
  noLoop();
}
 
void draw()
{
  background(204);  
  strokeWeight(10);
  translate(width/2,height);
  branch(0);
}
 
void branch(int depth)
{
    if (depth < 10) {
      line(0,0,0,-height/3);
      pushMatrix();
      {
        translate(0,-height/5);
        rotate(random(-PI/4,PI/4));
        scale(0.7);
        branch(depth + 1);
      }
      popMatrix();
      pushMatrix();
      {
        translate(0,-height/3);
        rotate(random(-PI/4,PI/4));
        scale(0.7);
        branch(depth + 1);
      }
      popMatrix();
    }
}
 
void mouseClicked()
{
  redraw();
}

*/
