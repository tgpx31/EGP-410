#include "EnemyFleeState.h"
#include "Enemy.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Player.h"

EnemyFleeState::EnemyFleeState(Enemy* pEnemy) : SM_State(2)
,mpEnemy(pEnemy)
{
	addTransition(new Transition(TO_WANDER_TRANSITION, 0));
	addTransition(new Transition(TO_CHASE_TRANSITION, 1));
}

EnemyFleeState::~EnemyFleeState()
{
}

void EnemyFleeState::onEntrance()
{
	mpEnemy->setSprite(true);
}

void EnemyFleeState::onExit()
{
	mpEnemy->setSprite(false);
}

Transition* EnemyFleeState::update()
{
	float distanceToPlayer = abs((mpEnemy->getUnit()->getPosition() - gpGameApp->getPlayer()->getPosition()).getLength());
	if (distanceToPlayer <= 250.0f)
	{
		if (gpGameApp->getPlayer()->getInvincible())
		{
			return NULL;
		}
		else
		{
			return mTransitions[TO_CHASE_TRANSITION];
		}
	}
	else
	{
		return mTransitions[TO_WANDER_TRANSITION];
	}
}
