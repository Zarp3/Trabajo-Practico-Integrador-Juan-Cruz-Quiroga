#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mira.h"
#include "Hud.h"
#include "Personaje.h"
#include "ctime"

class Ovni {
private:
    Sprite sprite;
    float velocidad;
    Clock relojDisparo;
    bool puedeDisparar;

public:
    Ovni(Texture& textura, float velocidadInicial) : velocidad(velocidadInicial), puedeDisparar(false) {
        sprite.setTexture(textura);
        sprite.setPosition(rand() % 800 + 80, 100);
        sprite.setScale(0.2f, 0.2f); 
    }

    void mover() {
        sprite.move(0, velocidad);
        if (sprite.getPosition().y > 300) {
            sprite.setPosition(rand() % 800 + 80, 150);
            puedeDisparar = false;
            relojDisparo.restart();
        }
    }

    bool listoParaDisparar() {
        if (!puedeDisparar && relojDisparo.getElapsedTime().asSeconds() > 3) {
            puedeDisparar = true;
        }
        return puedeDisparar;
    }

    void disparar(int& vidas, HUD& hud) {
        if (puedeDisparar) {
            vidas--; 
            hud.actualizarVidas(vidas); 
            puedeDisparar = false;
            relojDisparo.restart();
        }
    }

    bool fueImpactado(const Vector2f& posicionDisparo) {
        return sprite.getGlobalBounds().contains(posicionDisparo);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};