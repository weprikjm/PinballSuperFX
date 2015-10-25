#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool LoadCollisionMap();
public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> board;
	p2List<PhysBody*> flippers;


	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* pinball;




	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	//Pinball Objects
	 //int table_vertex[];
	PhysBody* table;

	//R_Up_Flipper coords;
	//335, 586
	/*R_Down_Flipper coords
	310, 657
	*/


};
