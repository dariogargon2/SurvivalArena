#include "Enemy.hpp"
#include <cmath>


Enemy::Enemy(sf::Vector2f position)
{
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setPosition(position);
}

void Enemy::update(sf::Vector2f playerPosition, const std::vector<Enemy>& enemies, float deltaTime)
{
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f velocity(0.f, 0.f);

    sf::Vector2f direction = playerPosition - pos;
    float lenght = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (lenght > 0.001f)
    {
        direction /=lenght;
        velocity += direction * 80.f;
    }

    for (const auto& other : enemies)
    {
        if (&other == this) continue;
        
        sf::Vector2f diff = pos - other.getPosition();
        float dist = std::sqrt(diff.x * diff.x + diff.y+ diff.y);

        if (dist < 30.f && dist > 5.f)
        {
            diff /= dist;

            float force = 30.f - dist;

            if (force > 5.F)
            force = 5.f;

            velocity += diff * force;

        }        
    }

    float maxSpeed = 120.f;
    float vlen = std::sqrt(velocity.x * velocity.x + velocity.y + velocity.y);

    if(vlen > maxSpeed)
    {
        velocity /= vlen;
        velocity *= maxSpeed;
    }

    shape.move(velocity * deltaTime);
}

sf::Vector2f Enemy::getPosition() const
{
    return shape.getPosition();
}
float Enemy::getRadius() const
{
    return shape.getRadius();
}


void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}