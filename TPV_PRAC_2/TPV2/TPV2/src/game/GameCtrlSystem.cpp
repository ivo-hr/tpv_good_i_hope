#include "GameCtrlSystem.h"
#include "../sdlutils/InputHandler.h"
#include "Manager.h"
#include "FighterSystem.h"

void GameCtrlSystem::receive(const Message& m) {
    switch (m.id) {
    case _m_COLLISION_ASTEROIDFIGHTER:
        
        onCollision_FighterAsteroid();
        break;
    case _m_ASTEROIDS_EX:
        onAsteroidsExtinction();
        break;
    default:
        break;
    }
}

void GameCtrlSystem::initSystem()
{
    state_ = GameCtrlSystem::NEWGAME;
    auto fghtrSys = mngr_->getSystem<FighterSystem>();
    assert(fghtrSys != nullptr);
    fghtrSys->health = fghtrSys->maxHealth;
}

void GameCtrlSystem::update()
{

    if (ih().keyDownEvent()) {

        if (ih().isKeyDown(SDLK_SPACE) && state_ == GameCtrlSystem::GAMEOVER) {
            initSystem();
        }
        else if (ih().isKeyDown(SDLK_SPACE) && state_ != GameCtrlSystem::RUNNING) {
            state_ = GameCtrlSystem::RUNNING;
            Message m;
            m.id = _m_ROUND_START;
            mngr_->send(m);
        }

    }
}

void GameCtrlSystem::onCollision_FighterAsteroid()
{
    auto& ast = mngr_->getEntities(ecs::_grp_ASTEROID);
    int n = ast.size();

    for (int i = 0; i < n; i++) {
        mngr_->setAlive(ast[i], false);
    }

    auto fghtrSys = mngr_->getSystem<FighterSystem>();

    if (fghtrSys->health > 1)

        state_ = GameCtrlSystem::PAUSED;
    else {
        state_ = GameCtrlSystem::GAMEOVER;
    }

        
}

void GameCtrlSystem::onAsteroidsExtinction()
{
    auto& bul = mngr_->getEntities(ecs::_grp_BULLETS);
    int n = bul.size();

    for (int i = 0; i < n; i++) {
        mngr_->setAlive(bul[i], false);
    }
    state_ = GameCtrlSystem::GAMEOVER;
}