#pragma once
#include "p2SString.h"
//#include "Application.h"
#include "PugiXml\src\pugixml.hpp"
class Application;
class PhysBody;

class Module
{
private :
	bool enabled;
	
public:
	Application* App;
	p2SString name;

	Module(Application* parent, bool start_enabled = true) : App(parent), enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return enabled;
	}

	void Enable()
	{
		if(enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if(enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	virtual bool Init(pugi::xml_node&) 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual void OnCollision(PhysBody* body1, PhysBody* body2)
	{ }
};