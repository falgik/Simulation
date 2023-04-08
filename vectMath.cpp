#include "vectMath.h"

Vector2f toVector(Vector2f point1, Vector2f point2)
{
	return Vector2f(point2.x - point1.x, point2.y - point1.y);
}

float vectorLength(Vector2f point1, Vector2f point2)
{
	return sqrt(pow(toVector(point1, point2).x, 2) + pow(toVector(point1, point2).y, 2));
}

float vectorLength(Vector2f vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float getAng(Vector2f point1, Vector2f point2)
{
	return (atan2(point2.y - point1.y, point2.x - point1.x) * 180.f) / 3.14159265f;
}

Vector2f normalized(Vector2f point1, Vector2f point2)
{
	return toVector(point1, point2) / vectorLength(toVector(point1, point2));
}

Vector2f normalized(Vector2f vector)
{
	return vector / vectorLength(vector);
}

void toNorm(Vector2f& vector)
{
	float length = vectorLength(vector);
	if (length == 0.f || length == 1.f)
		return;
	vector /= vectorLength(vector);
}

Vector2f vectorFromAngle(const float angle, const float length)
{
	return Vector2f(cos(angle * 0.0174533), sin(angle * 0.0174533)) * length;
}

Vector2f vectorLerp(Vector2f a, Vector2f b, float t)
{
	return a + t * (b - a);
}

float ilerp(float a, float b, float t)
{
	return a + t * (b - a);
}