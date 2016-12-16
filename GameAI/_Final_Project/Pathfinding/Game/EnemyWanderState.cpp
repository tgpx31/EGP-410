#include "EnemyWanderState.h"
#include "Enemy.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Player.h"

EnemyWanderState::EnemyWanderState(Enemy* pEnemy) : SM_State(0)
,mpEnemy(pEnemy)
{
	addTransition(new Transition(TO_CHASE_TRANSITION, 1));
	addTransition(new Transition(TO_FLEE_TRANSITION, 2));
}

EnemyWanderState::~EnemyWanderState()
{
}

void EnemyWanderState::onEntrance()
{
}

void EnemyWanderState::onExit()
{
}

Transition* EnemyWanderState::update()
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
			return mTransitions[TO_CHASE_TRANSITION];
		}
	}
	else
	{
		return NULL;
	}
}
