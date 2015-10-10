#include <cmath>
#include "bullet.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>


Bullet::Bullet(const std::string& name,int len, float s) :
  Drawable(name.substr(0,len),
           Vector2f(Gamedata::getInstance().getXmlInt(name.substr(0,len) +"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name.substr(0,len)+"/startLoc/y")), 
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
  orientationX(0),
  orientationY(0) 
{ 
}

Bullet::Bullet(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt(n+"/rotationSpeed"),false), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0),
  orientationX(0),
  orientationY(0) 
{ }

Bullet::Bullet(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt("defaultRotationSpeed"),false), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0),
  orientationX(0),
  orientationY(0) 

{ }

Bullet::Bullet(const Bullet& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(s.scale),
  orientationX(s.orientationX),
  orientationY(s.orientationY) 

{ }

Bullet& Bullet::operator=(const Bullet& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void Bullet::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
   frame->draw(x,y,angle);
}

int Bullet::calculateDistance(Drawable *obj) { 
  float x,y,x1,y1;
  x = X() + frameWidth/2;
  y = Y() + frameHeight/2;
  Bullet * sprite = dynamic_cast<Bullet *> (obj);
  x1 = sprite->X()+sprite->getFrameWidth()/2;
  y1 = sprite->Y()+sprite->getFrameHeight()/2;
  return hypot(x-x1, y-y1);
}


void Bullet::updateVelocitiesAfterCollision() {
    velocityY( - velocityY() ) ; 
    velocityX( -velocityX() ) ;
}



void Bullet::setOrientation(int x, int y,float playerX,float playerY,int a){
 int length = sqrt((x-playerX)*(x-playerX) + (y-playerY)*(y-playerY));
 velocityX((x-playerX)/length);
 velocityY((y-playerY)/length);
 angle = a+270;
 
 X(playerX+60/scale);
 Y(playerY+60/scale);
 }
void Bullet::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() *3000* static_cast<float>(ticks) * 0.001;

 setPosition(getPosition() + incr);
  
}
