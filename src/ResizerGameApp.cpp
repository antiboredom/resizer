#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ResizerGameApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void ResizerGameApp::setup()
{
}

void ResizerGameApp::mouseDown( MouseEvent event )
{
}

void ResizerGameApp::update()
{
}

void ResizerGameApp::draw()
{
	// clear out the window with black
	gl::clear( Color( .1, .1, .1 ) );
  gl::enableAlphaBlending();
  
  float tSecs = getElapsedSeconds();
  int tFrames = getElapsedFrames();
  int tWinW = getWindowWidth();
  int tWinH = getWindowHeight();
  
  int tMaxEnemies = 30;
  float tClosest = 1000;
  float tEnemySpeed = constrain(float(tFrames) / 1000.0 + 1.0, 1.0, 8.0);
  float tEnemyCurve = abs(sin(tFrames * .001)) * 270;
  float tEnemyDistance = 70;
  tEnemyDistance -= constrain(tFrames * .01, 20.0, 70.0);
  
  float tEnemyCurve2 = abs(cos(tFrames * .001)) * 270;
  float tEnemyDistance2 = 90;
  tEnemyDistance2 -= constrain(tFrames * .01, 15.0, 90.0);
  
  int tPlayerY = constrain(tWinW - 300, 0, tWinH);
  int tPlayerX = 70;
  Vec2f player = Vec2f(tPlayerX, tPlayerY);
  float health = 10;
  
  //  draw the score
	Vec2f tSize = Vec2f( tWinW, 100 );
	Font tFont = Font( "Arial", 12 );
  string txt = "Score: " + std::to_string(tFrames);
	TextBox tbox = TextBox().alignment( TextBox::RIGHT ).font( tFont ).size( Vec2i( tSize.x, TextBox::GROW ) ).text( txt );
  gl::color( .8, .8, .8 );
  gl::Texture tTextTexture = gl::Texture( tbox.render() );
  if( tTextTexture ) gl::draw( tTextTexture );
  cout << "Score: " << tFrames << "\n";
  
  
  
  //  draw enemies
  gl::color(.8, .1, .1);
  
  for (int i = 0; i < tMaxEnemies; ++i){
    float tX = ( 600 - ( tFrames % 600 ) * tEnemySpeed ) - ( sin(i * .5) * tEnemyCurve ) + 300;
    float tY = sin( tSecs ) * 20 + i * tEnemyDistance;
    float tX2 = tX - 50;
    float tY2 = sin( tSecs + .5) * 20 + i * tEnemyDistance;
    
    gl::drawVector( Vec3f(tX, tY, 0), Vec3f(tX2, tY2, 0), 10, 5 );
    
    float tDist = min( player.distance( Vec2f(tX2, tY2)), player.distance( Vec2f(tX, tY) ) );
    if ( tDist < tClosest ) tClosest = tDist;
  }
  
  // wave2
  if (tFrames > 2000) {
    for (int i = 0; i < tMaxEnemies; ++i){
      float tX = ( 700 - ( tFrames % 700 ) * tEnemySpeed ) - ( sin(i * .5) * tEnemyCurve2 ) + 300;
      float tY = cos( tSecs ) * 20 + i * tEnemyDistance2;
      float tX2 = tX - 50;
      float tY2 = cos( tSecs + .5) * 20 + i * tEnemyDistance2;
      tX += 300;
      tX2 += 300;
      
      gl::drawVector( Vec3f(tX, tY, 0), Vec3f(tX2, tY2, 0), 10, 5 );
      
      float tDist = min( player.distance( Vec2f(tX2, tY2)), player.distance( Vec2f(tX, tY) ) );
      if ( tDist < tClosest ) tClosest = tDist;
    }
  }
  
  // player color
  gl::color( .1, .8, .1 );
  
  //  animate player
  if (tFrames > 100) {
    health += sin(tSecs) * 3;
  }
  
  //  flash yellow if almost hit
  if ( tClosest < health + 5 ) {
    gl::color( 1, 1, 0 );
  }
  
  //  quit if hit
  if ( tClosest <= health) {
    quit();
  }
  
  //  draw the player
  gl::drawSolidCircle(player, health);
  
  
}

//void ResizerGameApp::draw()
//{
//  gl::enableAlphaBlending();
//  
//	// clear out the window with black
//	gl::clear( Color( 0, 0, 0 ) );
//  
//  float tSecs = getElapsedSeconds();
//  
//  if (getElapsedFrames() % 500 < 250) {
//    int tWinW = getWindowWidth();
//    int tWinH = getWindowHeight();
//    int tMaxBalls = 70;
//    
//    for (int i = 0; i < tMaxBalls; ++i) {
//      
//      float tX = sin( tSecs - i * sin(getElapsedSeconds() * .1)) * (tWinW/2 - 40) + tWinW/2;
//      float tY = cos( tSecs - i * .1) * (tWinH/2 - 40) + tWinH/2;
//      float tX2 = sin( tSecs + i * sin(getElapsedSeconds() * .1)) * (tWinW/2 - 40) + tWinW/2;
//      float tY2 = cos( tSecs + i * .1) * (tWinH/2 - 40) + tWinH/2;
//      
//      float tR = i * .2;
//      gl::color(1, 1, 1, .5);
//      gl::drawVector(Vec3f(tX2, tY2, 0), Vec3f(tX, tY, 0), 0, 0);
//      gl::color(1, 1, 1, 1);
//      gl::drawSolidCircle( Vec2f( tX, tY ), tR );
//      gl::drawSolidCircle( Vec2f( tX2, tY2 ), tR );
//    }
//  } else {
//  
//    int tGridSize = getWindowWidth() / 50;
//    int tDivisions = getWindowWidth() / 5;
//    
//    for ( int x = 0; x < getWindowWidth(); x += tGridSize ) {
//      for ( int y = 0; y < getWindowWidth(); y += tGridSize ) {
//        float tRadius = sin( tSecs + y/tDivisions + x/tDivisions ) * tGridSize + tGridSize + randFloat(-1, 1);
//        tRadius = tRadius / 3;
//        gl::drawSolidCircle( Vec2f( x, y ), tRadius);
//      }
//    }
//  }
//
//  
//}

CINDER_APP_NATIVE( ResizerGameApp, RendererGl )
