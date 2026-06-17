#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Enemy
{
    public:
        Enemy(sf::Vector2f position);

        void update(sf::Vector2f playerPosition, const std::vector<Enemy>& enemies, float deltaTime);
        void draw(sf::RenderWindow& window);

        sf::Vector2f getPosition() const;
        float getRadius() const;

    private:
        sf::CircleShape shape;
};