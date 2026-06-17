#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

bool freePosition(sf::Vector2f pos, const std::vector<Enemy>& enemies, float minDistance)
{
    for (const auto& enemy : enemies)
    {
        sf::Vector2f otherPos = enemy.getPosition();
        
        float dx = pos.x - otherPos.x;
        float dy = pos.y - otherPos.y;

        float distance = std::sqrt(dx * dx + dy * dy);
        if(distance < minDistance)
            return false;
    }
    
    return true;
}
float sideOfLine(sf::Vector2f A, sf::Vector2f B, sf::Vector2f P)
{
    return (B.x - A.x) * (P.y - A.y)
         - (B.y - A.y) * (P.x - A.x);
} 

int main()
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Survival Arena");

    sf::Texture pipi;
    if (!pipi.loadFromFile("../assets/pipi.png"))
    {
        std::cout << "error textura";
    }

    Player player(pipi);
    std::vector<Enemy> enemies;
 
    sf::Clock clock;
    sf::Clock spawnClock;

    bool paused = false;
    int score = 0;

    bool reset = false;

    sf::Font font;
    if (!font.openFromFile("../assets/OpenSans-Regular.ttf"))
    {
        return -1;
    }

    sf::Text healthTxt(font, "", 30);
    healthTxt.setPosition({10.f, 10.f});

    sf::Text GameOverTxt(font, "GAME OVER", 100);
    GameOverTxt.setPosition({150, 200});
    bool GameOver = false;

    sf::Text scoreTxt(font, "", 30);
    scoreTxt.setPosition({600  , 10});

    float passCooldown = 0.f;

     
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        if (passCooldown > 0.f)
            passCooldown -= deltaTime;

        while (auto event= window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
             window.close();
            }
            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf <sf::Event::KeyPressed>();
                if (key->code == sf::Keyboard::Key::Space)
                {
                    paused = !paused;
                } 
                if (key->code == sf::Keyboard::Key::R)
                {
                    score = 0;
                    GameOver = false;
                }                 
            }
        }  
        
        if (!GameOver && !paused)
        {
            sf::Vector2f prevPlayerpos = player.getPosition();

            player.update(deltaTime);

            sf::Vector2f currPlayerPos = player.getPosition();

            for (size_t i = 0; i < enemies.size(); i++)
            {
                for (size_t j = i * 1; j < enemies.size(); j++)
                {
                    sf::Vector2f A = enemies[i].getPosition();
                    sf::Vector2f B = enemies[j].getPosition();

                    float sideBefore = sideOfLine(A, B, prevPlayerpos);
                    float sideAfter = sideOfLine(A, B, currPlayerPos );
                    if (sideBefore * sideAfter < 0)
                    {
                        score += 10;
                        passCooldown = 0.7f;
                    }    
                }                
            }
            

            for (auto& Enemy : enemies)
            {
                Enemy.update(player.getPosition(), enemies, deltaTime);
            }

            if (spawnClock.getElapsedTime().asSeconds() > 5.f)
            {
                int side = rand() % 4;
                sf::Vector2f position;
                if(side==0)
                   position = sf::Vector2f(rand() % 800, 0.f);
                else if(side == 1)
                    position = sf::Vector2f(rand() % 800, 0.f);
                else if(side==2)
                    position = sf::Vector2f(0.f, rand() % 600);
                else
                    position = sf::Vector2f(800.f, rand() % 600);
                    
                bool valid = false;
                while (!valid)
                {
                    valid = freePosition(position, enemies, 50.f);
                    if (!valid)
                    {
                        int side = rand() % 4;
                        if (side == 0)
                            position = sf::Vector2f(rand() % 800, 0.f);
                        else if (side == 1)
                            position = sf::Vector2f(rand() % 800, 600.f);                            
                        else if (side == 2)
                            position = sf::Vector2f(0.f, rand() % 600);
                        else
                            position = sf::Vector2f(800.f, rand() % 600);                        
                    }
                }
                    enemies.push_back(Enemy(position));
                    score += 5;
                    spawnClock.restart();
            }
        
            for(auto& enemy : enemies)
            {
                enemy.update(player.getPosition(), enemies, deltaTime);
                sf::Vector2f diff = player.getPosition() - enemy.getPosition();
                float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                if (distance < player.getRadius() + enemy.getRadius())
                {
                    player.takeDamage();
                    if (player.getHealth() <= 0)
                    {
                    GameOver = true;
                    }
                }

                enemy.draw(window);
            }
            

            if (player.getHealth() <= 0)
            {
                GameOver = true;
            }                                                                                                                                                                                                                                                               
        }  

        window.clear();

        healthTxt.setString("Vidas: " + std::to_string(player.getHealth()));
        scoreTxt.setString("Puntos: " + sf::String(std::to_string(score)));

        for (auto& Enemy : enemies)
        {
            Enemy.draw(window);
        }

        window.draw(scoreTxt);

        player.draw(window);
        if (!GameOver)
        {
            window.draw(healthTxt);
        }

        if (GameOver)
        {
            window.draw(GameOverTxt);
        }
        
        window.display();
    }   
}