#pragma once
#include <SFML/window.hpp>
#include <SFML/graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Mira
{
private:
	Sprite Spritemira;
	Texture TexturaMira;
public:
	
	Mira(const string& mira) {

		if (!TexturaMira.loadFromFile("MiraPrincipal.png")) {
			cout << "Error al cargar la textura mira";
		}
		Spritemira.setTexture(TexturaMira);
		Spritemira.setOrigin(TexturaMira.getSize().x / 2, TexturaMira.getSize().y / 2);
		Spritemira.setScale(0.2f, 0.2f);
	}

	void Seguimiento(RenderWindow& window){
		
			int mouseX = Mouse::getPosition(window).x;
			int mouseY = Mouse::getPosition(window).y;

			Spritemira.setPosition(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	void draw(RenderWindow& window) {
		window.draw(Spritemira);	

	}

};