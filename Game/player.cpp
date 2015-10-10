#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <cmath>
#include "player.h"
void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
	    currentFrame = (currentFrame + 1) % (numberOfFrames);
	    timeSinceLastFrame = 0;
	}
}

Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           Gamedata::getInstance().getXmlInt(name+"/rotationSpeed"),
           false   
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  oldOrientationX(0),
  oldOrientationY(0),
  newOrientationX(0),
  newOrientationY(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  angle(0),
  key( 0 ),
  h(),
  health(100),
  gotHit(false),
  score(0),
  god(false)
{ }

Player::Player(const Player& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ), 
  oldOrientationX(s.oldOrientationX),
  oldOrientationY(s.oldOrientationY),
  newOrientationX(s.newOrientationX),
  newOrientationY(s.newOrientationY),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  angle(0),
  key( 0 ),
  h(),
  health(100),
  gotHit(false),
  score(0),
  god(false)
  { }

void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(health>0)
  frames[currentFrame]->draw(x, y,angle);
  h.draw();
}



bool Player::detectCollision(Jets * jet){
  float x,y,x1,y1;
  x = X() + frames[currentFrame]->getWidth()/2;
  y = Y() + frames[currentFrame]->getHeight()/2;
  bool collision;

  collision = false;

  	x1 = jet->X()+jet->getFrameWidth()/2;
 	y1 = jet->Y()+jet->getFrameHeight()/2;
        if( hypot(x-x1, y-y1)<=100){
		collision = true;
                gotHit = true;
                if(!god)
		health-=10;
         }
	return collision;
}

int Player::calculateDistance(Drawable *obj) {
  return hypot(X()-obj->X(), Y()-obj->Y());
}


void Player::update(Uint32 ticks) {
  
  if(getRotate())  
   {
   int delta_x = newOrientationX - X();
   int delta_y = newOrientationY - Y();
   angle = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;
   }
  
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;

  setPosition(getPosition() + incr);
  if(gotHit && !god){
  h.update();
  gotHit = false;
  h.setScore(score);  
  }
  
  if(key==1) { velocityY(0.0);velocityX(-1000.0);}
  else if(key == 2) { velocityY(1000.0);velocityX(0.0); }
  else if(key == 3) { velocityY(0.0);velocityX(1000.0);}
  else if(key == 4) { velocityY(-1000.0);velocityX(0.0);}
  if(key == 5){ velocityY(1000.0);velocityX(-1000.0);}
  else if(key == 6){ velocityY(-1000.0);velocityX(-1000.0);}
  else if(key == 7){ velocityY(-1000.0);velocityX(1000.0);}
  else if(key == 8){ velocityY(1000.0);velocityX(1000.0);}
  else if(key == 0){velocityX(0.0);velocityY(0.0);}
  if(key != 0)
    if ( Y() < 0) { velocityY( abs( velocityY() ) );}
    if ( Y() > worldHeight-frameHeight) { velocityY( -abs( velocityY() ) ); }
    if ( X() < 0) {velocityX( abs( velocityX() ) );}
    if ( X() > worldWidth-frameWidth) {velocityX( -abs( velocityX() ) );}	
}
