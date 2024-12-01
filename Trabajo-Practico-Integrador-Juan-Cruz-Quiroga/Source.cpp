#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mira.h"
#include "Hud.h"
#include "Personaje.h"
#include "ctime"
#include "Ovni.h"

using namespace std;
using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(960, 540), "Juego con Mira Clase");
    window.setMouseCursorVisible(false);

    Texture TexturaEnemigoDer, TexturaAliadoDer, TexturaInicio, TexturaFondo, TexturaenemigoIzq, TexturaAliadoIzq, TexturaOvni, TexturaGameOver, TexturaVictoria;

    if (!TexturaEnemigoDer.loadFromFile("Enemigo.png") ||
        !TexturaenemigoIzq.loadFromFile("Enemigo.png") ||
        !TexturaAliadoIzq.loadFromFile("Aliado.png") ||
        !TexturaAliadoDer.loadFromFile("Aliado.png") ||
        !TexturaOvni.loadFromFile("EnemigoDisparo.png") ||
        !TexturaGameOver.loadFromFile("GameOver.png") ||
        !TexturaVictoria.loadFromFile("Victoria.png") ||
        !TexturaInicio.loadFromFile("inicio.png") ||
        !TexturaFondo.loadFromFile("fondo.png")) {
        cerr << "Error al cargar texturas" << endl;
        return -1;
    }

    Sprite SpriterInicio(TexturaInicio);
    Sprite SpriterFondo(TexturaFondo);
    Sprite SpriterGameOver(TexturaGameOver);
    Sprite SpriteVictoria(TexturaVictoria);


    Mira mira("MiraPrincipal.png");

    int currentScreen = 0;
    int vidas = 3;
    int puntaje = 0;
    int EnemigosM = 0;

    Clock relojPersonajes;
    vector<Personajes> personajes;
    vector<Ovni> EnemigosOvni;


    HUD hud("WesternCowboy.ttf", vidas, puntaje, 0);


    while (window.isOpen()) {
        Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == Event::Closed) {
                window.close();
            }
            if (evento.type == Event::MouseButtonPressed && evento.mouseButton.button == Mouse::Left) {
                if (currentScreen == 0) {
                    currentScreen = 1;
                }
            }
            if (vidas <= 0) {
                currentScreen = 3;
                if (evento.type == sf::Event::Closed)
                    window.close();

                if (evento.type == sf::Event::KeyPressed)
                {
                    if (evento.key.code == sf::Keyboard::Escape)
                        window.close();
                }
            }
            if (puntaje >= 10) {
                currentScreen = 4;
                if (evento.type == sf::Event::Closed)
                    window.close();

                if (evento.type == sf::Event::KeyPressed)
                {
                    if (evento.key.code == sf::Keyboard::Escape)
                        window.close();
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2f posicionDisparo = window.mapPixelToCoords(Mouse::getPosition(window));
            for (auto pj = personajes.begin(); pj != personajes.end();) {
                if (pj->fueImpactado(posicionDisparo)) {
                    if (pj->esUnEnemigo()) {
                        puntaje++;
                        EnemigosM++;
                        hud.actualizarPuntaje(puntaje);
                        hud.actualizarEnemigos(EnemigosM);
                    }
                    else {
                        vidas--;
                        puntaje--;
                        hud.actualizarVidas(vidas);
                    }
                    pj = personajes.erase(pj);
                    hud.actualizarPuntaje(puntaje);
                }
                else {
                    ++pj;
                }
            }
            for (auto ov = EnemigosOvni.begin(); ov != EnemigosOvni.end();) {
                if (ov->fueImpactado(posicionDisparo)) {
                    puntaje++;
                    hud.actualizarPuntaje(puntaje);
                    ov = EnemigosOvni.erase(ov);
                }
                else {
                    ++ov;
                }
            }

        }

        
        if (relojPersonajes.getElapsedTime().asSeconds() > 2.0f) {
            bool haciaDerecha = 1;
            bool esEnemigo = rand() % 2;
            float velocidad = 0.1f;

            if (esEnemigo) {
                personajes.emplace_back(TexturaenemigoIzq, velocidad, !haciaDerecha, true, TexturaenemigoIzq, haciaDerecha);

            }
            else {
                personajes.emplace_back(TexturaAliadoIzq, velocidad, !haciaDerecha, false, TexturaAliadoIzq, haciaDerecha);
            }

            EnemigosOvni.emplace_back(TexturaOvni, 0.0);
            std::cout << "Se ha creado un nuevo Ovni." << std::endl;

            relojPersonajes.restart();
        }

        for (auto ps = personajes.begin(); ps != personajes.end();) {
            ps->mover();
            if (ps->Fueradelapantalla()) {
                if (ps->esUnEnemigo()) {
                    EnemigosM++;
                    hud.actualizarEnemigos(EnemigosM);
                }
                ps = personajes.erase(ps);
            }
            else {
                ++ps;
            }
        }

        for (auto& ovni : EnemigosOvni) {
            ovni.mover();
            if (ovni.listoParaDisparar()) {
                ovni.disparar(vidas, hud);
            }
        }

        mira.Seguimiento(window);

        window.clear();

        if (currentScreen == 0) {
            window.draw(SpriterInicio);
        }
        else if (currentScreen == 1) {
            window.draw(SpriterFondo);
            for (auto& pj : personajes) {
                pj.draw(window);
            }

            for (auto& ovni : EnemigosOvni) {
                ovni.draw(window);
            }
            hud.draw(window);
        }else if (currentScreen == 3) {
            window.draw(SpriterGameOver);
        }
        else if (currentScreen == 4) {
            window.draw(SpriteVictoria);
        }
        
        if (puntaje >= 10) {
            currentScreen = 4;
        }

        mira.draw(window);
        window.display();

        
    }

    return 0;
}