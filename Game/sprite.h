#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&,int,float);
  Sprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  Sprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Sprite(const Sprite& s);
  virtual ~Sprite() {} 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual std::string getType()const { return "Sprite"; }
  virtual void update(Uint32 ticks);
  virtual int calculateDistance(Drawable *s);
  virtual void updateVelocitiesAfterCollision(); 
  int getFrameWidth() const { return frameWidth; }
  int getFrameHeight() const { return frameHeight; }
  float getScale() const { return scale; }
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
};
#endif
