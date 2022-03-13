

#include "Manager.h"

namespace ecs {

Manager::Manager() :
		ents_(), 
		hdlrs_(), 
		entsByGroup_() 
{

	ents_.reserve(100);


	for (auto &groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}
}

Manager::~Manager() {


	for (auto e : ents_)
		delete e;
}

void Manager::refresh() {

	for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
			auto &groupEntities = entsByGroup_[gId];
		groupEntities.erase(
				remove_if(groupEntities.begin(), groupEntities.end(),
						[gId](Entity *e) {
							return !e->isAlive() || !e->hasGroup(gId);
						}), groupEntities.end());
	}


	ents_.erase( 
			remove_if(ents_.begin(), ents_.end(), [](Entity *e) {
				if (e->isAlive()) {
					return false;
				} else {
					delete e;
					return true;
				}
			}), 
			ents_.end());

}

}
