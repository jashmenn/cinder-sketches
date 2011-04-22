#include "cLista.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

cLista::cLista()
{
}

cLista::cLista( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= Rand::randFloat( 5.0f );
	mRadius	= 3.0f;
}

void cLista::update()
{
	mLoc += mDir * mVel;
}

void cLista::draw()
{
	gl::drawSolidCircle( mLoc, mRadius );
}
