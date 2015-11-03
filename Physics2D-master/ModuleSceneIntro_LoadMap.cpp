//#include "ModuleSceneIntro.h"
//Module Scene start
/*

// Pivot 0, 0
int pinball[134] = {
584, 1079,
584, 221,
578, 187,
566, 149,
545, 106,
523, 77,
496, 51,
463, 31,
421, 12,
375, 4,
219, 4,
189, 15,
172, 29,
159, 46,
150, 68,
147, 90,
148, 121,
155, 152,
159, 168,
180, 209,
179, 216,
170, 216,
147, 172,
141, 152,
137, 121,
134, 90,
131, 25,
124, 14,
113, 8,
97, 11,
88, 24,
89, 97,
92, 153,
96, 195,
99, 216,
116, 270,
115, 278,
106, 275,
89, 215,
85, 192,
78, 64,
75, 46,
65, 36,
40, 29,
16, 36,
3, 58,
3, 203,
8, 250,
15, 293,
21, 321,
75, 492,
75, 504,
33, 607,
32, 670,
0, 708,
0, 916,
171, 1022,
171, 1076,
326, 1076,
326, 1023,
499, 915,
499, 713,
451, 652,
451, 645,
536, 455,
543, 455,
543, 1079
};

App->physics->AddEdge({0, 0, 585, 1024}, pinball, 134);

// Pivot 0, 0
int pinball2[14] = {
521, 195,
507, 151,
478, 110,
442, 76,
409, 59,
382, 51,
382, 103
};

App->physics->AddEdge({0, 0, 585, 1024}, pinball2, 14);

// Pivot 0, 0
int pinball3[8] = {
248, 54,
257, 54,
257, 105,
248, 105
};

App->physics->AddEdge({0, 0, 0, 0}, pinball3, 8);

// Pivot 0, 0
int pinball4[8] = {
294, 48,
303, 48,
303, 97,
294, 97
};

App->physics->AddEdge({0, 0, 0, 0}, pinball4, 8);

// Pivot 0, 0
int pinball5[8] = {
335, 48,
344, 48,
344, 97,
336, 97
};

App->physics->AddEdge({0, 0, 0, 0}, pinball5, 8);

// Pivot 0, 0
int pinball6[68] = {
36, 70,
45, 70,
47, 153,
50, 216,
65, 276,
82, 322,
299, 429,
296, 445,
301, 460,
369, 477,
369, 489,
362, 520,
341, 584,
333, 585,
332, 576,
352, 523,
352, 508,
341, 497,
328, 490,
310, 490,
303, 499,
292, 543,
208, 501,
203, 493,
196, 445,
184, 434,
168, 427,
160, 424,
148, 424,
142, 430,
150, 481,
128, 476,
51, 261,
41, 211
};

App->physics->AddEdge({0, 0, 0, 0}, pinball6, 68);

// Pivot 0, 0
int pinball7[26] = {
382, 608,
388, 612,
497, 432,
514, 369,
520, 333,
520, 287,
513, 287,
466, 382,
487, 400,
487, 415,
442, 467,
427, 466,
408, 544
};

App->physics->AddEdge({0, 0, 0, 0}, pinball7, 26);

// Pivot 0, 0
int pinball8[12] = {
33, 750,
43, 750,
43, 849,
138, 908,
134, 917,
33, 855
};

App->physics->AddEdge({0, 0, 0, 0}, pinball8, 12);

// Pivot 0, 0
int pinball9[12] = {
464, 750,
457, 750,
457, 850,
360, 909,
364, 917,
464, 856
};

App->physics->AddEdge({0, 0, 0, 0}, pinball9, 12);

// Pivot 0, 0
int pinball10[10] = {
80, 725,
80, 824,
136, 856,
145, 849,
92, 723
};

App->physics->AddEdge({0, 0, 0, 0}, pinball10, 10);

// Pivot 0, 0
int pinball11[10] = {
415, 725,
415, 824,
360, 857,
353, 849,
405, 725
};

App->physics->AddEdge({0, 0, 0, 0}, pinball11, 10);

// Other elements ------------------------------------------------

// Small bouncy ball bottom center under flippers
App->physics->AddBody(248, 1024, 24, b_static, 1.0f, 0.8f);

// Two big bouncers on top
bouncer1.body = App->physics->AddBody(256, 175, 50, b_static, 1.0f, 1.5f);
bouncer1.body->listener = this;

bouncer2.body = App->physics->AddBody(343, 169, 50, b_static, 1.0f, 1.5f);
bouncer2.body->listener = this;

// Bouncers on the sides

// Pivot 0, 0
int b1[8] = {
90, 733,
101, 728,
147, 838,
133, 843
};

side_bouncer1.body = App->physics->AddBody({0, 0, 585, 1024}, b1, 8, b_static, 1.0f, 1.0f, false);
side_bouncer1.body->listener = this;

// Pivot 0, 0
int b2[8] = {
409, 732,
398, 726,
350, 835,
365, 841
};

side_bouncer2.body = App->physics->AddBody({0, 0, 585, 1024}, b2, 8, b_static, 1.0f, 1.0f, false);
side_bouncer2.body->listener = this;

// Sensors (blue lights on the floor)
tex_light_tiny = App->textures->Load("pinball/sensor_tiny.png");
tex_light_medium = App->textures->Load("pinball/sensor_med.png");
tex_light_big = App->textures->Load("pinball/sensor_big.png");

fx_light_tiny = App->audio->LoadFx("pinball/bonus2.wav");
fx_light_medium = App->audio->LoadFx("pinball/bonus2.wav");
fx_light_big = App->audio->LoadFx("pinball/bonus3.wav");

lights.PushBack(Light(this, 422, 140, lightTypes::tiny));
lights.PushBack(Light(this, 451, 159, lightTypes::tiny));
lights.PushBack(Light(this, 481, 179, lightTypes::tiny));

lights.PushBack(Light(this, 220, 514, lightTypes::tiny));
lights.PushBack(Light(this, 251, 530, lightTypes::tiny));

lights.PushBack(Light(this, 73, 525, lightTypes::tiny));
lights.PushBack(Light(this, 61, 556, lightTypes::tiny));
lights.PushBack(Light(this, 49, 587, lightTypes::tiny));

lights.PushBack(Light(this, 73, 245, lightTypes::medium));
lights.PushBack(Light(this, 64, 207, lightTypes::medium));
lights.PushBack(Light(this, 61, 170, lightTypes::medium));
lights.PushBack(Light(this, 58, 134, lightTypes::medium));
lights.PushBack(Light(this, 57, 99, lightTypes::medium));
lights.PushBack(Light(this, 55, 63, lightTypes::medium));
lights.PushBack(Light(this, 13, 63, lightTypes::medium));
lights.PushBack(Light(this, 13, 100, lightTypes::medium));
lights.PushBack(Light(this, 14, 136, lightTypes::medium));
lights.PushBack(Light(this, 15, 174, lightTypes::medium));
lights.PushBack(Light(this, 19, 214, lightTypes::medium));
lights.PushBack(Light(this, 25, 253, lightTypes::medium));
lights.PushBack(Light(this, 34, 291, lightTypes::medium));
lights.PushBack(Light(this, 46, 333, lightTypes::medium));
lights.PushBack(Light(this, 61, 373, lightTypes::medium));

lights.PushBack(Light(this, 266, 63, lightTypes::big));
lights.PushBack(Light(this, 309, 58, lightTypes::big));
lights.PushBack(Light(this, 352, 59, lightTypes::big));

lights.PushBack(Light(this, 426, 32, lightTypes::big));
lights.PushBack(Light(this, 385, 477, lightTypes::big));

lights.PushBack(Light(this, 6, 870, lightTypes::big));
lights.PushBack(Light(this, 472, 870, lightTypes::big));

// Sensor for player losing (under flippers)

player_lose = App->physics->AddBody({245, 1080, 200, 50}, b_static, 1.0f, 0.0f, false, true);
player_lose->listener = this;
*/

//Module player start
/*

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

FlipperPosition.Set(148, 587);

FlipperAnchorA.Set(155, 585);
FlipperAnchorB.Set(-20, -0);

b2RevoluteJoint* LeftFlipperBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper, -0.16f, 0.16f);

FlipperPosition.Set(187, 657);

FlipperAnchorA.Set(177, 657);
FlipperAnchorB.Set(-20, 0);

b2RevoluteJoint* LeftFlipperDownBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper, -0.16f, 0.16f);

FlipperPosition.Set(400, 580);

FlipperAnchorA.Set(335, 584);
FlipperAnchorB.Set(10, 10);

//b2RevoluteJoint* RightFlipperBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);

FlipperPosition.Set(200, 580);

FlipperAnchorA.Set(310, 655);
FlipperAnchorB.Set(10, 10);

//b2RevoluteJoint* RightFlipperDownBody = App->physics->CreateFlipper(x, y, anchorLeftFlipper, 8, FlipperAnchorA, FlipperPosition, FlipperAnchorB, LeftFlipper);


//RightFlipper

//Rotating Gear
App->physics->CreateGear(237, 237, 26.0f);

*/