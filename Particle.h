#pragma once
#include "Vector2d.h"
#include "Collider.h"
#include "AABBCollider.h"
#include "SATCollider.h"

class Particle
{
	//just uncomment the collider type you want to use
public:
	Vector2d postion;
	Vector2d velocity;
	Vector2d acceleration;
	Vector2d forces;
	//Collider* collider;
	//AABBCollider* collider;
	SATCollider* collider;

	float mass;
	float drag;

	Particle(Vector2d postion, float mass = 1, float drag = 0.3f);
	void Update(float dt);
	void addForce(Vector2d force);
};