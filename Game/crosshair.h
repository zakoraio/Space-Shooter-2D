#ifndef CROSSHAIR__H
#define CROSSHAIR__H
#include <string>
#include "drawable.h"

class CrossHair : public Drawable {
public:
  CrossHair(const std::string&,int,float);
  CrossHair(const std::string&, const Vector2f& pos, const Vector2f& vel);
  CrossHair(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  CrossHair(const CrossHair& s);
  virtual ~CrossHair() {} 
  CrossHair& operator=(const CrossHair&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual std::string getType()const { return "CrossHair"; }
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
