#pragma once
#include "System.h"


class RenderSystem : public ecs::System {
public:

	constexpr static ecs::sysId_type id = ecs::_sys_RENDER;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	void initSystem() override;

	// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondiente: si el juego est� parado, etc (como en
	// la pr�ctica 1)
	void update() override;
private:

	void drawMsgs();

	void drawAsteroids();

	void drawFighter();

	void drawBullets();

	void drawHealth();

	uint8_t winner_ = 0; // 0 - None, 1 - Asteroid, 2- Fighter
};