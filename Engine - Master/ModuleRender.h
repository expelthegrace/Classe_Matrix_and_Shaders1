#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include <cmath>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

	math::float4x4 LookAt(math::float3 & target, math::float3 & eye, math::float3 & up);
	math::float4x4 CalcProjection();

	math::float4x4 projectionMatrix;
	math::float4x4 viewMatrix;

private:
	void* context;
};
