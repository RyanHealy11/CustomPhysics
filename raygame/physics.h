#pragma once
#include "glm/vec2.hpp"
#include "shapes.h"

class physObject 
{
public:
	glm::vec2 pos;
	glm::vec2 vel;

	glm::vec2 forces;

	physObject();

	float mass;
	float drag;

	shape collider;

	void tickPhys(float delta);
	void draw() const;

	//add a continuous force with respect to mass
	void addForce(glm::vec2 force);
	//adds an instantaneous force with respect to mass
	void addImpulse(glm::vec2 impulse);
	//accelerates the object without respect to the mass
	void addAcell(glm::vec2 acell);
	//adds an instantaneous force without respect to mass
	void addVelocityChange(glm::vec2 delta);

};