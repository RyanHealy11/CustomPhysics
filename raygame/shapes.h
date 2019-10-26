#pragma once
#include "glm/vec2.hpp"
#include "mapbox/variant.hpp"

struct Circle
{
	float radius;
};

struct aabb
{
	glm::vec2 halfExtents;
};

using shape = mapbox::util::variant<Circle, aabb>;

bool CheckCircleCircle(glm::vec2 posA, Circle circleA, glm::vec2 posB, Circle circleB);
bool CheckAABBAABB(glm::vec2 posA, aabb aabbA, glm::vec2 posB, aabb aabbB);
bool checkCircleAABB(glm::vec2 posA, Circle circ, glm::vec2 posB, aabb ab);

bool checkCircleX(glm::vec2 posA, Circle lhs, glm::vec2 posB, shape rhs);
bool checkAABBX(glm::vec2 posA, aabb lhs, glm::vec2 posB, shape rhs);

void resolvePhysBodies(class physObject& lhs, class physObject& rhs);

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
	                  glm::vec2 posB, glm::vec2 velB, float massB,
	                  float elasticity, glm::vec2 normal, glm::vec2*dst);