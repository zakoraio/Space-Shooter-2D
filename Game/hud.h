#ifndef HUD__H
#define HUD__H


#include <iostream>
#include "ioManager.h"
#include "aaline.h"
#include "vector2f.h"



class Hud
{
    public:
    Hud(SDL_Surface * screen ,int x,int y);
    void drawHUD();
    void setPlayerScore(int s){ playerScore = s; }
   Hud(const Hud&);
   Hud& operator=(const Hud&);
   void setGameStarted(bool started){ gameStarted = started; }
   private:

    SDL_Surface* screen;
    int startX;
    int startY;
   const std::string username;
   const std::string title;
   const std::string score;
   const std::string pressTMsg;
   const std::string pressRMsg;
   const std::string pressCMsg;
   const std::string loadSpriteMsg;
   Vector2f scoreLoc;
   Vector2f pressTMsgLoc;
   Vector2f pressRMsgLoc;
   Vector2f pressCMsgLoc;
   Vector2f loadSpriteMsgLoc;
   Vector2f collisonMsgLoc;
   int playerScore;
   bool gameStarted;

};

#endif
