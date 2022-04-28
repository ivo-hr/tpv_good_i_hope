#include "AsteroidsSystem.h"
#include "Entity.h"
#include "components/Transform.h"
#include "Manager.h"
#include "Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "components/FramedImage.h"
#include "components/asteroidTypeGen.h"

void AsteroidsSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_END:
		onRoundOver();
		break;
	case _m_COLLISION_BULLETASTEROID:
		nextGen(m.collision_bulast_data.a);
		break;
	default:
		break;
	}
}

void AsteroidsSystem::initSystem()
{
}

void AsteroidsSystem::update()
{
	auto& ast = mngr_->getEntities(ecs::_grp_ASTEROID);
	auto n = ast.size();

	for (int i = 0; i < n; i++) {
		ast[i]->update();
	}

	moveAsteroids();
	toroidalMov();
	auto sys = mngr_->getSystem<GameCtrlSystem>();

	if (sys->getState() == sys->RUNNING) {
		if (sdlutils().currRealTime() > lastSpwnTime_ + asteroidRate_ * 1000) {
			
			createAsteroids(1);

			lastSpwnTime_ = sdlutils().currRealTime();
		}

		if (numOfAsteroids_ <= 0) {
			Message end;
			end.id = _m_ASTEROIDS_EX;
			mngr_->send(end);
		}
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a)
{
	sdlutils().soundEffects().at("bangSmall").play();
	nextGen(a);
	mngr_->setAlive(a, false);

}

void AsteroidsSystem::onRoundOver()
{
	auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROID);		//Asteroid group

	auto n = asteroids.size();												//Group size

	//Kill every asteroid in group
	for (auto k = 0u; k < n; k++)
	{
		mngr_->setAlive(asteroids[k], false);
	}
	numOfAsteroids_ = 0;
}

void AsteroidsSystem::onRoundStart()
{
	createAsteroids(10);
}

void AsteroidsSystem::createAsteroids(uint16_t num)
{
	if (numOfAsteroids_ < limOfAsteroids_)
	{
		//Create asteroids until maxed out
		for (auto i = 0u; i < num; i++) {

			auto& rand = sdlutils().rand();			//Random number generator

			//Entity creation and integration to group
			auto e = mngr_->addEntity(ecs::_grp_ASTEROID);


				//Current asteroid Transform

			//Size and generation
			auto s = rand.nextInt(0, 3);

			

			if (s == 0)			s = 15;
			else if (s == 1)	s = 30;
			else				s = 45;

			//Starting position
			float x = rand.nextInt(-s, sdlutils().width() + s);
			float y = rand.nextInt(-s, sdlutils().height() + s);

			//Direction point
			auto cx = rand.nextInt(sdlutils().width() / 2 - 100, sdlutils().width() / 2 + 100);
			auto cy = rand.nextInt(sdlutils().height() / 2 - 100, sdlutils().height() / 2 + 100);

			//Translation of starting position outside view, randomized  axis priority
			if (rand.nextInt(0, 2) == 0) {

				if (y < sdlutils().height() && y > 0)
				{
					if (rand.nextInt(0, 2) == 0) {
						x = -s;
					}
					else x = sdlutils().width() + s;
				}

				else if (x < sdlutils().width() && x > 0)
				{
					if (rand.nextInt(0, 2) == 0) {
						y = -s;
					}
					else y = sdlutils().height() + s;
				}
			}
			else {

				if (x < sdlutils().width() && x > 0)
				{
					if (rand.nextInt(0, 2) == 0) {
						y = -s;
					}
					else y = sdlutils().height() + s;
				}

				else if (y < sdlutils().height() && y > 0)
				{
					if (rand.nextInt(0, 2) == 0) {
						x = -s;
					}
					else x = sdlutils().width() + s;
				}


			}


			auto sp = rand.nextInt(1, 5) / 10.0f;				//Speed of  the asteroid
			auto dirX = ((cx - x) / 100) * sp;
			auto dirY = ((cy - y) / 100) * sp;
			//Asteroid type maker
			auto r = rand.nextInt(0, 10);
			//Asteroid that follows

			mngr_->addComponent<Transform>(e, Vector2D(x, y), Vector2D(dirX, dirY), s, s, 0);

			if (r < 3)
			{
				r = 1;
				mngr_->addComponent<FramedImage>(e, &sdlutils().images().at("asteroid_g"), 6, 5);						//Image
			}

			//Normal asteroid
			else
			{
				r = 0;
				mngr_->addComponent<FramedImage>(e, &sdlutils().images().at("asteroid"), 6, 5);							//Image

				//Asteroid direction

			}
			mngr_->addComponent<asteroidTypeGen>(e, s/15, r);
			numOfAsteroids_++;	
		}
	}
}

void AsteroidsSystem::moveAsteroids()
{
	auto& astEnt = mngr_->getEntities(ecs::_grp_ASTEROID);
	
	for (int i = 0; i < astEnt.size(); i++) {

		auto currAst = astEnt[i];
		auto currAstTr = mngr_->getComponent<Transform>(currAst);
		if (mngr_->getComponent<asteroidTypeGen>(currAst)->typ_ == 0) {
			currAstTr->getPos() = currAstTr->getPos() + currAstTr->getVel();
		}
		else followFighter(currAstTr);
	}

}

void AsteroidsSystem::followFighter(Transform* ast)
{
	auto fght = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_FGHTR));
	
	ast->getVel() = ast->getVel().rotate(ast->getVel().angle(fght->getPos() - ast->getPos()));
	ast->getPos() = ast->getPos() + ast->getVel()/2;
}

void AsteroidsSystem::toroidalMov()
{
	auto& astEnt = mngr_->getEntities(ecs::_grp_ASTEROID);
	for (int i = 0; i < astEnt.size(); i++) {

		auto currAst = mngr_->getComponent<Transform>(astEnt[i]);
		
		if (currAst->getPos().getX() > sdlutils().width()) {
		currAst->getPos().setX(-currAst->getWidth());
		}
		else if (currAst->getPos().getX() + currAst->getHeight() < 0) {
		currAst->getPos().setX(sdlutils().width());
		}
		else if (currAst->getPos().getY() > sdlutils().height()) {
			currAst->getPos().setY(-currAst->getHeight());
		}
		else if (currAst->getPos().getY() + currAst->getWidth() < 0) {
			currAst->getPos().setY(sdlutils().height());
		}
		
		
	}
}

void AsteroidsSystem::nextGen(ecs::Entity* old)
{
	auto gen = mngr_->getComponent<asteroidTypeGen>(old)->gen_;
	auto typ = mngr_->getComponent<asteroidTypeGen>(old)->typ_;
	auto trans = mngr_->getComponent<Transform>(old);

	if (gen > 1) {
		for (int i = 0; i < 2; i++) {
			auto newAst = mngr_->addEntity(ecs::_grp_ASTEROID);

			mngr_->addComponent<asteroidTypeGen>(newAst, gen - 1, typ);

			mngr_->addComponent<Transform>(newAst,
				trans->getPos(),
				trans->getVel().rotate(sdlutils().rand().nextInt(0, 360)),
				(int)trans->getWidth() / 2, (int)trans->getHeight() / 2, 0);

			if (typ == 0) {
				mngr_->addComponent<FramedImage>(newAst, &sdlutils().images().at("asteroid"), 6, 5);
			}
			else mngr_->addComponent<FramedImage>(newAst, &sdlutils().images().at("asteroid_g"), 6, 5);
			numOfAsteroids_++;
		}
	}
	numOfAsteroids_--;

	mngr_->setAlive(old, false);


}
