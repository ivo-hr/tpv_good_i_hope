#pragma once
#include "../game/System.h"

class Entity;
class Vector2D;

class BulletsSystem : public ecs::System {
public:

	constexpr static ecs::sysId_type id = ecs::_sys_BULLET;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	void initSystem() override;

	// Si el juego est� parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la pr�ctica 1.
	void update() override;
private:

	// Para gestionar el mensaje de que el jugador ha disparado. A�adir una bala al
	// juego, como en la pr�ctica 1. Recuerda que la rotaci�n de la bala ser�a
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height, float rot);


	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala �b�.
	void onCollision_BulletAsteroid(ecs::Entity* b);


	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
	// balas, y desactivar el sistema.
	void onRoundOver();


	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();

	float timeLastShot = 0.f;
	float fireRate = 0.f;

	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_ = false;

};
