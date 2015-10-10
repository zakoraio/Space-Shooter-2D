#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include <vector>
#include "player.h"
#include "hud.h"
#include "jets.h"
#include "explosion.h"
#include "bullet.h"
#include <SDL_mixer.h>
#include "crosshair.h"
class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();
  void toggleCollisonDetection() { detectCollision = !detectCollision; }
  void toggelDrawHud() { drawHud =!drawHud; }
  void loadSprites();
  void unloadSprites();
  void reset();
private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  const std::string username;

  World parallax1; 
  World parallax2;
  Viewport& viewport;
  std::vector<Jets *> jets;
  std::vector<Explosion *> explosions;
  std::vector<Bullet *> bullets;
  Player * player;
  CrossHair *crosshair;
  Mix_Chunk *explode;
  Mix_Chunk *fire;
  Mix_Chunk *music;
  int currentSprite;
  bool makeVideo;
  int frameCount;
  const int frameMax;
  bool detectCollision;
  int collisonDistance;
  Hud * hud;
  bool drawHud;
  unsigned int wave;  
  bool gameOver;
  bool gameStarted;
void draw() const;
  void update();
   
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
