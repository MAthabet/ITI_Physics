#include "AABBCollider.h"

AABBCollider::AABBCollider(Vector2d ul, Vector2d lr)
{
	this->ul = ul;
	this->lr = lr;
}

void AABBCollider::updatePosition(Vector2d position)
{
	ul += this->position - position;
	lr += this->position - position;
	this->position = position;
}

bool AABBCollider::checkCollision(AABBCollider* other)
{
    return !(ul.x > other->lr.x || ul.y > other->lr.y || lr.x < other->ul.x || lr.y < other->ul.y);
}
