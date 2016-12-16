#include "Trackable.h"
#include "Defines.h"
#include "Vector2D.h"
#include <map>

class Door;
class Sprite;

class DoorManager : public Trackable
{
private:
	std::map<IDType, Door*> mDoors;

public:
	DoorManager();
	~DoorManager();

	void addDoor(IDType id, Door* pDoor);
	void createDoor(Vector2D position, Sprite* pSprite);
	Door* getDoorTo(IDType mapTo);

	void update();
	void draw();
};