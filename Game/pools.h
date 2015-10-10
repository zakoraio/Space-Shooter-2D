#ifndef POOLS__H
#define POOLS__H
#include <algorithm>
#include "jets.h"
#include "explosion.h"
#include "bullet.h"
#include<list>

class Pools{

Explosion * getExplosionObjFromPool();

Bullet *  getBulletObjFromPool();

Jets * getJetObjFromPool();

Pools(int eLimit,int jLimit,int bLimit);

void returnExplsionObjToPool(Explosion * e);
void returnJetObjToPool(Jets * j);
void returnBulletObjToPool(Bullet * e);

std::list<Explosion *> freeExplObjs;
std::list<Explosion *> inuseExplObjs;
std::list<Jets *> freeJetObjs;
std::list<Jets *> inuseJetObjs;
std::list<Bullet *> freeBulletObjs;
std::list<Bullet *> inuseBulletObjs;

};
#endif
