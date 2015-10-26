#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT /2;
	int diameter = 21;

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* big_ball = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	big_ball->CreateFixture(&fixture);

	//Create box

	int x_b = 490;
	int y_b = 722;

	b2BodyDef dock;
	dock.type = b2_kinematicBody;
	dock.position.Set(PIXEL_TO_METERS(x_b), PIXEL_TO_METERS(y_b));

	b2Body* dock_body = world->CreateBody(&dock);

	b2PolygonShape shape_d;
	shape_d.SetAsBox(PIXEL_TO_METERS(9) * 0.5f, PIXEL_TO_METERS(67) * 0.5f);

	b2FixtureDef fixture_d;
	fixture_d.shape = &shape_d;
	dock_body->CreateFixture(&fixture_d);

	//Create Bottom
	
	return true;
}

 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

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


PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, int type)
{
	b2BodyDef body;
	switch (type)
	{
	case 1:
		body.type = b2_kinematicBody;
		break;
	case -1:
		body.type = b2_staticBody;
		break;
	default:	
		case 0:
			body.type = b2_dynamicBody;
			break;
		break;
	}
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;


	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}


b2RevoluteJoint* ModulePhysics::CreateFlipper(int x, int y, int* anchor, int sizeAnchor, int* shape, int sizeShape)
{
	//Create Flippers



	//b2Vec2	rightFlipperPosition;
	b2Vec2	leftFlipperPosition;

	leftFlipperPosition.Set(144, 582);
	//rightFlipperPosition.Set(310, 657);

	
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0;


	//b2BodyDef body1;
	//body1.type = b2_dynamicBody;
	//body1.position.Set(PIXEL_TO_METERS(144), PIXEL_TO_METERS(575));

	b2BodyDef body2;
	body2.type = b2_dynamicBody;
	body2.position.Set(PIXEL_TO_METERS(200), PIXEL_TO_METERS(580));
	

	//b2PolygonShape shape1;
	//shape1.SetAsBox(PIXEL_TO_METERS(10),PIXEL_TO_METERS(10));
	//b2FixtureDef fixture1;
	//fixture1.density = 1;
	//fixture1.shape = &shape1;


	//b2Body* b1 = world->CreateBody(&body1);
	//b1->CreateFixture(&fixture1);



	b2PolygonShape shape2;
	shape2.SetAsBox(PIXEL_TO_METERS(25), PIXEL_TO_METERS(5));
	b2FixtureDef fixture2;
	fixture2.density = 1;
	fixture2.shape = &shape2;
	

	b2Body* b2 = world->CreateBody(&body2);
	b2->CreateFixture(&fixture2);

	
	b2RevoluteJointDef revoluteJoint;
	revoluteJoint.bodyA = ground;
	revoluteJoint.bodyB = b2;
	revoluteJoint.collideConnected = true;
	revoluteJoint.enableLimit = true;
	revoluteJoint.lowerAngle = -0.16 * b2_pi;
	revoluteJoint.upperAngle = 0.16 * b2_pi;



	revoluteJoint.localAnchorA.Set(PIXEL_TO_METERS(167),PIXEL_TO_METERS(585));
	revoluteJoint.localAnchorB.Set(PIXEL_TO_METERS(-10), PIXEL_TO_METERS(-10));
	//revoluteJoint.referenceAngle = 0;
	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJoint);


	return joint;
}

PhysBody* ModulePhysics::CreateGear(int x, int y, float radius)
{
// Create sphere
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);


	/*b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);*/
	
	b2PolygonShape shape;
	shape.SetAsBox(PIXEL_TO_METERS(35), PIXEL_TO_METERS(35));

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);
	b->SetGravityScale(0);

	//Create Pin
	b2BodyDef body_g;
	body_g.type = b2_staticBody;
	int x_g = x - 15;
	int y_g = y - 60;
	body_g.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b_g = world->CreateBody(&body_g);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(13), PIXEL_TO_METERS(13));

	b2FixtureDef fixture_g;
	fixture_g.shape = &box;
	fixture_g.density = 1.0f;

	b_g->CreateFixture(&fixture_g);
	
	
	b_g->SetGravityScale(0);

	/*b2DistanceJointDef dJointDef;
	dJointDef.bodyB = b;
	dJointDef.bodyA = b_g;
	dJointDef.Initialize(b, b_g, b->GetWorldCenter(), b_g->GetWorldCenter());
	dJointDef.collideConnected =false; 

	b2DistanceJoint* d_joint = (b2DistanceJoint*)world->CreateJoint(&dJointDef);*/
	
	b2RevoluteJointDef jointDef;
	jointDef.bodyB = b;
	jointDef.bodyA = b_g;
	jointDef.Initialize(b, b_g, b->GetWorldCenter());
	jointDef.collideConnected = false;

	//jointDef.enableLimit = true;
	jointDef.maxMotorTorque = 0.1f;
	jointDef.motorSpeed = 0.0f;
	jointDef.enableMotor = true;

	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
	

	PhysBody* pbody = new PhysBody();
	pbody->body = b_g;
	b_g->SetUserData(pbody);
	pbody->width = pbody->height = radius;
	return pbody;

}




PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}




update_status ModulePhysics::PostUpdate()
{
	b2Vec2 mouse_position;
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();
				App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

					prev = v;
				}

				v = b->GetWorldPoint(polygonShape->GetVertex(0));
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
					prev = v;
				}

				v = b->GetWorldPoint(shape->m_vertices[0]);
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
			}
			break;

			// Draw a single segment(edge) ----------------------------------
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = b->GetWorldPoint(shape->m_vertex0);
				v2 = b->GetWorldPoint(shape->m_vertex1);
				App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
			}
			break;
			}


//Joint render

			/*

			for (b2Joint* b = world->GetJointList(); b; b = b->GetNext())
			{
				for (b2Fixture* f1 = b->GetBodyA()->GetFixtureList(); f1; f1 = f1->GetNext())
				{
					b2ChainShape* shape1 = (b2ChainShape*)f1->GetShape();
					b2Vec2 prev, v;

					for (int32 i = 0; i < shape1->m_count; ++i)
					{
						v = b->GetBodyA()->GetWorldPoint(shape1->m_vertices[i]);
						if (i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

				}*/
				/*
				for (b2Fixture* f2 = b->GetBodyA()->GetFixtureList(); f2; f2 = f2->GetNext())
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for (int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetBodyB()->GetWorldPoint(shape->m_vertices[i]);
						if (i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

				}

				

			

			

			}
			
			*/


			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
				mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());
				if (f->GetShape()->TestPoint(b->GetTransform(), mouse_position) == true)
				{
					body_clicked = b;
				}
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (body_clicked != NULL)
	{
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
		{
			char debug = 'a';
		}
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_clicked;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * body_clicked->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	
	
	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	}

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && body_clicked != NULL)
	{
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{
			char debug = 'a';
		}
		mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
		mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());

		mouse_joint->SetTarget(mouse_position);
		b2Vec2 AnchorA = mouse_joint->GetAnchorA();
		b2Vec2 AnchorB = mouse_joint->GetAnchorB();

		App->renderer->DrawLine(AnchorA.x, AnchorA.y, AnchorB.x, AnchorB.y, 255, 0, 0, 255, true);
	}
	// TODO 4: If the player releases the mouse button, destroy the joint
	/*if (App->input->GetMouseButton(SDL_BUTTON_LEFT) != KEY_DOWN)
	{
		delete(mouse_joint);
		body_clicked = NULL;
	}*/
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}