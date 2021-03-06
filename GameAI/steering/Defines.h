#ifndef DEFINES_H
#define DEFINES_H

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

const IDType INVALID_ID = -1;

const IDType HIGHEST_ID = 9999;

const float MAX_WANDER_ROTATION = 1.0f;

const float DEFAULT_RADIUS = 200.0f;
const float COHESION_RADIUS = 150.0f;
const float SEPERATION_RADIUS = 75.0f;

#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()

#endif