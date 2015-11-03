#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	lives = 2;
	score = 0;
	globalScore = 0;


	ball.graphic = App->textures->Load("pinball/ball.png");
	flipper1.graphic = App->textures->Load("pinball/flipperLeft.png");
	flipper2.graphic = App->textures->Load("pinball/flipperRight.png");
	//flipper1.fx = flipper2.fx = App->audio->LoadFx("pinball/flipperLeft.wav");
	
	flipper_up1.graphic = App->textures->Load("pinball/flipperLeftBig.png");
	flipper_up2.graphic = App->textures->Load("pinball/flipperRightBig.png");
	
	spring.graphic = App->textures->Load("pinball/spring.png");
	//spring.fx = App->audio->LoadFx("pinballflipperLeft.wav");
	

	
	b2Vec2 ballPosInit;
	ballPosInit.y = 582;
	ballPosInit.x = 502;

	ball.body = App->physics->AddBody(ballPosInit.x, ballPosInit.y, 18, b_dynamic, 1.0f, 0.3f, true);
	ball.fx = App->audio->LoadFx("pinball/ball_bounce.wav");
	ball.body->listener = this;
	
	// Pivot 0, 0
	// Pivot -145, -579
	int flipperLeftU[12] = {
		2, 1,
		11, 3,
		46, 32,
		38, 31,
		13, 21,
		4, 14
	};
	SDL_Rect f1 = {138,592, 0, 0};

	flipper1.body = App->physics->AddBody(f1, flipperLeftU, 12, b_dynamic);
	flipper1_wheel = App->physics->AddBody(148, 587, 3, b_static);
	App->physics->CreateRevoluteJoint(flipper1.body, flipper1_wheel,  5, 5, 0, 0 , 60, 0);
	//flipper1.body->listener = this;



	// Pivot -178, -649
	int flipperLeftD[16] = {
		12, 2,
		25, 11,
		45, 26,
		63, 42,
		53, 40,
		26, 29,
		6, 17,
		4, 6
	};

	flipper_up1.body = App->physics->AddBody({ 192, 670, 0, 0}, flipperLeftD, 16, b_dynamic);
	flipper_up1_wheel = App->physics->AddBody(180, 653, 3, b_static);
	App->physics->CreateRevoluteJoint(flipper_up1.body, flipper_up1_wheel, 8, 7, 0, 0, 60, 0);

	 


	
	// Pivot 0, 0

	// Pivot -336, -578
	// Pivot -256, -649
	int flipperRightD[16] = {
		0, 42,
		28, 15,
		50, 1,
		59, 3,
		57, 13,
		49, 21,
		25, 32,
		6, 42
	};


	flipper_up2.body = App->physics->AddBody({ 250, 645, 0, 0 }, flipperRightD, 16, b_dynamic);
	flipper_up2_wheel = App->physics->AddBody(300, 645, 3, b_static);
	App->physics->CreateRevoluteJoint(flipper_up2.body, flipper_up2_wheel, 50, 0, 0, 0, 0, -60);






	int flipperRightU[14] = {
		36, 0,
		31, 11,
		5, 34,
		16, 31,
		37, 21,
		49, 13,
		53, 4
	};

	
	flipper2.body = App->physics->AddBody({ /*334*/334, 585, 0, 0 }, flipperRightU, 14, b_dynamic, 1.0f, 0.2f);
	flipper2_wheel = App->physics->AddBody(334, 585, 3, b_static);
	App->physics->CreateRevoluteJoint(flipper2.body, flipper2_wheel, 50, 0, 0, 0, 0, -60);
	
	
	
	



	/*
	
	
	
	
	
	*/
	
	
	
	
	

	
	
	
	
	/*
	
	int Capture[4] = {
		482, 697,
		496, 697
	};

	*/
	
	spring.body = App->physics->AddBody({486, 900, 15, 65}, b_dynamic);
	spring_wheel = App->physics->AddBody(476, 650, 10, b_static);
	App->physics->CreateLineJoint(spring.body, spring_wheel, 0, 0, 0, 0, 20.0f, 1.0f);
	
	metalGear.body->App->physics->AddBody()



	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;

	App->textures->Unload(ball.graphic);
	App->textures->Unload(flipper1.graphic);
	App->textures->Unload(flipper2.graphic);
	App->textures->Unload(flipper_up1.graphic);
	App->textures->Unload(flipper_up2.graphic);

	App->physics->DestroyBody(ball.body);
	App->physics->DestroyBody(flipper1.body);
	App->physics->DestroyBody(flipper2.body);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	static float spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		ball.body->Push(0.0f, -400.0f);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->audio->PlayFx(flipper1.fx);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper1.body->Turn(-360);
		flipper_up1.body->Turn(-360);
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper2.body->Turn(360);
		flipper_up2.body->Turn(360);
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring_push += 175.0f;
		spring.body->Push(0, spring_push);
	}
	else
		spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		App->audio->PlayFx(spring.fx);
	}

	int x, y;


//, ball.body->GetAngle());

	ballBlit();

	flipper1.body->GetPosition(x, y);
	App->renderer->Blit(flipper1.graphic, x , y, NULL, 1.0f, flipper1.body->GetAngle(), 0, 0);
	
	flipper2.body->GetPosition(x, y);
	App->renderer->Blit(flipper2.graphic, x, y, NULL, 1.0f, flipper2.body->GetAngle(), 0, 0);
	
	flipper_up1.body->GetPosition(x, y);
	App->renderer->Blit(flipper_up1.graphic, x, y, NULL, 1.0f, flipper_up1.body->GetAngle(), 0, 0);
	
	flipper_up2.body->GetPosition(x, y);
	App->renderer->Blit(flipper_up2.graphic, x, y, NULL, 1.0f, flipper_up2.body->GetAngle(), 0, 0);
	
	spring.body->GetPosition(x, y);
	App->renderer->Blit(spring.graphic, x, y, NULL, 1.0f, spring.body->GetAngle());
	
	return UPDATE_CONTINUE;
}


void ModulePlayer::ballBlit()
{

	int x, y;

	ball.body->GetPosition(x, y);
	//this->ballPosInit.x;
	//this->ballPosInit.y;
	if (y > 900)
	{
		ball.body->SetPosition(502, 582);
		x = 598;
		y = 575;
		App->audio->PlayFx(spring.fx);
		lives--;
	}
	App->renderer->Blit(ball.graphic, x, y, NULL, 1.0f);

}
