#pragma once

#include "Trackable.h"
#include "Defines.h"
#include "Vector2D.h"
#include <map>

class Candy;
class Sprite;

class CandyManager : public Trackable
{
private:
	std::map<IDType, Candy*> mCandy;

public:
	CandyManager();
	~CandyManager();

	void addCandy(IDType id, Candy* pCandy);
	void createCandy(Vector2D position, Sprite* pSprite, float respawnTime);

	void update(float time);
	void draw();
};