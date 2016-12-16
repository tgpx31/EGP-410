#include "EnemyChaseState.h"
#include "Enemy.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Player.h"

EnemyChaseState::EnemyChaseState(Enemy* pEnemy) : SM_State(1)
,mpEnemy(pEnemy)
{
	addTransition(new Transition(TO_WANDER_TRANSITION, 0));
	addTransition(new Transition(TO_FLEE_TRANSITION, 2));
}

EnemyChaseState::~EnemyChaseState()
{
}

void EnemyChaseState::onEntrance()
{
}

void EnemyChaseState::onExit()
{
}

Transition* EnemyChaseState::update()
{
	float distanceToPlayer = abs((mpEnemy->getUnit()->getPosition() - gpGameApp->getPlayer()->getPosition()).getLength());
	if (distanceToPlayer <= 250.0f)
	{
		if (gpGameApp->getPlayer()->getInvincible())
		{
			return mTransitions[TO_FLEE_TRANSITION];
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return mTransitions[TO_WANDER_TRANSITION];
	}
}
