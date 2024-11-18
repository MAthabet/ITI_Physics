#include "SATCollider.h"

SATCollider::SATCollider(vector<Vector2d> points)
{
	this->points = points;
}

void SATCollider::updatePosition(Vector2d position)
{
	int size = points.size();
	for (int i =0; i < size ;i++)
	{
		points[i].x += (position.x - this->position.x);
		points[i].y += (position.y - this->position.y);
	}
	this->position = position;
}

bool SATCollider::checkCollision(SATCollider* other)
{
	std::vector<Vector2d> axis = getNormals();
	std::vector<Vector2d> otherAxis = other->getNormals();

	//insert all normals in one array to minimize coding
	axis.insert(axis.end(), otherAxis.begin(), otherAxis.end());
	for (const auto& axis : axis) 
	{
		Vector2d projectionA = projectShape(axis);
		Vector2d projectionB = other->projectShape(axis);

		if (projectionA.y < projectionB.x || projectionB.y < projectionA.x) 
			return false;
	}
	return true;
}

vector<Vector2d> SATCollider::getNormals()
{
	vector<Vector2d> normals;
	int size = points.size();
	for (size_t i = 0; i < size-1; i++) {
		Vector2d edge = points[i + 1] - points[i];
		Vector2d normal = Vector2d(-edge.y, edge.x);
		normals.push_back(normal);
	}
	Vector2d edge = points[size-1] - points[0];
	Vector2d normal = Vector2d(-edge.y, edge.x);
	normals.push_back(normal);

	return normals;
}

Vector2d SATCollider::projectShape(Vector2d axis)
{
	float min = axis * points[0];
	float max = min;

	for (const auto& point : points) {
		float projection = axis * point;
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}

	return Vector2d(min , max);
}
