#pragma once
#include <SFML/Graphics.hpp>
class Player 
{
    public:
        Player(sf::Texture& texture);
        void draw(sf::RenderWindow& window);
        void update(float deltaTime);

        sf::Vector2f getPosition() const;
        float getRadius() const;

        void takeDamage();
        int getHealth() const;

    private:
        sf::Sprite sprite;
        int health;
        float damageCooldown;
}; 