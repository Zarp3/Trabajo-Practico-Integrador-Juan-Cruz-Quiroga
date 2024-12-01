#pragma once
#include <SFML/window.hpp>
#include <SFML/graphics.hpp>
#include <string>

using namespace sf;

class HUD {
private:
    Font font;
    Text textoVidas;
    Text textoEnemigos;
    Text textoPuntaje;

    int vidas;
    int enemigosMuertos;
    int puntaje;

public:
    
    HUD(const std::string& WesternCowboy, int vidasIniciales, int enemigosIniciales, int puntajeInicial)
        : vidas(vidasIniciales), enemigosMuertos(enemigosIniciales), puntaje(puntajeInicial)
    {
        
        if (!font.loadFromFile(WesternCowboy)) {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        textoVidas.setFont(font);  
        textoVidas.setCharacterSize(30);
        textoVidas.setString("Vidas: " + std::to_string(vidas));
        textoVidas.setFillColor(Color::White);
        textoVidas.setPosition(60, 500);

     
        textoEnemigos.setFont(font);  
        textoEnemigos.setCharacterSize(30);
        textoEnemigos.setString("Enemigos muertos: " + std::to_string(enemigosMuertos));
        textoEnemigos.setFillColor(Color::White);
        textoEnemigos.setPosition(250, 500);

        
        textoPuntaje.setFont(font);  
        textoPuntaje.setCharacterSize(30);
        textoPuntaje.setString("Puntaje: " + std::to_string(puntaje));
        textoPuntaje.setFillColor(Color::White);
        textoPuntaje.setPosition(750, 500);
       
        actualizarTextos();
    }

   
    void actualizarVidas(int nuevasVidas) {
        vidas = nuevasVidas;
        actualizarTextos();
    }

    void actualizarEnemigos(int nuevosEnemigos) {
        enemigosMuertos = nuevosEnemigos;
        actualizarTextos();
    }

    void actualizarPuntaje(int nuevoPuntaje) {
        puntaje = nuevoPuntaje;
        actualizarTextos();
    }

    
    void draw(RenderWindow& window) {
        window.draw(textoVidas);
        window.draw(textoEnemigos);
        window.draw(textoPuntaje);
    }

private:
    
    void actualizarTextos() {
        textoVidas.setString("Vidas: " + std::to_string(vidas));
        textoEnemigos.setString("Enemigos muertos: " + std::to_string(enemigosMuertos));
        textoPuntaje.setString("Puntaje: " + std::to_string(puntaje));
    }
};
