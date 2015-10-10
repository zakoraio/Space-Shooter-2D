#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "twowaymultisprite.h"


void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
          frameCounter = (frameCounter + 1) % (numberOfFrames/2);
          currentFrame = frameCounter;
          if(flip){
              currentFrame = frameCounter + (numberOfFrames/2);
          }
	  timeSinceLastFrame = 0;
	 }
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  MultiSprite(name),
  flip(false),
  frameCounter(0)
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :

  MultiSprite(s), 
  flip( s.flip ),
  frameCounter(s.frameCounter)
  { }



void TwoWayMultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if(getRotate())  
   angle += getRotationSpeed() % 360;

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
    flip = false;
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
    flip = true;
    frameCounter = 0;
  }  

}
