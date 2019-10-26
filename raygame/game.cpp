#pragma once
#include "game.h"
#include "raylib.h"
#include <iostream>

game::game() 
{
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;

}


void game::init()
{		
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);	
}

void game::tick()
{
	accumulatedFixedTime += GetFrameTime();

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1) 
	{
		physObjects.emplace_back();
		//std::cout << "added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousPos = GetMousePosition();
		babyPhys.pos = { mousPos.x,mousPos.y };
		//babyPhys.addForce({ 100,0 });

		if (mb0)
		{
			babyPhys.collider = Circle{ 15.0f };
		}
		else 
		{
			babyPhys.collider = aabb{ {15,15} };
		}

	}
}


void game::tickPhys()
{
	accumulatedFixedTime -= targetFixedStep;

	//std::cout << "phys Tick" << std::endl;

	for (auto& i : physObjects) 
	{
		i.tickPhys(targetFixedStep);
	}

	for (auto &i : physObjects) 
	{
		for (auto &j : physObjects)
			{
			//skiping self collision
			if (&i == &j) {continue;}

			bool collision = false;

			i.collider.match([i, j, &collision](Circle c) {if (checkCircleX(i.pos, c, j.pos, j.collider)) { collision = true; }},
				[i, j, &collision](aabb a) {if (checkAABBX(i.pos, a, j.pos, j.collider)) { collision = true; }});

			if (collision) { resolvePhysBodies(i, j); }
			}
	}
}

void game::draw() const
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	for (const auto& i : physObjects) 
	{
		i.draw();
	}

	EndDrawing();
}

void game::exit()
{
	CloseWindow();
}

bool game::shouldClose() const
{
	return WindowShouldClose();
}

bool game::shouldPhysics() const
{
	return accumulatedFixedTime >= targetFixedStep;
}
