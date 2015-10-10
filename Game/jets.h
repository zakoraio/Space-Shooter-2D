#ifndef JETS__H
#define JETS__H
#include <string>
#include "drawable.h"
#include "collisionStrategy.h"


class Jets : public Drawable {
public:
  Jets(const std::string&,int,float);
  Jets(const std::string&, const Vector2f& pos, const Vector2f& vel);
  Jets(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Jets(const Jets& s);
  virtual ~Jets() {} 
  Jets& operator=(const Jets&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual std::string getType()const { return "Sprite"; }
  virtual void update(Uint32 ticks);
  virtual int calculateDistance(Drawable *s);
  virtual void updateVelocitiesAfterCollision(); 
  bool collidsWith(Drawable * d);
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }
  float getScale() const { return scale; }
  virtual bool collidedWith(const Drawable*) const;
  void setPlayerCoordinates(float x ,float y) { playerX = x ; playerY = y; };
  void setXTh(int x) { throttleX = x; }
  void setYTh(int y) { throttleY = y; }

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int angle;
  int scale; 
  CollisionStrategy *strategy;
  float playerX;
  float playerY;
  int throttleX;
  int throttleY;
};
#endif
