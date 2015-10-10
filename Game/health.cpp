#include "health.h"

#include <sstream>
Health::Health() :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(1000, 100)), 
  totalLength(200), 
  currentLength(200), 
  thick(10), 
  increments(20),
  interval(1000),
  deltaTime(0),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xce, 0xb4, 0xb4) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(RED),
  score(0) {
}

Health::Health(int sx, int sy, int tl, int cl,
               float t, int inc, Uint32 c, float sp):
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(sx, sy)), 
  totalLength(tl), 
  currentLength(cl), 
  thick(t), 
  increments(inc),
  interval(sp),
  deltaTime(SDL_GetTicks()),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
    color(c),score(0) {
}

void Health::drawBox() const {
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+totalLength, start[1], 
                      thick, GRAY);
  // Two Horizontal lines
  Draw_AALine(screen, start[0], start[1]-8, 
                      start[0]+totalLength, start[1]-8, 
                      1.0, BLACK);
  Draw_AALine(screen, start[0], start[1]+8, 
                      start[0]+totalLength, start[1]+8, 
                      1.0, BLACK);
  // Two Vertical lines
  Draw_AALine(screen, start[0]-1, start[1]-8, 
                      start[0]-1, start[1]+8, 
                      2.0, BLACK);
  Draw_AALine(screen, start[0]+totalLength+1, start[1]-8, 
                      start[0]+totalLength+1, start[1]+8, 
                      2.0, BLACK);
  
}

void Health::draw() const {
  drawBox();
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+currentLength, start[1], 
                      thick, color);
 if(currentLength<10) {
  Draw_AALine(screen, 0, 430, 
                      1500,430 , 
                      1500, 0xFF,0x00,0xFF,0x90);
 
  TTF_Font * font = TTF_OpenFont(
        Gamedata::getInstance().getXmlStr("font/file").c_str(), 
         100);
  IOManager::getInstance().printMessageAtF("Game Over", 300,300,font); 

    TTF_CloseFont(font);
  font = TTF_OpenFont(
        Gamedata::getInstance().getXmlStr("font/file").c_str(), 
         40);
    
   std::string s = "High score ----";
std::ostringstream oss;    

oss << score;
     
   s= s+oss.str();
   
   IOManager::getInstance().printMessageAtF(s, 300,500,font); 

    TTF_CloseFont(font);
  }
}
void Health::update() {
    if(currentLength > 0)
    currentLength -= increments;
  }
