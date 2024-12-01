#pragma once
#include <SFML/window.hpp>
#include <SFML/graphics.hpp>
#include <string>
#include <vector>
using namespace sf;

class Personajes
{
private:

	Sprite spriteIzq;
	Sprite spriteDer;
	float velocidad;
	bool haciaDer;
	bool haciaIzq;
	bool esEnemigo;

public:
	
	Personajes(Texture& texturaIzq, float velocidadinicial, bool haciaizq, bool enemigo, Texture& texturaDer, bool haciaDerecha) :
		haciaIzq(haciaizq), haciaDer(haciaDerecha), velocidad(velocidadinicial), esEnemigo(enemigo) {

		spriteIzq.setTexture(texturaIzq);
		spriteDer.setTexture(texturaDer);

		if (haciaIzq) {
			spriteIzq.setPosition(-50, 320);
		} else {
			spriteIzq.setPosition(900, 320);
		}
		spriteIzq.setScale(0.3, 0.3);
	}


	void mover() {
		if (haciaIzq) {
			spriteIzq.move(velocidad, 0);
		} else {
			spriteIzq.move(-velocidad, 0);
		}
	}

	void draw(RenderWindow& window) {
		window.draw(spriteIzq);
	}

	bool Fueradelapantalla() {

		if (haciaIzq) {
			return spriteIzq.getPosition().x > 600;
		} else {
			return spriteIzq.getPosition().x < -100;
		}
	}

	bool esUnEnemigo(){
		return esEnemigo;
	}

	bool fueImpactado(const Vector2f& posicionDisparo) const {
		return spriteIzq.getGlobalBounds().contains(posicionDisparo);
	}

};