#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include "health.h"
#include "jets.h"
class Player : public Drawable {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual ~Player() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks); 
  virtual void advanceFrame(Uint32 ticks);
  virtual std::string getType() const { return "Player"; }
  virtual int calculateDistance(Drawable *s); 
  virtual void updateVelocitiesAfterCollision() { } // not implemented for multisprite yet
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  int getAngle() const { return angle; }
  void setNewOrientation(int x, int y){
  if(abs(X()+frames[currentFrame]->getWidth()/2-x)>20)
  newOrientationX = x;
  if(abs(Y()+frames[currentFrame]->getHeight()/2-y)>20)
  newOrientationY = y;
  
  }
  void reset() { X(750);Y(430);health=100; score = 0;h.reset();}
  bool detectCollision(Jets * jet);
  void setKey(int c) { key = c;}
  void hit() { gotHit = true;}
  int getHealth() const { return health; }
  void incrementScore() { score+=50; }
  int getScore() const { return score ;} 
  void toggleGod() { god = !god; }
protected:
  const std::vector<Frame *> frames;
 
  int worldWidth;
  int worldHeight;
  int oldOrientationX;
  int oldOrientationY;
  
  int newOrientationX;
  int newOrientationY;
  int currentFrame;  
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  int angle;
  int key;
  Health h;
  int health;
  bool gotHit;
  int score;
  bool god;
};
#endif
