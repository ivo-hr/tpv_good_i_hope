#include "BadObject.h"
#include "../Game.h"

bool BadObject::toDelete()
{
	return !alive || game->isRebased(this);
}

void BadObject::onEnter()
{
	instances += 1;
}

void BadObject::onDelete()
{
	instances -= 1;
}

void BadObject::reset()
{
	instances = 0;
}

int BadObject::instances = 0;