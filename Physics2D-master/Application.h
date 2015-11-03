#ifndef __APPLICATION_H__
#define __APPLICATION_H__



#include "PugiXml\src\pugixml.hpp"


#include "p2List.h"
#include "Globals.h"

#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "j1FileSystem.h"
//
#pragma comment (lib,"Box2D/libx86/Debug/Box2D.lib")

class Module;

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModulePhysics* physics;
	j1FileSystem* file;

private:

	p2List<Module*> list_modules;
	p2SString			title;
	p2SString			organization;
public:

	Application();
	~Application();

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;
	const char* GetOrganization() const;
	bool Init();
	update_status Update();
	bool CleanUp();
	const char*GetTitle() const;
private:

	void AddModule(Module* mod);
};

extern Application* App;

#endif