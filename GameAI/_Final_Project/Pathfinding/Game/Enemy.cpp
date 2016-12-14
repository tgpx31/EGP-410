#include "Enemy.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Player.h"

#include "GameApp.h"
#include "PlayerDeathMessage.h"
#include "GameMessageManager.h"

bool Enemy::checkCollidingPlayer()
{
	if (getCollider()->isCollidingCylinders(gpGameApp->getPlayer()->getCollider()))
		return true;

	return false;
}

Enemy::Enemy(Sprite* pNormalSprite, Sprite* pFleeSprite)
{
	mpNormalSprite = pNormalSprite;
	mpFleeSprite = pFleeSprite;
	
	mpUnit = new KinematicUnit(mpNormalSprite, Vector2D(100, 100), 0.0f, Vector2D(0, 0), 0.0f, .8f);

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
	mpUnit->seek(gpGameApp->getPlayer()->getPosition());
	if (checkCollidingPlayer())
	{
		std::cout << "Hit the player" << std::endl;
		// Player death
		GameMessage* pMessage = new PlayerDeathMessage();
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
}

void Enemy::draw()
{
	mpUnit->draw(gpGame->getGraphicsSystem()->getBackBuffer());
}
