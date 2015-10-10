#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "frame.h"
 
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, int rotSpeed, bool r): 
    name(n), position(pos), velocity(vel),rotationSpeed(rotSpeed) ,rotate(r) {}

  Drawable(const Drawable& s) : 
    name(s.name), position(s.position), velocity(s.velocity),rotationSpeed(s.rotationSpeed),rotate(s.rotate)
    { }

  virtual ~Drawable() {}

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }
  virtual const Frame* getFrame() const = 0;

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;
  virtual std::string getType() const = 0; // added to detect the polymorphic type of the derived classes used in collision detection in managler.cpp
  float X() const { return position[0]; }
  void X(float x) { position[0] = x;    }

  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y;    }

  float velocityX() const  { return velocity[0]; }
  void velocityX(float vx) { velocity[0] = vx;   }
  float velocityY() const  { return velocity[1]; }
  void velocityY(float vy) { velocity[1] = vy;   }

  const Vector2f& getVelocity() const   { return velocity; }
  void setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const   { return position; }
  void setPosition(const Vector2f& pos) { position = pos;  }

// New Function added to incorporate rotation and collision detection features in sprites
  
  int getRotationSpeed() const{ return rotationSpeed; } 
  void setRotationSpeed(int r) { rotationSpeed = r; }
  void toggleRotation(){ rotate = !rotate; }
  bool getRotate() const { return rotate; } 
  //virtual void updateVelocitiesAfterCollision() = 0; 
  //virtual int calculateDistance(Drawable *s) = 0;

//

  virtual bool collidedWith(const Drawable*) const { 
    throw std::string("No collidedWith");  
  }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  int rotationSpeed;
  bool rotate;
};
#endif
