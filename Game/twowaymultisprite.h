#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "multisprite.h"

class TwoWayMultiSprite : public MultiSprite {
public:
  TwoWayMultiSprite(const std::string&);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  virtual ~TwoWayMultiSprite() { } 
  virtual void advanceFrame(Uint32 ticks);
  virtual void update(Uint32 ticks);
  virtual std::string getType() const { return "TwoWayMultiSprite"; }

private:
  bool flip;
  int frameCounter;
};
#endif
