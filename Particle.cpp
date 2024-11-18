#include "Particle.h"

Particle::Particle(Vector2d postion, float mass, float drag)
{
	this->postion = postion;
	this->velocity = this->forces = this->acceleration = Vector2d(0, 0);
	this->mass = mass;
	this->drag = drag;
}

void Particle::Update(float dt)
{
	this->acceleration = this->forces / this->mass;
	this->velocity += this->acceleration * dt;
	this->postion += this->velocity * dt;
	collider->updatePosition(this->postion);
}

void Particle::addForce(Vector2d force)
{
	this->forces += force;
}
