#include "Plane.h"
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <iostream>

Plane::Plane(const glm::vec2& normal, const float distance, const glm::vec4& colour, const bool kinematic) :
	PhysicsObject(PLANE, colour, kinematic)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

Plane::~Plane()
{
}

void Plane::Debug()
{
	std::cout << "Plane normal x: " <<  m_normal.x << std::endl;
	std::cout << "Plane normal y: " << m_normal.y << std::endl;
}

void Plane::makeGizmo()
{
	// length of the line
	float lineSegmentLength = 300.0f;
	// center line location
	glm::vec2 centrePoint = m_normal * m_distanceToOrigin;
	//easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	// uses the direction of the parallel normal for the direction of the line
	glm::vec2 start = centrePoint + (parallel * lineSegmentLength);
	glm::vec2 end = centrePoint - (parallel * lineSegmentLength);
	// draws the line between the 2 positions and of the specified colour
	aie::Gizmos::add2DLine(start, end, m_colour);
}

void Plane::resolveCollision(RigidBody* actor2)
{
	float elasticity = 1;

	float j = glm::dot(-(1 + elasticity) * (actor2->GetVelocity()), m_normal) /
		(1 / actor2->GetMass());

	glm::vec2 force = m_normal * j;
	actor2->ApplyForce(force);
}