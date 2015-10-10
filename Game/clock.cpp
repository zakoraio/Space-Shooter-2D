#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"


const int Clock::size = 1000;

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  frames(0),
  ticksSinceLastFrame(0),
  ticksAtLastFrame(0),
  sumOfTicks(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  fpsLoc(Gamedata::getInstance().getXmlInt("textCoordinates/fpsX"),
         Gamedata::getInstance().getXmlInt("textCoordinates/fpsY")),
  secondsLoc(Gamedata::getInstance().getXmlInt("textCoordinates/secondsX"),
         Gamedata::getInstance().getXmlInt("textCoordinates/secondsY")),

  capFrameRate(false),
  fpsIndex(0),
  avgFps(0)
{
   
for(int i =0;i<size;i++)
  fpsArray[i] = 0;
    start();
}

Clock::Clock(const Clock& c) :
  frames(c.frames), 
  ticksSinceLastFrame(c.ticksSinceLastFrame), 
  ticksAtLastFrame(c.ticksAtLastFrame), 
  sumOfTicks(c.sumOfTicks),
  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  fpsLoc(c.fpsLoc),
  secondsLoc(c.secondsLoc),
  capFrameRate(c.capFrameRate),
  fpsIndex(c.fpsIndex),
  avgFps(c.avgFps)
{

for(int i =0;i<size;i++)
  fpsArray[i] = c.fpsArray[i];
}

void Clock::draw() const { 
  IOManager::getInstance().
    printMessageValueAt("Avgfps: ", avgFps, fpsLoc[0], fpsLoc[1]);
  IOManager::getInstance().
    printMessageValueAt("seconds: ", getSeconds(), 
                                     secondsLoc[0], secondsLoc[1]);
}

void Clock::update() { 
  if ( paused ) return;
 // else if(sloMo) ticksSinceLastFrame = 1;  
  else{
      ++frames;
      int frameCap = Gamedata::getInstance().getXmlInt("frameCap");
      unsigned int clockTicks = 0;
      clockTicks = SDL_GetTicks(); 

      ticksSinceLastFrame = clockTicks - ticksAtLastFrame; 
      if(Gamedata::getInstance().getXmlBool("framesAreCapped") && ticksSinceLastFrame < (unsigned int)1000/ frameCap){
         SDL_Delay((1000/frameCap) - ticksSinceLastFrame);       
  	 clockTicks = SDL_GetTicks(); 
      }
   
      sumOfTicks += (clockTicks - ticksAtLastFrame);
      ticksAtLastFrame = clockTicks;
 }

avgFps = calculateAvgFps(); 
}
unsigned int Clock::getTicksSinceLastFrame() const {
  if (paused) return 0;
  else if(sloMo) return 1;
  return ticksSinceLastFrame;
}

void Clock::toggleSloMo() {
 if(!sloMo)
  sloMo = true;
  else
  sloMo = false;

}

int Clock::getFps() const { 
  if ( getSeconds() > 0 && frames > 0) return frames/getSeconds();  
  return 0;
}

int Clock::calculateAvgFps(){

  int avgFps = 0;
  int sumFps = 0;
  fpsIndex = (fpsIndex+1) % size;
  fpsArray[fpsIndex-1] = getFps();

  for(int i=0;i<size;i++)
  {
    sumFps+=fpsArray[i];
  }

  if(frames<=size){
    avgFps = sumFps/frames;
  }
  else{
    avgFps = sumFps/size;
  }
  return avgFps;
}

void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  ticksAtLastFrame = SDL_GetTicks(); 
}

void Clock::pause() {
  if( started && !paused ) {
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    ticksAtLastFrame = SDL_GetTicks();
    paused = false;
  }
}
