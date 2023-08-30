#include "Body/BodyFactory.h"
#include "Character.h"
#include "Skeleton.h"
#include "math/Math.h"
Character* BodyFactory::makeCharacter(const Skeleton& _skeleton, const Controller& controller)
{
    Character* player = new Character(_skeleton, controller);
    player->initialize();
    return player;
}