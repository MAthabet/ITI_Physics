#include "PhysicsWorld.h"

void PhysicsWorld::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

void PhysicsWorld::Update(float deltaTime)
{
	int size = particles.size();
	for (int i = 0; i < size; i++) 
	{
		particles[i]->Update(deltaTime);
		for (int j = i + 1; j < size; j++)
		{
			if (particles[i]->collider->checkCollision(particles[j]->collider))
			{
				printf("Collided");
				elasticCollision(particles[i], particles[j]);
			}
		}
	}
}
// m1v1 + m2v2 = m'1v'1 + m'2v'2
// v'1 = m1-m2/mt v1 + 2 m2/mt v2
// v'2 = m2-m1/mt v2 + 2 m1/mt v1
void elasticCollision(Particle* i, Particle* j)
{
	Vector2d v1 = i->velocity;
	Vector2d v2 = j->velocity;
	i->velocity = ecFinalVelocity(v1, i->mass, v2, j->mass);
	j->velocity = ecFinalVelocity(v2, j->mass, v1, i->mass);
	printf("Vx = %f  Vy = %f\n", i->velocity.x, i->velocity.y);
	printf("Vx = %f  Vy = %f\n", j->velocity.x, j->velocity.y);
}
// final velocity afetr elastic collision
Vector2d ecFinalVelocity(Vector2d vself,const float& mself,Vector2d vother,const float& mother)
{
	float mt = mself + mother;
	return vself * ((mself - mother) / mt) + vother * (2 * mother / mt);
}