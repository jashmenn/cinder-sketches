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
     void rettf(int sx, int sy, int ex, int ey);
     void building(int sx, int sy, int ex, int ey);
     void rett(int sx, int sy, int ex, int ey);
     void dlinea(int sx, int sy, int ex, int ey);
     void linea(int sx, int sy, int ex, int ey);
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
  hasSetup = false;
}

void schizzoApp::update()
{
  if(!hasSetup) {
    gl::clear( Color( 1.0, 1.0, 1.0) );
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
  // retth(0, by, getWindowWidth(), getWindowHeight());
  // rettf(0, by, getWindowWidth(), getWindowHeight());

  // Technical areas 
  int px0 = 0;
  while (px0 < 0.95*getWindowWidth()) {
    int dey = int(Rand::randInt(80, 300));
    int dex = int(Rand::randInt(15000, 30000) / (80 + dey));
    if (px0 + dex > 0.95*getWindowWidth()) dex = getWindowWidth() - px0;
    building(px0, by - dey, px0 + dex, by);
    px0 = px0 + dex + int(Rand::randInt(-5, 20));
  }
}

void schizzoApp::building(int sx, int sy, int ex, int ey) {
  int dex = ex - sx;
  int dey = ey - sy;
   
  // Technical areas // vani tecnici
  int h [2];
  h[0] = int(Rand::randInt(5, 20));
  h[1] = int(Rand::randInt(5, 20));
  sy = sy + fmax(h[0], h[1]);
  for (int i=0; i<2; i++) {
    if (Rand::randInt(4) > 1) {
      int dex1 = int(Rand::randInt(10, dex-10));
      int dex2 = int(Rand::randInt(10, dex-10));
      instructions.add(0, sx + dex1, sy - h[i]);
      instructions.add(2, ex - dex2, sy);
      printf("rett %d %d %d %d\n", sx + dex1, sy - h[i], ex - dex2, sy);
      rett(sx + dex1, sy - h[i], ex - dex2, sy);
    }
  }
   
  // antenne
  if ((Rand::randInt(4) > 0) && (dey > 200)) {
    for(int i=0; i<2; i++) {
      int px = sx + int(Rand::randInt(10, dex - 10));
      dlinea(px, sy - int(Rand::randInt(10, 50)), px, sy);
    }
  }
   
  // end // fondo
  instructions.add(0, sx, sy);
  instructions.add(2, ex, ey);
   
  // Shadow on the right // ombra a dx
  if (Rand::randInt(4) > 1) {
    int om = int(Rand::randInt(10, 30));
    dlinea(ex, sy, ex, ey);
    rettf(ex-om, sy, ex, ey);
    ex = ex - om;
  }
   
  rett(sx, sy, ex, ey);
   
  /*
  if ((Rand::randInt(1.5) > 1) && (dex > 80)) {
    if (Rand::randInt(2) > 1) { // dome // cupola
      int ox = 10;
      int cx = (sx + ex) / 2;
      int cy = sy + (cx - sx - ox);
      float rad = (cx - sx - ox) * 1.414;
      for (float beta=0; beta<=PI/2.0; beta+=PI/16.0) {
        instructions.add(0, sx + ox, sy);
        for (float alfa=PI/4.0; alfa<=PI*3.0/4.0; alfa+=PI/16.0) {
          instructions.add(1, cx - int(rad * cos(alfa) * cos(beta)), cy - int(rad * sin(alfa)));
        } 
      }
      for (float alfa=PI/4.0; alfa<PI/2.0; alfa+=PI/32.0) {
        linea(cx - int(rad * cos(alfa)), cy - int(rad * sin(alfa)), cx + int(rad * cos(alfa)), cy - int(rad * sin(alfa)));
      } 
    }
    else { // pyramid // piramide
      int cdex = (ex - sx) / 2;
      int cdey = cdex / 2;
      linea(sx, sy, sx + cdex, sy - cdey);
      linea(sx + cdex, sy - cdey, ex, sy);
      for (int i=10; i<cdex; i+=10) {
        linea(sx + i, sy - i / 2, ex - i, sy - i / 2);
        linea(sx + i * 2, sy, sx + cdex + i, sy - cdey + i / 2);
        linea(ex - i * 2, sy, sx + cdex - i, sy - cdey + i / 2);
      }     
    }
  }
  */
 
  // Base // basamento
  int ba = 0;
  if (Rand::randInt(4) > 1) {
    ba = int(Rand::randInt(10, 20));
    dlinea(sx, ey-ba, ex, ey-ba);
    rettf(sx, ey-ba, ex, ey);
  } 
 
  // Back // spalle
  if (Rand::randInt(4) > 1) {
    int sp = 10;
    sx = sx + sp;
    ex = ex - sp;
    dlinea(sx, sy, sx, ey);   
    dlinea(ex, sy, ex, ey);   
  }
 
  // architrave
  if (Rand::randInt(4) > 1) {
    sy = sy + int(Rand::randInt(10, 20));
    dlinea(sx, sy, ex, sy);   
  }
 
  // Vertical strip // fascia verticale
  if (Rand::randInt(10) > 7) {
    int hf = 20;
    int p = (sx + ex) / 2;
    rettv(p-hf, sy, p+hf, ey);
  }
 
  // White base // basamento bianco
  if (Rand::randInt(4) > 1) {
    ey = ey - ba - int(Rand::randInt(10, 20));
    dlinea(sx, ey, ex, ey);   
  }

  // Horizontal band // fascia orizzontale
  if (Rand::randInt(10) > 6) {
    int hf = 8;
    int p = (sy + ey) / 2;
    retth(sx, p-hf, ex, p+hf);
  }
   
  // Vertical lines // righe verticali
  if (Rand::randInt(4) > 1) {
    int sp = 10;
    dex = ex - sx;
    int nr = dex / sp;
    int ox = (dex - nr * sp) / 2;
    for (int i=0; i<nr; i++) {
      int j = sx + ox + i * sp;
      linea(j, sy, j, ey);
    }
  }
   
  // Horizontal lines // righe orizzontali
  if (Rand::randInt(4) > 1) {
    int sp = 30;
    dey = ey - sy;
    int nr = dey / sp;
    int oy = (dey - nr * sp) / 2;
    for (int i=0; i<nr; i++) {
      int j = sy + oy + i * sp;
      dlinea(sx, j, ex, j);
    }
  }
 
}
 


// ------------------------------------------------------------
// Filled rectangle // rettangolo pieno
void schizzoApp::rettf(int sx, int sy, int ex, int ey) {
  int dex = ex - sx;
  int dey = ey - sy;
  instructions.add(DI_MOVE_TO, sx, sy);
  for (int i=0; i<fmin(dex, dey); i+=2*DE) {
    instructions.add(DI_LINE_TO, sx, sy + i);
    instructions.add(DI_LINE_TO, sx + i, sy);
  }
  if (dex > dey) {
    for (int i=0; i<dex-dey; i+=2*DE) {
      instructions.add(DI_LINE_TO, sx + i, ey);
      instructions.add(DI_LINE_TO, sx + dey + i, sy);
    }
  }
  else {
    for (int i=0; i<dey-dex; i+=2*DE) {
      instructions.add(DI_LINE_TO, sx, sy + dex + i);
      instructions.add(DI_LINE_TO, ex, sy + i);
    }
  }
  for (int i=fmin(dex, dey); i>=0; i-=2*DE) {
    instructions.add(DI_LINE_TO, ex - i, ey);
    instructions.add(DI_LINE_TO, ex, ey - i);
  }
}

// ------------------------------------------------------------
// Empty rectangle // rettangolo vuoto
void schizzoApp::rett(int sx, int sy, int ex, int ey) {
  dlinea(sx, sy, ex, sy);
  dlinea(sx, ey, ex, ey);
  dlinea(sx, sy, sx, ey);
  dlinea(ex, sy, ex, ey);
}

void schizzoApp::dlinea(int sx, int sy, int ex, int ey) {
  linea(sx, sy, ex, ey);
  linea(sx, sy, ex, ey);
}

void schizzoApp::linea(int sx, int sy, int ex, int ey) {
  instructions.add(0, sx + int(Rand::randInt(-DE, DE)), sy + int(Rand::randInt(-DE, DE)));
  instructions.add(1, ex + int(Rand::randInt(-DE, DE)), ey + int(Rand::randInt(-DE, DE)));
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
