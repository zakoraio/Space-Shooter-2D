#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "twowaymultisprite.h"
#include "gamedata.h"
#include "manager.h"
#include "player.h"
#include <sstream>
#include<algorithm>
#include"explosion.h"


  static int CXT[20] ={0,150,300,450,600,750,900,1150,1300,1450};
  static int CYT[20] ={0,0,0,0,0,0,0,0,0,0};

  static int CYR[20] ={0,100,200,300,400,500,600,700,800};
  static int CXR[20] ={1400,1400,1400,1400,1400,1400,1400,1400,1400};

  static int CXB[20] ={0,150,300,450,600,750,900,1150,1300,1450};
  static int CYB[20] ={800,800,800,800,800,800,800,800};

  static int CYL[20] ={0,100,200,300,400,500,600,700,800};
  static int CXL[20] ={0,0,0,0,0,0,0,0,0};

class CompareJets {
  public:
  bool operator()( const Jets *left , const Jets * right) const{
    return left->getScale() < right->getScale();
  }

};


void Manager::reset(){
wave = 3;

for (unsigned i = 0; i < explosions.size(); ++i) {
    Explosion *e = explosions[i];
    explosions.erase(explosions.begin()+i);
    delete e;
  }

for (unsigned i = 0; i < bullets.size(); ++i) {
  Bullet *b = bullets[i];
  bullets.erase(bullets.begin()+i);
  delete b;
}
unloadSprites();
loadSprites();
player->reset();
hud->setGameStarted(false);
clock.pause();
gameOver = false;
gameStarted= false;
}

Explosion* createExplosion(float x,float y){
 Explosion * e = new Explosion("explosion");
 e->X(x-20);
 e->Y(y-20);
return e;
}
int getRandomBetween(int min,int max){
        int number = Gamedata::getInstance().getRandInRange(min,max);
        return number;
}


Manager::~Manager() { 
 unloadSprites(); 
 
for (unsigned i = 0; i < explosions.size(); ++i) {
    Explosion *e = explosions[i];
    explosions.erase(explosions.begin()+i);
    delete e;
  }

for (unsigned i = 0; i < bullets.size(); ++i) {
  Bullet *b = bullets[i];
  bullets.erase(bullets.begin()+i);
  delete b;
}


delete crosshair;

    Mix_FreeChunk(fire);
    Mix_FreeChunk(explode);
    Mix_FreeChunk(music);
  
Mix_CloseAudio();delete player;
SDL_FreeSurface(screen);

}
Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  username(Gamedata::getInstance().getXmlStr("username")),
  parallax1("parallax1", Gamedata::getInstance().getXmlInt("parallax1/factor") ),
  parallax2("parallax2", Gamedata::getInstance().getXmlInt("parallax2/factor") ),
  viewport( Viewport::getInstance() ),
  jets(),
  explosions(),
  bullets(),
  player(new Player("player")),
  crosshair(NULL),
  explode(NULL),
  fire(NULL),
  music(NULL),
  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
  detectCollision(false),
  collisonDistance(Gamedata::getInstance().getXmlInt("collisonDistance")),
  hud( new Hud(io.getScreen(), Gamedata::getInstance().getXmlInt("hud/x"),Gamedata::getInstance().getXmlInt("hud/y"))),
  drawHud(false),
  wave(3),
  gameOver(false),
  gameStarted(false)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);

  Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

  explode = Mix_LoadWAV( "sounds/boom.wav" );    
  fire = Mix_LoadWAV( "sounds/fire.wav" );    
  music = Mix_LoadWAV( "sounds/Electric.wav" );    
  player->toggleRotation();
  player->X(750);
  player->Y(430);  
 
  crosshair = new CrossHair("crosshair",9,1.0);
 
  loadSprites();  

  viewport.setObjectToTrack(player);
}


void Manager::loadSprites(){


   for(unsigned int i =0;i<wave;i++){
	Jets *j = new Jets("jets",5,0.6);
	j->X(CXT[i]);
        j->Y(CYT[i]);
        j->setXTh(35);
        j->setYTh(150);
      jets.push_back(j);
   } 


   for(unsigned int i =0;i<wave;i++){
	Jets *j = new Jets("jets",5,0.6);
	j->X(CXR[i]);
        j->Y(CYR[i]);
        j->setXTh(150);
        j->setYTh(35);
      jets.push_back(j);
   } 


   for(unsigned int i =0;i<wave;i++){
	Jets *j = new Jets("jets",5,0.6);
	j->X(CXB[i]);
        j->Y(CYB[i]);
        j->setXTh(35);
        j->setYTh(150);
      jets.push_back(j);
   } 

   for(unsigned int i =0;i<wave;i++){
	Jets *j = new Jets("jets",5,0.6);
	j->X(CXL[i]);
        j->Y(CYL[i]);
        j->setXTh(150);
        j->setYTh(35);
      jets.push_back(j);
   } 


}
void Manager::unloadSprites(){
    for(unsigned int i=0;i<jets.size();i++){
	Jets * jet = jets[i];	
        jets.erase(jets.begin() + i);
        delete jet;
    } 
}
void Manager::draw() const {
  string message;
  if(detectCollision&&clock.getSeconds()>(unsigned int) Gamedata::getInstance().getXmlInt("minSprites")) //wait until 5 seconds have passed since the begenning of animation so the jets could spread out
   message = "Collision Detection :ON";
  else
   message = "Collision Detection :OFF";
 
 
  parallax1.draw();
  
for(unsigned i=0;i<explosions.size();i++){
  if(explosions[i]&&!explosions[i]->isComplete())
  explosions[i]->draw();
}



for(unsigned i=0;i<bullets.size();i++){
  bullets[i]->draw();
}


for (unsigned  i = 0; i < jets.size()/2; ++i) {
    jets[i]->draw();
  }
  parallax2.draw();
  
for (unsigned  i = jets.size()/2; i < jets.size(); ++i) {
    jets[i]->draw();
  }
  player->draw();
  if(drawHud){  
  clock.draw();
  hud->drawHUD();
}

  crosshair->draw();
  viewport.draw();
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % jets.size();
  viewport.setObjectToTrack(jets[currentSprite]);
}

void Manager::update() {

if(gameStarted){
float x,y; 

  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
  int dist = 0;
  bool collisionDetected =  false;
 player->update(ticks);
 hud->setPlayerScore(player->getScore());
int secs = clock.getSeconds();


for(unsigned int i = 0;i<bullets.size()/4;i++){
 if(secs>1 && secs%20==0){
  Bullet *b =  bullets[i];      
 	bullets.erase(bullets.begin()+i);
	delete b;
}
}


for(unsigned int i = 0;i<bullets.size();i++){
bullets[i]->update(ticks);
}



for(unsigned int i = 0;i<explosions.size()/4;i++){
 if(secs>1 && secs%20==0){
  Explosion *e =  explosions[i];      
 	explosions.erase(explosions.begin()+i);
	delete e;
}
}



for(unsigned int i = 0;i<explosions.size();i++){
if(explosions[i]){
explosions[i]->update(ticks);
}
}
  for(unsigned int i = 0; i < jets.size(); ++i) {
     if(jets[i]->getType() == "Sprite" && clock.getSeconds()>1){   // wait for at least 5 seconds before jumping in the collision detection so that the jets have change to spread out
	for(unsigned int j =0;j<jets.size();j++) {
            if(jets[j]->getType()=="Sprite" && i!=j){
                dist = jets[i]->calculateDistance(jets[j]);
                if(dist <= collisonDistance){
                  jets[j]->updateVelocitiesAfterCollision();
                  collisionDetected = true;
             }
           }
        }

    if(collisionDetected){
    	jets[i]->updateVelocitiesAfterCollision(); 
        collisionDetected = false;
      }
    }

   jets[i]->setPlayerCoordinates(player->X(),player->Y()); 
   jets[i]->update(ticks);
  }



  for(unsigned int j = 0; j < jets.size(); ++j) {
        if(player->detectCollision(jets[j])){
 		 Jets * jet;
		  x = jets[j]->X()-(jets[j]->getFrame()->getWidth()/2-jets[j]->getFrame()->getWidth()/2*jets[j]->getScale());
		  y = jets[j]->Y()-(jets[j]->getFrame()->getHeight()/2-jets[j]->getFrame()->getHeight()/2*jets[j]->getScale());
	          explosions.push_back(createExplosion(x,y)); 
		   Mix_PlayChannel( -1, explode, 0 ); 
		  jet = jets[j];
		  jets.erase(jets.begin()+j);
		  delete jet;
		  
        } 
  } 
 

std::vector<Jets *>::iterator iter = jets.begin();


 for(unsigned i =0 ;i<bullets.size();i++){
	 for(unsigned int j =0;j<jets.size();j++) {
            {
               dist = jets[j]->calculateDistance(bullets[i]);
                if(dist <= collisonDistance){
		  x = jets[j]->X()-(jets[j]->getFrame()->getWidth()/2-jets[j]->getFrame()->getWidth()/2*jets[j]->getScale());
		  y = jets[j]->Y()-(jets[j]->getFrame()->getHeight()/2-jets[j]->getFrame()->getHeight()/2*jets[j]->getScale());
	          explosions.push_back(createExplosion(x,y)); 
		   Mix_PlayChannel( -1, explode, 0 ); 
		  jets.erase(jets.begin()+j);
                  player->incrementScore();
                  bullets[i]->X(20000.0f);
                  bullets[i]->Y(20000.0f);   
             }
           }
        }
  }

  
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  parallax1.update();
  parallax2.update();

    if(SDL_GetTicks()%600==0 && !gameOver && gameStarted){
    loadSprites();  
   // unloadSprites();  
    wave++;
}
  viewport.update(); 
}
}



void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start();
  int startT,now;
  int x_coordinate = 0, y_coordinate = 0;
  drawHud=true;
  if(gameStarted)
  startT=clock.getSeconds(); 
  bool fired = false;
  SDL_ShowCursor(SDL_DISABLE);
  
   Mix_PlayChannel( -1, music, 0 ); 

  	hud->drawHUD();
  while ( not done ) {

    while ( SDL_PollEvent(&event) ) {
      
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }

        if ( keystate[SDLK_F1] ) {
            toggelDrawHud();
        }
        
        if ( keystate[SDLK_g] ) {
            	player->toggleGod();
        }
        if ( keystate[SDLK_F7] ) {
            reset();
        }
	if(!gameOver){
        if(keystate[SDLK_a])  player->setKey(1); 
        else if(keystate[SDLK_s])  player->setKey(2);
        else if(keystate[SDLK_d])  player->setKey(3);
        else if(keystate[SDLK_w])  player->setKey(4);
        if(keystate[SDLK_a] && keystate[SDLK_s]) player->setKey(5);
        else if(keystate[SDLK_a] && keystate[SDLK_w]) player->setKey(6);
        else if(keystate[SDLK_w] && keystate[SDLK_d]) player->setKey(7);
        else if(keystate[SDLK_s] && keystate[SDLK_d]) player->setKey(8);
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) {
		clock.unpause(); 
	  }
          else {
		clock.pause(); 
          }
        }
        if (keystate[SDLK_F3]) {
          clock.toggleSloMo();
        }
        if (keystate[SDLK_b]) {
          gameStarted = true;
          hud->setGameStarted(true);

          if ( clock.isPaused() ) {
		clock.unpause(); 
	  }
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
      }
      
     else if(event.type == SDL_KEYUP&&!gameOver){
        player->setKey(0);
        if(keystate[SDLK_a]) { player->setKey(1);}
        else if(keystate[SDLK_s]) { player->setKey(2);}
        else if(keystate[SDLK_d]) { player->setKey(3);}
        else if(keystate[SDLK_w]) { player->setKey(4);}
        }
  
      else if( event.type == SDL_MOUSEMOTION ) {
               SDL_GetMouseState(&x_coordinate, &y_coordinate);
               player->setNewOrientation(x_coordinate,y_coordinate);
               crosshair->X(x_coordinate);
               crosshair->Y(y_coordinate);
         }  
    }
     if( event.type == SDL_MOUSEBUTTONDOWN &&!gameOver)
    {
	if( event.button.button == SDL_BUTTON_LEFT )
        {
		if(!fired){	
		   	Mix_PlayChannel( -1, fire, 0 ); 
			SDL_Delay(20);
			Bullet * bullet = new Bullet("bullet",6,1.5);
			bullet->setOrientation(event.button.x,event.button.y,player->X(),player->Y(),player->getAngle());	
                	bullets.push_back(bullet);
			fired = true;
		}
	}
    }
    
   if( event.type == SDL_MOUSEBUTTONUP ) if( event.button.button == SDL_BUTTON_LEFT ) fired = false;
   if(player->getHealth()<=0)
     {
	gameOver = true;
     }
   	 draw();
   	 update();
    	now = clock.getSeconds();
    	if(now-startT>3&&now<5){
      		drawHud= false;
    	}
 
  }
}
