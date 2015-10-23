#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	pinball = App->textures->Load("pinball/Capture.png");
	
	

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

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
	//Create Flippers
	335; 586;
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}
	//mouseJointDef();

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = board.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(pinball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}


	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
