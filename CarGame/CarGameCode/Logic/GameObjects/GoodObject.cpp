#include "GoodObject.h"
#include "../Game.h"

bool GoodObject::toDelete()
{
	return !alive || game->isRebased(this);
}

void GoodObject::onEnter()
{
	instances += 1;
}

void GoodObject::onDelete()
{
	instances -= 1;
}

void GoodObject::reset()
{
	instances = 0;
}

int GoodObject::instances = 0;
