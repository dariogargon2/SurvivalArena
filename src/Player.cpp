#include "Player.hpp"
#include <cmath>

Player::Player(sf::Texture& texture)
    :sprite(texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(
        texture.getSize().x / 2.f,
        texture.getSize().y / 2.f
    ));

    sprite.setPosition(sf::Vector2f(400.f, 300.f));

    health = 3;
    damageCooldown = 0.f;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);

}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}
float Player::getRadius() const
{
    return 16.f;
}

void Player::update(float deltaTime)
{
    if (damageCooldown > 0.f)
    {
        damageCooldown -= deltaTime;
    }
    if (damageCooldown < 0.f)
    {
        damageCooldown = 0.f;
    }
    

    float speed = 250.f;
    sf::Vector2f direction = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        health = 3;
        sprite.setPosition(sf::Vector2f(400.f, 300.f));
    }

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length !=0.f)
    {
        direction / length;
    }

    sprite.move(direction * speed * deltaTime);

    sf::Vector2f pos = sprite.getPosition();
    float r = 16.f;

    pos.x = std::max(r, std::min(pos.x, 800.f - r));
    pos.y = std::max(r, std::min(pos.y, 600.f - r));

    sprite.setPosition(pos);
}

#include <iostream>
void Player::takeDamage()
{
    if (damageCooldown <= 0.f)
    {
        health--;
        std::cout<<"Vida: " << health << std::endl;
        damageCooldown = 1.f;
    }
    

}
int Player::getHealth() const
{
    return health;
}

