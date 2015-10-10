# include "hud.h"


const int HUD_WIDTH = Gamedata::getInstance().getXmlInt("hud/width");
const int HUD_HEIGHT = Gamedata::getInstance().getXmlInt("hud/height");


Hud::Hud(SDL_Surface * surface , int x , int y):
screen(surface),
startX(x),
startY(y),
username(Gamedata::getInstance().getXmlStr("username")),
title(Gamedata::getInstance().getXmlStr("screenTitle") ),
score(Gamedata::getInstance().getXmlStr("scoreMsg") ),
pressTMsg(Gamedata::getInstance().getXmlStr("pressTMsg")),
pressRMsg(Gamedata::getInstance().getXmlStr("pressRMsg")),
pressCMsg(Gamedata::getInstance().getXmlStr("pressCMsg")),
loadSpriteMsg(Gamedata::getInstance().getXmlStr("loadSpritesMsg")),
scoreLoc(Gamedata::getInstance().getXmlInt("textCoordinates/scoreX"),Gamedata::getInstance().getXmlInt("textCoordinates/scoreY")),
pressTMsgLoc(Gamedata::getInstance().getXmlInt("textCoordinates/pressTX"), Gamedata::getInstance().getXmlInt("textCoordinates/pressTY")),
pressRMsgLoc(Gamedata::getInstance().getXmlInt("textCoordinates/pressRX"),Gamedata::getInstance().getXmlInt("textCoordinates/pressRY")),
pressCMsgLoc(Gamedata::getInstance().getXmlInt("textCoordinates/pressCX"),Gamedata::getInstance().getXmlInt("textCoordinates/pressCY")),
loadSpriteMsgLoc(Gamedata::getInstance().getXmlInt("textCoordinates/loadSpritesX"),Gamedata::getInstance().getXmlInt("textCoordinates/loadSpritesY")),
collisonMsgLoc(Gamedata::getInstance().getXmlInt("textCoordinates/collisonX"),Gamedata::getInstance().getXmlInt("textCoordinates/collisonY")),
playerScore(0),
gameStarted(false)
{
 SDL_WM_SetCaption(title.c_str(), NULL);
}


void Hud::drawHUD() {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, startX, startY+HUD_HEIGHT/2,
                      startX+HUD_WIDTH,startY+HUD_HEIGHT/2,
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, startX,startY, startX+HUD_WIDTH,startY, RED);
  
if(!gameStarted){
  	Draw_AALine(screen, 0, 430, 
                      1500,430 , 
                      1500, 0x20,0xFF,0xFF,0x90);
  
 	TTF_Font * font = TTF_OpenFont(
        	Gamedata::getInstance().getXmlStr("font/file").c_str(), 
         	60);
  	IOManager::getInstance().printMessageAtF("Press B to begin game", 300,300,font); 

    TTF_CloseFont(font);
}
  	IOManager &io = IOManager::getInstance();
   	std::ostringstream oss;    
   	oss <<" : "<< playerScore;  
  	io.printMessageAt(score+oss.str(), scoreLoc[0],scoreLoc[1]); 
}

