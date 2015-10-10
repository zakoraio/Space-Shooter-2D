#ifndef BULLET__H
#define BULLET__H
#include <string>
#include "drawable.h"

class Bullet : public Drawable {
public:
  Bullet(const std::string&,int,float);
  Bullet(const std::string&, const Vector2f& pos, const Vector2f& vel);
  Bullet(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Bullet(const Bullet& s);
  virtual ~Bullet() {} 
  Bullet& operator=(const Bullet&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual std::string getType()const { return "Bullet"; }
  virtual void update(Uint32 ticks);
  virtual int calculateDistance(Drawable *s);
  virtual void updateVelocitiesAfterCollision(); 
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }
  float getScale() const { return scale; }
  void setOrientation(int x,int y,float playerX ,float playerY,int angle);
private:
  const Frame * frame;
  //const Frame * midFrame;
  //const Frame * smallFrame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int angle;
  int scale;
  int orientationX;
  int orientationY;

};
#endif
