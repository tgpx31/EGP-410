#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class CylinderCollision;

class Candy : public Trackable
{
private:
	Sprite* mpSprite;
	CylinderCollision* mpCollider;
	Vector2D mPosition;
	float mRespawnTime;
	float mElapsedTime;
	bool mIsActive;

public:
	Candy(Vector2D position, Sprite* pSprite, float respawnTime);
	~Candy();

	void update(float time);
	void draw();
};