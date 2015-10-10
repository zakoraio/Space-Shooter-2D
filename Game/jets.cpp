#include <cmath>
#include "jets.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "bullet.h"
int getRandomFactor2(int max){
        int number = Gamedata::getInstance().getRandInRange(200,max);
        return number;
}

int getRandomFactorBetween(int min,int max){
        int number = Gamedata::getInstance().getRandInRange(min,max);;
        number *= rand() % 2 ?  -1 : 1;
        return number;
}


Jets::Jets(const std::string& name,int len, float s) :
  Drawable(name.substr(0,len),
           Vector2f(Gamedata::getInstance().getXmlInt("jets/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt("jets/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name.substr(0,len)+"/speedX")*s, 
                    Gamedata::getInstance().getXmlInt(name.substr(0,len)+"/speedY")*s),
           Gamedata::getInstance().getXmlInt(name.substr(0,len)+"/rotationSpeed"), 
           false),
  frame( FrameFactory::getInstance().getScaledFrame(name,len,s) ),
  frameWidth(frame->getWidth()*s),
  frameHeight(frame->getHeight()*s),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(s),
  strategy(new RectangularCollisionStrategy()), 
  playerX(0.0),
  playerY(0.0),
  throttleX(300),
  throttleY(throttleX) 
{ 
}

Jets::Jets(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt(n+"/rotationSpeed"),false), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0),
  strategy(new RectangularCollisionStrategy()),
  playerX(0.0),
  playerY(0.0),
  throttleX(300),
  throttleY(throttleX) 
{ }

Jets::Jets(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt("defaultRotationSpeed"),false), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0),
  strategy(new RectangularCollisionStrategy()),
  playerX(0.0),
  playerY(0.0),
  throttleX(300),
  throttleY(throttleX)
{ }

Jets::Jets(const Jets& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(s.scale),
  strategy(s.strategy),
  playerX(s.playerX),
  playerY(s.playerY),
  throttleX(s.throttleX), 
  throttleY(s.throttleY)
{ }

Jets& Jets::operator=(const Jets& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}



void Jets::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
   frame->draw(x,y,angle);
}

bool Jets::collidedWith(const Drawable * d) const {
	return strategy->execute((*this),*d);
}

int Jets::calculateDistance(Drawable *obj) { 
  float x,y,x1,y1;
  x = X() + frameWidth/2;
  y = Y() + frameHeight/2;
  Jets * sprite = dynamic_cast<Jets *> (obj);
  if(sprite==NULL){
  Bullet * sprite = dynamic_cast<Bullet *> (obj);
  x1 = sprite->X()+sprite->getFrameWidth()/2;
  y1 = sprite->Y()+sprite->getFrameHeight()/2;
  return hypot(x-x1, y-y1);
  }
  else{
  x1 = sprite->X()+sprite->getFrameWidth()/2;
  y1 = sprite->Y()+sprite->getFrameHeight()/2;
  return hypot(x-x1, y-y1);
  }

}

void Jets::updateVelocitiesAfterCollision() {
    velocityY( - velocityY() ) ; 
    velocityX( -velocityX() ) ;
}

void Jets::update(Uint32 ticks) { 

  int deviation = getRandomFactorBetween(0,200);
  int length = sqrt((playerX+deviation - X())*(playerX+deviation-X()) + (playerY+deviation-Y())*(playerY+deviation-Y()));
  velocityX(throttleX*(playerX - X())/length);
  velocityY(throttleY*(playerY - Y())/length);
   int delta_x = playerX - X();
   int delta_y = playerY - Y();
   angle = -(atan2(delta_y, delta_x)*180.0000)/3.142 ;
  
   Vector2f incr = getVelocity() *  static_cast<float>(ticks) * 0.001;
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
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
