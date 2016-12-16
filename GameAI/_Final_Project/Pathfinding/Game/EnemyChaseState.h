#include "StateMachine.h"

class Enemy;
class  EnemyChaseState : public SM_State
{
public:
	EnemyChaseState(Enemy* pEnemy);
	~EnemyChaseState();

	void onEntrance();
	void onExit();
	Transition* update();

private:
	Enemy* mpEnemy;
};