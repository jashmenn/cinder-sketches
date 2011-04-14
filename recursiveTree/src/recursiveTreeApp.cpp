#include "cinder/Cinder.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/params/Params.h"



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
    // keep track of time
    double        mTime;
	double        mLastDraw;
	params::InterfaceGl		mParams;

    float mStartingWidth;
    int mMaxDepth;
    int mSegmentLengthMin;
    int mSegmentLengthMax;
    float mBranchRotationMin;
    float mBranchRotationMax;
    float mProbBranch;
    float mScaleReduction;
    float mBranchRotationMin2;
    float mBranchRotationMax2;
};

void recursiveTreeApp::setup()
{
  Rand::randomize();
  gl::enableAlphaBlending();
  gl::clear( Color( 1.0, 1.0, 1.0) );
  glEnable(GL_LINE_SMOOTH);
  mReset = 0;
  mTime = getElapsedSeconds();
  mLastDraw = mTime;

  mStartingWidth = 11.0;
  mMaxDepth = 12;
  mSegmentLengthMin = 4;
  mSegmentLengthMax = 14;
  mBranchRotationMin = -13.0f;
  mBranchRotationMax = 11.0f;
  mProbBranch = 0.7f;
  mScaleReduction = 0.7f;
  mBranchRotationMin2 = 10.0f;
  mBranchRotationMax2 = 20.0f;

  // Setup the parameters
  mParams = params::InterfaceGl( "Parameters", Vec2i( 200, 400 ) );
  mParams.addParam( "Starting Width", &mStartingWidth, "min=1 max=20 step=1" );
  mParams.addParam( "Max Depth", &mMaxDepth, "min=1 max=20 step=1" );
  mParams.addParam( "Seg Length (min)", &mSegmentLengthMin, "min=1 max=30 step=1" );
  mParams.addParam( "Seg Length (max)", &mSegmentLengthMax, "min=1 max=30 step=1" );
  mParams.addParam( "Branch Rotation (min)", &mBranchRotationMin, "min=-360 max=360 step=1" );
  mParams.addParam( "Branch Rotation (max)", &mBranchRotationMax, "min=-360 max=360 step=1" );
  mParams.addParam( "Prob Branch", &mProbBranch, "min=0.0 max=1.0 step=0.05" );
  mParams.addParam( "Scale Reduction", &mScaleReduction, "min=0.0 max=1.0 step=0.05" );
  mParams.addParam( "Branch Rotation 2 (min)", &mBranchRotationMin2, "min=-360 max=360 step=1" );
  mParams.addParam( "Branch Rotation 2 (max)", &mBranchRotationMax2, "min=-360 max=360 step=1" );
}

void recursiveTreeApp::mouseDown( MouseEvent event )
{
  printf("mouseDown\n");
  mReset = 0;
}

void recursiveTreeApp::update()
{
  // calculate elapsed time
  //double elapsed = getElapsedSeconds() - mTime;
  mTime = getElapsedSeconds();
  // printf("elapsed: %f (%f)\n", mTime, round(mTime));
  int t = 3;
  if(((((int)round(mTime)) % t) == 0) && 
      (mTime - mLastDraw > t)) {
     mReset = 0;
     mLastDraw = mTime;
  }
}

void recursiveTreeApp::draw()
{
  if(mReset == 0) {
    gl::color( ColorA( 1.0f, 1.0f, 1.0f, 0.5f ) ); 
    gl::drawSolidRect( getWindowBounds() );

    gl::pushMatrices();
    gl::translate( Vec2f( Rand::randFloat(getWindowWidth()), getWindowHeight() ) );
    gl::rotate(Rand::randFloat(-3, 3)); 
    float newScale = Rand::randFloat(0.5,1);
    gl::scale(Vec3f( newScale, newScale, newScale ));
    branch(0, mStartingWidth);
    gl::popMatrices();
    mReset = 1;
  }

  // params::InterfaceGl::draw();
}

void recursiveTreeApp::branch(int depth, float width) 
{
  if (depth < mMaxDepth) {

    if(depth < 4) {
       gl::color( ColorA( 0.1f, 0.1f, 0.1f, 1.0f ) ); 
    } else if (depth < 7) {
       gl::color( ColorA( 0.1f, 0.1f, 0.1f, 0.8f ) ); 
    } else if (depth < 9) {
       gl::color( ColorA( 0.1f, 0.1f, 0.1f, 0.7f ) ); 
    } else {
       gl::color( ColorA( 0.1f, 0.1f, 0.1f, 0.5f ) ); 
    }
    glLineWidth( width );

    float segmentLength = Rand::randFloat(mSegmentLengthMin, mSegmentLengthMax);
    gl::drawLine( Vec2f(0, 0), Vec2f(0, -getWindowHeight()/segmentLength) );
    gl::translate(Vec2f(0, -getWindowHeight()/segmentLength));
    gl::rotate(Rand::randFloat(mBranchRotationMin, mBranchRotationMax)); 

    if (Rand::randFloat(1.0) < mProbBranch) { // branching
      gl::pushMatrices();
      gl::rotate(Rand::randFloat(mBranchRotationMin2, mBranchRotationMax2)); 
      gl::scale(Vec3f( mScaleReduction, mScaleReduction, mScaleReduction ));
      branch(depth + 1, width*mScaleReduction) ;
      gl::popMatrices();

      gl::pushMatrices();
      gl::rotate(-1*Rand::randFloat(mBranchRotationMin2, mBranchRotationMax2)); 
      gl::scale(Vec3f( mScaleReduction, mScaleReduction, mScaleReduction ));
      branch(depth + 1, width*mScaleReduction) ;
      gl::popMatrices();
    } else { // continue
      branch(depth, width);
    }

  }
}

CINDER_APP_BASIC( recursiveTreeApp, RendererGl )


