#ifndef AI_H_
#define AI_H_

#include "Entity.h"

typedef Entity* Path;

Path Locate2DPath ( Entity seeker, Entity dst );

Path Locate3DPath ( Entity seeker, Entity dst );

#endif//AI_H_