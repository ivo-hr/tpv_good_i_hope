#pragma once
#include "System.h"


class RenderSystem : public ecs::System {
public:

	constexpr static ecs::sysId_type id = ecs::_sys_RENDER;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	void initSystem() override;

	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondiente: si el juego está parado, etc (como en
	// la práctica 1)
	void update() override;
private:

	void drawMsgs();

	void drawAsteroids();

	void drawFighter();

	void drawBullets();

	void drawHealth();

	uint8_t winner_ = 0; // 0 - None, 1 - Asteroid, 2- Fighter
};