#ifndef _IMGUI_
#define _IMGUI_

#include "Module.h"
class ModuleImgui :
	public Module
{
public:
	ModuleImgui();
	virtual ~ModuleImgui();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


};

#endif
