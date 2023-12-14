#include <SFML/Graphics.hpp>

int main() {
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Scroll Down Example");

    // Configuration de la vitesse de défilement
    float scrollSpeed = 100.0f; // pixels par seconde

    // Configuration des cases
    sf::RectangleShape box(sf::Vector2f(50, 50));
    box.setFillColor(sf::Color::Green);

    // Position initiale de la première case
    float currentY = -50.0f;

    // Utilisation de sf::Clock pour mesurer le temps entre les mises à jour
    sf::Clock clock;

    // Boucle principale
    while (window.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mise à jour du temps
        float deltaTime = clock.restart().asSeconds();

        // Mise à jour de la position des cases
        currentY += scrollSpeed * deltaTime;
        if (currentY > window.getSize().y) {
            // Réinitialiser la position si la case est en bas de la fenêtre
            currentY = -50.0f;
        }

        // Effacement de la fenêtre
        window.clear();

        // Dessin de la case
        box.setPosition(375, currentY); // Centre de la fenêtre en x
        window.draw(box);

        // Affichage de la fenêtre
        window.display();
    }

    return 0;
}
