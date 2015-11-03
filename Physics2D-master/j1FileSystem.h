#pragma once
#include "PugiXml\src\pugixml.hpp"
#include "Module.h"
struct SDL_RWops;

int close_sdl_rwops(SDL_RWops *rw);

class j1FileSystem : public Module
{
public:

	
	j1FileSystem(Application* app, bool start_enabled = true);
	// Destructor
	virtual ~j1FileSystem();

	// Called before render is available
	

	// Called before quitting
	bool CleanUp();
	bool Init(pugi::xml_node& config);
	// Utility functions
	bool AddPath(const char* path_or_zip, const char* mount_point = NULL);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;
	const char* GetSaveDirectory() const
	{
		return "save/";
	}

	// Open for Read/Write
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;

	unsigned int Save(const char* file, const char* buffer, unsigned int size) const;

private:

};

 // __j1FILESYSTEM_H__