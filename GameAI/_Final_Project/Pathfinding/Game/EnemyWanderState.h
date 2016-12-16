#include "StateMachine.h"

class Enemy;
class  EnemyWanderState : public SM_State
{
public:
	EnemyWanderState(Enemy* pEnemy);
	~EnemyWanderState();

	void onEntrance();
	void onExit();
	Transition* update();

private:
	Enemy* mpEnemy;
};