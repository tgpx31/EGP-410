#include "Enemy.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"

Enemy::Enemy(Sprite* pNormalSprite, Sprite* pFleeSprite)
{
	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, Vector2D(100, 100), 0.0f, Vector2D(0, 0), 0.0f);

	mpStateMachine = new StateMachine();
}

Enemy::~Enemy()
{
	delete mpUnit;
	mpUnit = NULL;

	delete mpStateMachine;
	mpStateMachine = NULL;
}

void Enemy::update(float time)
{
	//mpStateMachine->update();
	mpUnit->update(time);
}

void Enemy::draw()
{
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}
