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

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> board;


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

/*Up(Little) Flipper

	int R_Up_flipper[20] = {
	337, 579,
	331, 580,
	309, 597,
	297, 607,
	293, 612,
	294, 614,
	320, 602,
	333, 596,
	339, 588,
	340, 582
};

Down(Little) Flipper
	int R_Down_flipper[18] = {
	314, 650,
	307, 650,
	297, 655,
	271, 676,
	257, 690,
	258, 693,
	306, 672,
	315, 661,
	317, 654
	};
*/
	//R_Up_Flipper coords;
	//335, 586
	/*R_Down_Flipper coords
	310, 657
	*/

	//Engranatge Center
	//236,237
	//Radi 26
};
