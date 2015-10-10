#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <SDL_rotozoom.h>
#include "crosshair.h"



CrossHair::CrossHair(const std::string& name,int len, float s) :
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
  scale(s) 
{ 
}

CrossHair::CrossHair(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt(n+"/rotationSpeed"),false), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0)
{ }

CrossHair::CrossHair(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel,Gamedata::getInstance().getXmlInt("defaultRotationSpeed"),false), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(1.0)
{ }

CrossHair::CrossHair(const CrossHair& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(0),
  scale(s.scale)
{ }

CrossHair& CrossHair::operator=(const CrossHair& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void CrossHair::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
   frame->draw(x,y,angle);
}

int CrossHair::calculateDistance(Drawable *obj) { 
  float x,y,x1,y1;
  x = X() + frameWidth/2;
  y = Y() + frameHeight/2;
  CrossHair * sprite = dynamic_cast<CrossHair *> (obj);
  x1 = sprite->X()+sprite->getFrameWidth()/2;
  y1 = sprite->Y()+sprite->getFrameHeight()/2;
  return hypot(x-x1, y-y1);
}


void CrossHair::updateVelocitiesAfterCollision() {
    velocityY( - velocityY() ) ; 
    velocityX( -velocityX() ) ;
}

void CrossHair::update(Uint32 ticks) { 
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
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
