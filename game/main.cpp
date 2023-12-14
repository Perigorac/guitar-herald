#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1220,720), "SFML Background Layers Example");

    // Chargement des images de fond
    sf::Texture backgroundTexture1;
    if (!backgroundTexture1.loadFromFile("./assets/DelphiTheatre.jpg")) {
        std::cerr << "Erreur lors du chargement de l'image de fond 1" << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("./assets/SekilosUnstroked.png")) {
        std::cerr << "Erreur lors du chargement de l'image de fond 2" << std::endl;
        return 1;
    }

    // Création des sprites pour les images de fond
    sf::Sprite backgroundSprite1(backgroundTexture1);
    backgroundSprite1.setScale(static_cast<float>(window.getSize().x) / backgroundTexture1.getSize().x,
                               static_cast<float>(window.getSize().y) / backgroundTexture1.getSize().y);

    sf::Sprite backgroundSprite2(backgroundTexture2);
    backgroundSprite2.setScale(static_cast<float>(window.getSize().x) / backgroundTexture2.getSize().x,
                               static_cast<float>(window.getSize().y) / backgroundTexture2.getSize().y);

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

        // Dessin du premier fond
        window.draw(backgroundSprite1);

        // Dessin du deuxième fond
        window.draw(backgroundSprite2);

        // Dessin de la case
        box.setPosition(375, currentY); // Centre de la fenêtre en x
        window.draw(box);

        // Affichage de la fenêtre
        window.display();
    }

    return 0;
}
