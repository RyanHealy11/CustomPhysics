#include "physics.h"
#include"raylib.h"

physObject::physObject()
{
	pos = { 0,0 };
	vel = { 0,0 };
	forces = { 0,0 };

	mass = 1.0f;
	drag = 1.0f;
}

void physObject::tickPhys(float delta)
{
	//integrating forces into velocity 
	vel += forces * delta;
	forces = { 0,0 };

	// integrate linear drag
	vel *= 1 - delta * drag;

	//integrating velocity into position
	pos += vel * delta;
}

void physObject::draw() const
{
	collider.match([this](Circle c) {DrawCircle(pos.x, pos.y, c.radius, SKYBLUE); },
		           [this](aabb a) {DrawRectangle(pos.x - a.halfExtents.x, pos.y - a.halfExtents.y, a.halfExtents.x * 2, a.halfExtents.y * 2, RED); });
	
	
}

void physObject::addForce(glm::vec2 force)
{
	forces += force * (1.0f / mass);
}

void physObject::addAcell(glm::vec2 acell)
{
	forces += acell;
}

void physObject::addImpulse(glm::vec2 impulse)
{
	vel += impulse * (1.0f * mass);
}

void physObject::addVelocityChange(glm::vec2 delta)
{
	vel += delta;
}
