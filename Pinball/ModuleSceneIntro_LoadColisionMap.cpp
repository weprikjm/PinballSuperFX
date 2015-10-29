#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

bool ModuleSceneIntro::LoadCollisionMap()
{

	//Create bottom
	PhysBody* groundBox =App->physics->CreateRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5,-1);

	  //groundBox
//	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	bool ret = true;
	//Creating Pinball Table
	/*
	table = (App->physics->CreateChain(0, 0, table_array, SIZE));
	*/

	int OutestEdge[152] = {
		506, 143,
		498, 129,
		488, 119,
		476, 105,
		460, 89,
		440, 76,
		417, 64,
		398, 56,
		366, 46,
		339, 37,
		316, 35,
		293, 34,
		269, 33,
		254, 33,
		238, 33,
		218, 35,
		197, 38,
		178, 44,
		155, 49,
		134, 56,
		118, 64,
		101, 74,
		83, 85,
		70, 93,
		69, 101,
		69, 112,
		69, 121,
		69, 130,
		69, 141,
		69, 154,
		70, 164,
		70, 176,
		69, 199,
		68, 361,
		80, 369,
		77, 377,
		66, 369,
		36, 411,
		46, 419,
		42, 427,
		33, 420,
		33, 618,
		161, 694,
		162, 700,
		156, 701,
		147, 699,
		127, 683,
		93, 666,
		23, 624,
		23, 412,
		59, 361,
		59, 85,
		72, 76,
		90, 65,
		108, 57,
		124, 49,
		142, 43,
		157, 38,
		174, 34,
		192, 30,
		214, 27,
		235, 24,
		251, 23,
		262, 23,
		276, 23,
		290, 24,
		304, 24,
		346, 32,
		370, 36,
		401, 47,
		426, 59,
		450, 72,
		470, 87,
		487, 100,
		496, 112,
		506, 121
	};
	int x, y;

	x = 0;
	y = 0;

	board.add(App->physics->CreateChain(x, y, OutestEdge, 152));


	int	tinyLauncherCube[8] = {
		472, 687,
		480, 687,
		480, 695,
		472, 695
	};


	board.add(App->physics->CreateChain(x, y, tinyLauncherCube, 8));

	int tinyLauncherCube2[8] = {
		508, 687,
		497, 687,
		497, 696,
		508, 696
	};

	board.add(App->physics->CreateChain(x, y, tinyLauncherCube2, 8));

	int rightWall[12] = {
		505, 122,
		505, 144,
		506, 686,
		506, 760,
		514, 760,
		514, 122
	};

	board.add(App->physics->CreateChain(x, y, rightWall, 12));



	int B_Obstacle_E[24] = {
		56, 447,
		56, 576,
		56, 582,
		59, 585,
		170, 651,
		175, 651,
		176, 647,
		71, 585,
		63, 580,
		63, 446,
		62, 442,
		58, 442
	};
	App->physics->CreateChain(x, y, B_Obstacle_E, 24);

	int rightInnest[20] = {
		366, 467,
		362, 474,
		375, 479,
		374, 514,
		346, 528,
		336, 520,
		329, 528,
		341, 538,
		381, 521,
		382, 473
	};

	App->physics->CreateChain(x, y, rightInnest, 20);

	int R_Obstacle_Inner[14] = {
		335, 571,
		339, 580,
		413, 538,
		412, 454,
		403, 454,
		403, 532,
		342, 565
	};

	App->physics->CreateChain(x, y, R_Obstacle_Inner, 14);

	int R_Obstacle_Outer[14] = {
		433, 422,
		442, 421,
		443, 577,
		315, 647,
		308, 635,
		432, 566,
		432, 431

	};

	App->physics->CreateChain(x, y, R_Obstacle_Outer, 14);

	int R_Obstacle_Outest[10] = {
		325, 678,
		329, 687,
		465, 622,
		465, 611,
		333, 672
	};

	App->physics->CreateChain(x, y, R_Obstacle_Outest, 10);


	int L_Obstacle_Innest[20] = {
		134, 484,
		129, 476,
		118, 485,
		117, 528,
		161, 547,
		173, 533,
		167, 525,
		159, 536,
		125, 520,
		125, 491
	};

	App->physics->CreateChain(x, y, L_Obstacle_Innest, 20);

	int L_Obstacle_E[24] = {
		88, 473,
		88, 533,
		88, 542,
		89, 548,
		137, 584,
		142, 586,
		144, 581,
		102, 550,
		95, 545,
		95, 471,
		94, 467,
		89, 467
	};
	App->physics->CreateChain(x, y, L_Obstacle_E, 24);

	int Left_bar[8] = {
		474, 376,
		474, 763,
		465, 763,
		465, 376
	};
	App->physics->CreateChain(x, y, Left_bar, 8);




	//Flippers
	//Left Flipper



	int anchorLeftFlipper[8] = {
		144, 572,
		134, 585,
		145, 590,
		155, 577
	};



	int LeftFlipper[26] = {
		147, 575,
		141, 584,
		143, 589,
		147, 594,
		154, 598,
		163, 602,
		170, 604,
		178, 607,
		185, 609,
		191, 612,
		173, 593,
		163, 585,
		153, 579
	};

	b2Vec2 FlipperPosition; 
	b2Vec2 FlipperAnchorA;
	b2Vec2 FlipperAnchorB;

	FlipperPosition.Set(167,580);

	FlipperAnchorA.Set(167,585);
	FlipperAnchorB.Set(-12,-10);

	b2RevoluteJoint* LeftFlipperBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);
	
	FlipperPosition.Set(200, 650);

	FlipperAnchorA.Set(200, 650);
	FlipperAnchorB.Set(-15, -10);

	b2RevoluteJoint* LeftFlipperDownBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);

	FlipperPosition.Set(400, 580);

	FlipperAnchorA.Set(367, 585);
	FlipperAnchorB.Set(10, 10);

	//b2RevoluteJoint* RightFlipperBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);

	FlipperPosition.Set(200, 580);

	FlipperAnchorA.Set(167, 585);
	FlipperAnchorB.Set(10, 10);

	//b2RevoluteJoint* RightFlipperDownBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);


	//RightFlipper

	//Rotating Gear
	App->physics->CreateGear(237, 237, 26.0f);

	//Create Starting spring
	App->physics->CreateSpringBox(487, 702,9,20);

	return ret;

}
