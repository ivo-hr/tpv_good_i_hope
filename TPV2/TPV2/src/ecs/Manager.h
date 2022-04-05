#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include "Component.h"
#include "ecs.h"
#include "Entity.h"

namespace ecs {


class Manager {

public:
	Manager();
	virtual ~Manager();

	inline Entity* addEntity() {

		auto e = new Entity();
		e->setAlive(true);
		e->resetGroups();
		e->setContext(this);

		ents_.push_back(e);

		return e;
	}


	inline const auto& getEntities() {
		return ents_;
	}

	inline const auto& getEntitiesByGroup(grpId_type gId) {
		assert(gId < ecs::maxGroupId);
		return entsByGroup_[gId];
	}


	inline void setHandler(hdlrId_type hId, Entity *e) {
		assert(hId < ecs::maxHandlerId);
		hdlrs_[hId] = e;
	}


	inline Entity* getHandler(hdlrId_type hId) {
		assert(hId < ecs::maxHandlerId);
		return hdlrs_[hId];
	}

	void update() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->update();
	}


	void render() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->render();
	}

	void refresh();

private:


	friend Entity;

	void addToGroup(grpId_type gId, Entity *e) {
		entsByGroup_[gId].push_back(e);
	}

	std::vector<Entity*> ents_;
	std::array<Entity*, maxHandlerId> hdlrs_;
	std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;
};

}