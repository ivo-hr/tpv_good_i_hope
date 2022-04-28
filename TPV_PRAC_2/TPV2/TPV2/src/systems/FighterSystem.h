#pragma once
#include "../game/System.h"

class Texture;

class Transform;

class FighterSystem : public ecs::System {
public:

	constexpr static ecs::sysId_type id = ecs::_sys_FIGHTER;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;


	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;


	// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc).
	void update() override;

	int maxHealth = 3;
	int health = maxHealth;

	Texture* getHearts() { return hearts; };

private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotación 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego está parado).
	void onCollision_FighterAsteroid();


	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();


	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();


	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_ = false;

	Texture* hearts = nullptr;
	Transform* fghtrTR = nullptr;
};
