#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

Vector2f toVector(Vector2f point1, Vector2f point2);

float vectorLength(Vector2f point1, Vector2f point2);

float vectorLength(Vector2f vector);

float getAng(Vector2f point1, Vector2f point2);

Vector2f normalized(Vector2f point1, Vector2f point2);

Vector2f normalized(Vector2f vector);

void toNorm(Vector2f& vector);

Vector2f vectorFromAngle(const float angle, const float length);

Vector2f vectorLerp(Vector2f a, Vector2f b, float t);

float ilerp(float a, float b, float t);