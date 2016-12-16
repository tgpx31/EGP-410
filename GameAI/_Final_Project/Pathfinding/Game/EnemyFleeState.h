#include "StateMachine.h"

class Enemy;
class  EnemyFleeState : public SM_State
{
public:
	EnemyFleeState(Enemy* pEnemy);
	~EnemyFleeState();

	void onEntrance();
	void onExit();
	Transition* update();

private:
	Enemy* mpEnemy;
};