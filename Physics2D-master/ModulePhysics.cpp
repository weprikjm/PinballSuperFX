#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
	#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
	#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

// Called before render is available
bool ModulePhysics::Init()
{
	//LOG("Creating Physics environment");
	bool ret = true;

	return ret;
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics environment");

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	b2BodyDef test;
	ground = world->CreateBody(&test);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world->Step(timeStep, velocityIterations, positionIterations);

	// Check for collisions on sensors (collision listener does not work for sensors)
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	b2Vec2 mouse_position;

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;
	// get center
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		uint8 green = b->GetType() == b2BodyType::b2_staticBody ? 255 : 0;
		uint8 blue = b->GetType() == b2BodyType::b2_kinematicBody ? 255 : 0;
		
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();

					int32 count = polygonShape->GetVertexCount();

					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));

						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));

					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);
				}
				break;

				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, green, blue);
				}
				break;

				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);

						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);

						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);

					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);
				}
				break;

				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 255, green, blue);
				}
				break;
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
				mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());
				if (f->GetShape()->TestPoint(b->GetTransform(), mouse_position) == true)
				{
					body_clicked = f->GetBody();
				}
			}
				

		}
	}

	if (body_clicked != NULL && body_clicked->GetType() != b2_kinematicBody)
	{
	
		b2MouseJointDef def;
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
		{
			char debug = 'a';
		}
		
		def.bodyA = ground;
		def.bodyB = body_clicked;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 1.250f;
		def.maxForce = 25.0f * body_clicked->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	
		body_clicked = NULL;
		// TODO 3: If the player keeps pressing the mouse button, update
		// target position and draw a red line between both anchor points
	}
	int wat = App->input->GetMouseButton(SDL_BUTTON_LEFT);
	if (mouse_joint != NULL && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
	

		/*def.target.x = PIXEL_TO_METERS(App->input->GetMouseX());
		def.target.y = PIXEL_TO_METERS(App->input->GetMouseY());*/
		b2Vec2 pos_A, pos_B;
		pos_A = mouse_joint->GetAnchorB();
		pos_B.x = PIXEL_TO_METERS(App->input->GetMouseX());
		pos_B.y = PIXEL_TO_METERS(App->input->GetMouseY());
		
		mouse_joint->SetTarget(pos_B);

		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
		{
			char debug = 'a';
		}
		App->renderer->DrawLine(METERS_TO_PIXELS(pos_A.x),	METERS_TO_PIXELS(pos_A.y),METERS_TO_PIXELS(pos_B.x),	METERS_TO_PIXELS(pos_B.y),255, 0, 0);
	}

	if (mouse_joint != NULL && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_IDLE)
	{
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{
			char debug = 'a';
		}

		world->DestroyJoint(mouse_joint);
		mouse_joint = NULL;
	}
	return UPDATE_CONTINUE;
}
/*if (App->input->GetMouseButton(SDL_BUTTON_LEFT) != KEY_REPEAT body_clicked != NULL)
{
world->DestroyJoint(mouse_joint);
mouse_joint = NULL;
body_clicked = NULL;
}*/
// TODO 4: If the player releases the mouse button, destroy the joint
/*if (App->input->GetMouseButton(SDL_BUTTON_LEFT) != KEY_DOWN)
{
delete(mouse_joint);
body_clicked = NULL;
}*/

update_status ModulePhysics::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	p2List_item<PhysBody*>* item = bodies.getFirst();

	while(item != NULL)
	{
		delete item->data;
		item = item->next;
	}

	bodies.clear();

	// Delete the whole physics world!
	delete world;

	return true;
}

//
PhysBody* ModulePhysics::AddBody(const SDL_Rect& rect, body_type type, float density, float restitution, bool ccd, bool isSensor)
{
	b2BodyDef body;
	
	switch(type)
	{
		case b_static:
			body.type = b2_staticBody;
			break;

		case b_kinematic:
			body.type = b2_kinematicBody;
			break;

		default:
			body.type = b2_dynamicBody;
			break;
	}

	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;
	body.bullet = ccd;

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(PIXEL_TO_METERS(rect.w/2), PIXEL_TO_METERS(rect.h/2));

	b2FixtureDef box_fixture;
	box_fixture.shape = &box_shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, rect, type);
	bodies.add(ret);

	b->SetUserData(ret);

	return ret;
}


/*

b2Vec2* ModulePhysics::CreateGearBoxes(const int* _array, b2Vec2* & toFill)
{
	b2Vec2 ret[4];
	if (_array)
	{
		
		
	}

	return NULL;

}*/
b2Body* ModulePhysics::CreateGear(float density, float restitution, bool isSensor)
{
	
	/*
	Crear els bodies i la rotation(o gear) joint
	*/

	//
	//x:237 y:237: radius:26.0f
	//Create Gear squares
	
	b2BodyDef body_circle;
	b2Body* circle_b;


	// Create sphere
	int x = 237;
	int y = 237;
		
	body_circle.type = b2_dynamicBody;
	body_circle.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2CircleShape circleShape;
	circleShape.m_radius = PIXEL_TO_METERS(26.0f);
	
	
	b2FixtureDef circleFix;
	circleFix.shape = &circleShape;
	circleFix.density = 1.0f;

	circle_b = world->CreateBody(&body_circle);
	circle_b->CreateFixture(&circleFix);
	circle_b->SetGravityScale(0.0f);

	//Create boxes
	b2FixtureDef boxFix;

	b2PolygonShape box1;
	//237-204 = 33
	box1.SetAsBox(PIXEL_TO_METERS(5), PIXEL_TO_METERS(8), { 0, PIXEL_TO_METERS(33) }, 0);
	
	boxFix.shape = &box1;
	boxFix.density = 1.0f;

	circle_b->CreateFixture(&boxFix);
	

	//Create Pin
	b2BodyDef body_pin;
	b2Body* pin_b;
	body_pin.type = b2_staticBody;
	int x_g = x - 15;
	int y_g = y - 60;
	body_pin.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	pin_b = world->CreateBody(&body_pin);

	b2PolygonShape pinBox;
	pinBox.SetAsBox(PIXEL_TO_METERS(5), PIXEL_TO_METERS(5));

	b2FixtureDef fixture_g;
	fixture_g.shape = &pinBox;
	fixture_g.density = 1.0f;

	pin_b->CreateFixture(&fixture_g);

	b2RevoluteJointDef jointDef;
	jointDef.bodyB = circle_b;
	jointDef.bodyA = pin_b;
	jointDef.Initialize(circle_b, pin_b, pin_b->GetWorldCenter());
	jointDef.collideConnected = false;

	//jointDef.enableLimit = true;
	jointDef.maxMotorTorque = 0.1f;
	jointDef.motorSpeed = 0.0f;
	jointDef.enableMotor = true;

	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	return circle_b;

}



/*
 p2DynArray <int *> boxCoords;
 int Box1[8] = {
 240, 199,
 233, 199,
 233, 211,
 241, 211
 };
 boxCoords.PushBack(Box1);
 int Box2[8]
 {
 221, 216,
 211, 207,
 205, 213,
 214, 222
 };
 boxCoords.PushBack(Box2);
 int Box3[8]
 {
 209, 234,
 198, 234,
 198, 242,
 210, 242
 };
 boxCoords.PushBack(Box3);
 int Box4[8]
 {
 215, 253,
 206, 262,
 212, 268,
 221, 260
 };
 boxCoords.PushBack(Box4);
 int Box5[8]
 {
 241, 265,
 232, 265,
 233, 276,
 242, 276
 };
 boxCoords.PushBack(Box5);
 int Box6[8]
 {
 258, 254,
 252, 260,
 262, 269,
 268, 262

 };
 boxCoords.PushBack(Box6);
 int Box7[8]
 {
 263, 233,
 263, 241,
 276, 241,
 276, 234
 };
 boxCoords.PushBack(Box7);
 int Box8[8]
 {
 252, 215,
 259, 222,
 268, 213,
 262, 207
 };
 boxCoords.PushBack(Box8);

 /*Crear les fixtures
 - Cuadrats
 -rodona
 *
 b2BodyDef body;
 body.type = b2_dynamicBody;
 body.gravityScale = 0.0f;
 b2PolygonShape poly;
 b2Body* b = world->CreateBody(&body);
 //p2List<b2FixtureDef> fixtures;
 b2Vec2 vertices[3];
 240, 199,
 233, 199,
 233, 211,
 vertices[0].Set(240, 199);
 vertices[1].Set(233, 199);
 vertices[2].Set(233, 211);
 b2FixtureDef tmp;

 for (int i = 0; i < 8; i++)
 {
 for (int i2 = 0, j = 0; i2 < 8 && j <= 3; i2 += 2, j++)
 {
 vertices[j].x = boxCoords[i][i2];
 vertices[j].y = boxCoords[i][i2];
 }
 poly.Set(vertices,3);
 tmp.shape = &poly;
 char debug = 'a';
 char debug1 = 'b';
 b->CreateFixture(&tmp);
 }


 */

PhysBody* ModulePhysics::AddBody(int x, int y, int diameter, body_type type, float density, float restitution, bool ccd, bool isSensor)
{
	b2BodyDef body;

	switch(type)
	{
		case b_static:
		body.type = b2_staticBody;
		break;

		case b_kinematic:
		body.type = b2_kinematicBody;
		break;

		default:
		body.type = b2_dynamicBody;
		break;
	}

	float radius = PIXEL_TO_METERS(diameter) * 0.5f;

	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.angle = 0.0f;
	body.bullet = ccd;

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, {x,y,diameter,diameter}, type);
	bodies.add(ret);

	b->SetUserData(ret);

	return ret;
}


PhysBody* ModulePhysics::AddBody(const SDL_Rect& rect, int* points, uint count, body_type type, float density, float restitution, bool isSensor)
{
	b2BodyDef body;

	switch(type)
	{
		case b_static:
		body.type = b2_staticBody;
		break;

		case b_kinematic:
		body.type = b2_kinematicBody;
		break;

		default:
		body.type = b2_dynamicBody;
		break;
	}

	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	b2Vec2* p = new b2Vec2[count / 2];
	for(uint i = 0; i < count / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.Set(p, count / 2);

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, {rect.x, rect.y, rect.w, rect.h}, type);
	bodies.add(ret);

	delete[] p;

	b->SetUserData(ret);

	return ret;
}

PhysBody* ModulePhysics::AddEdge(const SDL_Rect& rect, int* points, uint count)
{
	b2BodyDef body;

	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[count / 2];

	for(uint i = 0; i < count / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);// *rect.w;
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);// *rect.h;
	}

	shape.CreateLoop(p, count / 2);

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, rect, b_static);
	bodies.add(ret);

	delete[] p;

	b->SetUserData(ret);

	return ret;
}


void ModulePhysics::DestroyBody(PhysBody* body)
{
	assert(body);
	bodies.del(bodies.findNode(body));
	delete body;
}

void ModulePhysics::CreateRevoluteJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1, int y_pivot_1, int x_pivot_2, int y_pivot_2, int max_angle, int min_angle)
{
	b2RevoluteJointDef def;

	def.bodyA = body_1->body;
	def.bodyB = body_2->body;

	def.localAnchorA.Set(PIXEL_TO_METERS(x_pivot_1), PIXEL_TO_METERS(y_pivot_1));
	def.localAnchorB.Set(PIXEL_TO_METERS(x_pivot_2), PIXEL_TO_METERS(y_pivot_2));

	if(max_angle != INT_MAX && min_angle != INT_MIN)
	{
		def.enableLimit = true;
		def.upperAngle = DEGTORAD * max_angle;
		def.lowerAngle = DEGTORAD * min_angle;
	}

	world->CreateJoint(&def);
}

void ModulePhysics::CreateLineJoint(PhysBody* body_1, PhysBody* body_2, int x_pivot_1, int y_pivot_1, int x_pivot_2, int y_pivot_2, float frequency, float damping)
{
	b2DistanceJointDef def;

	def.bodyA = body_1->body;
	def.bodyB = body_2->body;

	def.localAnchorA.Set(PIXEL_TO_METERS(x_pivot_1), PIXEL_TO_METERS(y_pivot_1));
	def.localAnchorB.Set(PIXEL_TO_METERS(x_pivot_2), PIXEL_TO_METERS(y_pivot_2));

	def.dampingRatio = damping; // 0 ... 1
	def.frequencyHz = frequency; // < 30.0f

	world->CreateJoint(&def);
}

void ModulePhysics::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	PhysBody* physA = (PhysBody*) contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*) contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}