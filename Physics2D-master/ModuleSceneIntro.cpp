#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "p2SString.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;


	// Music
	//App->audio->PlayMusic("pinball/Rhinoceros2.ogg", 0.0f);

	// Graphics
	graphics = App->textures->Load("pinball/Capture.png");
	bouncer1.texture = bouncer2.texture = bouncer3.texture = bouncer4.texture = bouncer5.texture = bouncer6.texture = bouncer7.texture = App->textures->Load("pinball/bouncerB.png");
	bouncer8.texture = App->textures->Load("pinball/rightBouncer.png");
	side_bouncer1.texture = App->textures->Load("pinball/left_bouncer_hit.png");
	side_bouncer2.texture = App->textures->Load("pinball/right_bouncer_hit.png");

	bouncer1.fx = bouncer2.fx = bouncer3.fx = bouncer4.fx = bouncer5.fx = bouncer6.fx = bouncer7.fx = App->audio->LoadFx("pinball/ding_short.wav");
	bouncer8.fx = bouncer9.fx = App->audio->LoadFx("pinball/ring.wav");
	
	
	/*
	player_lose_fx = App->audio->LoadFx("pinball/long_bonus.wav");
	*/


	LoadCollisionMap();

	bouncer1.body = App->physics->AddBody(110, 212, 34, b_static, 1.0f, 1.5f);
	bouncer1.body->listener = this;

	bouncer2.body = App->physics->AddBody(152, 293, 34, b_static, 1.0f, 1.5f);
	bouncer2.body->listener = this;

	bouncer3.body = App->physics->AddBody(116, 120, 34, b_static, 1.0f, 1.5f);
	bouncer3.body->listener = this;

	bouncer4.body = App->physics->AddBody(194, 120, 34, b_static, 1.0f, 1.5f);
	bouncer4.body->listener = this;

	bouncer5.body = App->physics->AddBody(272, 120, 34, b_static, 1.0f, 1.5f);
	bouncer5.body->listener = this;

	bouncer6.body = App->physics->AddBody(344, 120, 34, b_static, 1.0f, 1.5f);
	bouncer6.body->listener = this;

	bouncer7.body = App->physics->AddBody(317, 230, 34, b_static, 1.0f, 1.5f);
	bouncer7.body->listener = this;
	
	int bouncerSide1[10] = {
		29, 1,
		33, 3,
		4, 49,
		0, 46,
		27, 4
	};


	SDL_Rect bs1 = { 340, 482, 0, 0 };
	bouncer8.body = App->physics->AddBody(bs1, bouncerSide1, 10, b_static);


	int bouncerSide2[10] = {
		1, 3,
		34, 49,
		38, 45,
		5, 0,
		0, -2
	};

	SDL_Rect bs2 = { 125, 484, 0, 0 };
	bouncer9.body = App->physics->AddBody(bs2, bouncerSide2, 10, b_static);



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);
	App->textures->Unload(bouncer1.texture); // same as bouncer2.texture

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(graphics, 0, 0);

	if(bouncer1.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer1.hit_timer) == false)
			App->renderer->Blit(bouncer1.texture, 94, 193);
		else
			bouncer1.hit_timer = 0;
	}

	if(bouncer2.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer2.hit_timer) == false)
			App->renderer->Blit(bouncer2.texture, 136, 274);
		else
			bouncer2.hit_timer = 0;
	}

	if (bouncer3.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer3.hit_timer) == false)
			App->renderer->Blit(bouncer3.texture, 100, 101);
		else
			bouncer3.hit_timer = 0;
	}

	if (bouncer4.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer4.hit_timer) == false)
			App->renderer->Blit(bouncer4.texture, 178, 101);
		else
			bouncer4.hit_timer = 0;
	}

	if (bouncer5.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer5.hit_timer) == false)
			App->renderer->Blit(bouncer5.texture, 256, 101);
		else
			bouncer5.hit_timer = 0;
	}

	if (bouncer6.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer6.hit_timer) == false)
			App->renderer->Blit(bouncer6.texture, 328, 101);
		else
			bouncer6.hit_timer = 0;
	}
	if (bouncer7.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer7.hit_timer) == false)
			App->renderer->Blit(bouncer7.texture, 301, 211);
		else
			bouncer7.hit_timer = 0;
	}

	if (bouncer8.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer8.hit_timer) == false)
			App->renderer->Blit(bouncer8.texture, 301, 211);
		else
			bouncer8.hit_timer = 0;
	}

	if (bouncer9.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), bouncer9.hit_timer) == false)
			App->renderer->Blit(bouncer9.texture, 301, 211);
		else
			bouncer9.hit_timer = 0;
	}



	if(side_bouncer1.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), side_bouncer1.hit_timer) == false)
			App->renderer->Blit(side_bouncer1.texture, 84, 729);
		else
			side_bouncer1.hit_timer = 0;
	}

	if(side_bouncer2.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), side_bouncer2.hit_timer) == false)
			App->renderer->Blit(side_bouncer2.texture, 357, 729);
		else
			side_bouncer2.hit_timer = 0;
	}


	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(lights[i].on == true)
		{
			App->renderer->Blit(lights[i].texture, lights[i].x, lights[i].y);
		}
	}


	p2SString title("Lives: %d Score: %d Global Score: %d", App->player->lives,App->player->score, App->player->globalScore);//TODO GETTERS


	App->window->SetTitle(title.GetString()); 




	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* body1, PhysBody* body2)
{
	if(bouncer1.body == body1)
	{
		bouncer1.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer1.fx);
		App->player->score += 50;
		return;
	}
	
	if(bouncer2.body == body1)
	{
		bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer2.fx);
		return;
	}

	if (bouncer3.body == body1)
	{
		bouncer3.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer3.fx);
		App->player->score += 50;
		return;
	}

	if (bouncer4.body == body1)
	{
		bouncer4.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer4.fx);
		App->player->score += 50;
		return;
	}

	if (bouncer5.body == body1)
	{
		bouncer5.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer5.fx);
		App->player->score += 50;
		return;
	}

	if (bouncer6.body == body1)
	{
		bouncer6.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer6.fx);
		App->player->score += 50;
		return;
	}

	if (bouncer7.body == body1)
	{
		bouncer7.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer7.fx);
		App->player->score += 50;
		return;
	}

	if (bouncer8.body == body1)
	{
		bouncer8.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer8.fx);
		App->player->score += 100;
		return;
	}

	if (bouncer9.body == body1)
	{
		bouncer9.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer9.fx);
		App->player->score += 100;
		return;
	}


	if(side_bouncer1.body == body1)
	{
		side_bouncer1.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(side_bouncer1.fx);
		return;
	}

	if(side_bouncer2.body == body1)
	{
		side_bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(side_bouncer2.fx);
		return;
	}

	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(body1 == lights[i].body)
		{
			if(lights[i].on == false)
			{
				lights[i].on = true;
				App->audio->PlayFx(lights[i].fx);
			}
			return;
		}
	}

	if(player_lose == body1)
	{
		App->player->ball.body->SetLinearSpeed(0, 0);
		App->player->ball.body->SetAngularSpeed(0);
		App->player->ball.body->SetPosition(563, 582);
		App->audio->PlayFx(player_lose_fx);
		return;
	}
}

Light::Light(ModuleSceneIntro* scene, int x, int y, lightTypes type)
{
	this->type = type;
	this->x = x;
	this->y = y;

	int radius;

	switch(type)
	{
		case tiny:
			radius = 6;
			texture = scene->tex_light_tiny;
			fx = scene->fx_light_tiny;
			break;
		case medium:
			radius = 7;
			texture = scene->tex_light_medium;
			fx = scene->fx_light_medium;
			break;
		case big:
			radius = 11;
			texture = scene->tex_light_big;
			fx = scene->fx_light_big;
			break;
	}

	body = scene->App->physics->AddBody(x + radius, y + radius, radius * 2, b_static, 1.0f, 1.0f, false, true);
	body->listener = scene;
	on = false;
}

bool ModuleSceneIntro::LoadCollisionMap()
{

	//Create bottom
	
	
	//App->physics->AddBody({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5 }, b_static);
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

	App->physics->AddEdge({0,0,0,0}, OutestEdge, 152);


	int	tinyLauncherCube[8] = {
		472, 687,
		480, 687,
		480, 1895,
		472, 1895
	};


	
	App->physics->AddEdge({ 0, 0, 0, 0 }, tinyLauncherCube, 8);
	int tinyLauncherCube2[8] = {
		508, 687,
		497, 687,
		497, 1896,
		508, 1896
	};
	
	
	App->physics->AddEdge({ 0, 0, 0, 0 }, tinyLauncherCube2, 8);
	int rightWall[12] = {
		505, 122,
		505, 144,
		506, 686,
		506, 1760,
		514, 1760,
		514, 122
	};


	App->physics->AddEdge({ 0, 0, 0, 0 }, rightWall, 12);


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
	
	App->physics->AddEdge({ 0, 0, 0, 0 }, B_Obstacle_E, 24);
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


	App->physics->AddEdge({ 0, 0, 0, 0 }, B_Obstacle_E, 20);

	int R_Obstacle_Inner[14] = {
		335, 571,
		339, 580,
		413, 538,
		412, 454,
		403, 454,
		403, 532,
		342, 565
	};

	
	App->physics->AddEdge({ 0, 0, 0, 0 }, R_Obstacle_Inner, 14);

	int R_Obstacle_Outer[14] = {
		433, 422,
		442, 421,
		443, 577,
		315, 647,
		308, 635,
		432, 566,
		432, 431

	};

	
	App->physics->AddEdge({ 0, 0, 0, 0 }, R_Obstacle_Outer, 14);
	int R_Obstacle_Outest[10] = {
		325, 678,
		329, 687,
		465, 622,
		465, 611,
		333, 672
	};

	
	App->physics->AddEdge({ 0, 0, 0, 0 }, R_Obstacle_Outest, 10);

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

	
	App->physics->AddEdge({ 0, 0, 0, 0 }, L_Obstacle_Innest, 20);
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
	
	App->physics->AddEdge({ 0, 0, 0, 0 }, L_Obstacle_E, 24);
	int Left_bar[8] = {
		474, 376,
		474, 763,
		465, 763,
		465, 376
	};

	App->physics->AddEdge({ 0, 0, 0, 0 }, Left_bar, 8);
	
	//Obstacles
	int Obstacle_1[16] = {
		91, 123,
		91, 153,
		142, 153,
		142, 123,
		136, 123,
		136, 147,
		97, 147,
		97, 123
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_1, 16);

	int Obstacle_2[16] = {
		169, 122,
		169, 152,
		219, 152,
		219, 122,
		214, 122,
		214, 146,
		175, 146,
		175, 122
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_2, 16);

	int Obstacle_3[16] = {
		246, 123,
		246, 154,
		297, 154,
		297, 123,
		291, 123,
		291, 146,
		252, 146,
		252, 123
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_3, 16);

	int Obstacle_4[16] = {
		320, 121,
		320, 154,
		371, 154,
		371, 122,
		365, 122,
		365, 148,
		326, 148,
		326, 121
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_4, 16);

	int Obstacle_Aux[26] = {
		371, 144,
		423, 180,
		423, 249,
		416, 249,
		416, 189,
		403, 210,
		397, 206,
		413, 183,
		383, 163,
		367, 184,
		362, 181,
		378, 159,
		366, 150
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_Aux, 26);
	int Obstacle_Right[20] = {
		337, 522,
		332, 529,
		344, 537,
		382, 521,
		383, 473,
		366, 467,
		365, 474,
		374, 478,
		374, 516,
		347, 528
	};
	App->physics->AddEdge({ 0, 0, 0, 0 }, Obstacle_Right, 20);
	return ret;

}