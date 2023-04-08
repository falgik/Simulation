#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "vectMath.h"

using namespace sf;


struct Bact
{
    Bact(Vector2f _pos, float _health)
    {
        speed =  1.f + (float)rand() / RAND_MAX;
        health = _health;
        pos = _pos;
    }
    Vector2f pos;
    Vector2f dir;
    float health;
    float speed;
};

struct Food
{
    Vector2f pos;
    Color color;
};


class Program
{
public:
    void init(Vector2u _mapSize)
    {
        font.loadFromFile("consola.ttf");
        text.setFont(font);
        text.setFillColor(Color(181, 181, 181, 127));
        text.setCharacterSize(16);

        bactCirc.setRadius(5);
        bactCirc.setPointCount(10);
        bactCirc.setFillColor(Color::Green);

        foodCirc.setRadius(2);
        foodCirc.setPointCount(5);
        foodCirc.setFillColor(Color::Cyan);

        mapSize = _mapSize;

        Bact temp(Vector2f(mapSize.x / 2, mapSize.y / 2),5);
        bacts.push_back(temp);

        max_food_cnt = 300;
        food_spawn_time = 50;

    }

    void update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            food_spawn_time += 10;
        }
        else if (food_spawn_time > 10 && Keyboard::isKeyPressed(Keyboard::Down))
        {
            food_spawn_time -= 10;
        }


        spawnFood();

        for (auto it = bacts.begin(); it != bacts.end(); )
        {
           
            if (!food.empty())
            {
                auto min = food.begin();
         
                for (auto jt = food.begin(); jt != food.end(); jt++ )
                    if (vectorLength(it->pos, jt->pos) < vectorLength(it->pos, min->pos))
                        min = jt;

                it->dir = normalized(it->pos, min->pos);

                if (vectorLength(it->pos, min->pos) < 5)
                {
                    food.erase(min);
                    it->health +=2;
                }

                if (it->health >= 10)
                {
                    bacts.push_back(Bact((*it).pos - (*it).dir * 5.f, (*it).health / 2));
                    (*it).health /= 2;
                }
            }

            it->pos += it->dir * it->speed;
            it->health -= 0.01;
            if (it->health <= 0.f)
                it = bacts.erase(it);
            else
                ++it;
        }
    }

    void draw(RenderWindow& window)
    {
     
        for (const auto& it : food)
        {
            foodCirc.setPosition(it.pos);
            foodCirc.setFillColor(it.color);
            window.draw(foodCirc);
        }

        for (const auto& it : bacts)
        {
            bactCirc.setPosition(it.pos);
            bactCirc.setFillColor(Color(250 - 25 * it.health, 25 * it.health, 0));
            window.draw(bactCirc);
        }

        text.setPosition(10, 0);
        text.setString(std::to_string(bacts.size()) + " pts");
        window.draw(text);

        text.setPosition(10, 15);
        text.setString(std::to_string(food_spawn_time) + " ms");
        window.draw(text);
    }

private:

    void spawnFood()
    {
        if (food.size() >= max_food_cnt)
            return;

        if (foodTm.getElapsedTime().asMilliseconds() > food_spawn_time)
        {
            foodTm.restart();

            Vector2f newPos(rand() % mapSize.x, rand() % mapSize.y);
            Color color(100 + rand() % 155, 100 + rand() % 155, 100 + rand() % 155);
            food.push_back({ newPos, color });
        }
    }
    
    CircleShape bactCirc;
    CircleShape foodCirc;
    RectangleShape btn;
    std::list<Bact> bacts;
    std::list<Food> food;
    Vector2u mapSize;
    Clock foodTm;
    Font font;
    Text text;
    int max_food_cnt;
    int food_spawn_time;
};