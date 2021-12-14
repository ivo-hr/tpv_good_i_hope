#include "GameObjectContainer.h"
#include <vector>
GameObjectContainer:: ~GameObjectContainer(){
	int num = gameObjects.size();

	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr) delete gameObjects[i];
	}
}

void GameObjectContainer::update(){
	int num = gameObjects.size();
	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr) gameObjects[i]->update();
	}
}

void GameObjectContainer::draw(){
	int num = gameObjects.size();
	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr) gameObjects[i]->draw();
	}
}

void GameObjectContainer::drawDebug(){
	int num = gameObjects.size();
	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr) gameObjects[i]->drawDebug();
	}
}

void GameObjectContainer::add(GameObject* gameObject){
	gameObjects.push_back(gameObject);
}

void GameObjectContainer::removeDead(){
	int num = gameObjects.size();

	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr && gameObjects[i]->toDelete()){
			gameObjects[i]->onDelete();

			delete gameObjects[i];

			for (int j = i + 1; j < gameObjects.size(); j++) 
				gameObjects[j - 1] = gameObjects[j];
			
			num -= 1;

			gameObjects.resize(num);
		}
	}
}

vector<Collider*> GameObjectContainer::getCollisions(GameObject* g){
	int num = gameObjects.size();
	vector<Collider*> a;

	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr && gameObjects[i] != g &&
		 SDL_HasIntersection(&gameObjects[i]->getCollider(), &g->getCollider()))
			a.push_back(gameObjects[i]);
	}

	return a;
}

bool GameObjectContainer::hasCollision(GameObject* g){
	int num = gameObjects.size();

	for (int i = 0; i < num; i++){
		if (gameObjects[i] != nullptr && gameObjects[i] != g &&
		 SDL_HasIntersection(&gameObjects[i]->getCollider(), &g->getCollider()))
		 return true;
	}

	return false;
}
