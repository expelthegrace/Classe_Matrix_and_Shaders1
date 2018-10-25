#include "ModuleCamera.h"{}
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "GL/glew.h"
#include "SDL.h"
#include "ModuleInput.h"
#include "ModuleRenderExercise.h"



ModuleCamera::ModuleCamera()
{
}


bool ModuleCamera::Init() {
	cameraPos = { 0, 5, 5 };
	viewMatrix = App->camera->LookAt(math::float3(0, 0, 0),cameraPos, math::float3(0, 1, 0));
	projectionMatrix = CalcProjection();
	camSpeed = 0.5;

	return true;
}

void ModuleCamera::PintaGrid() {

	int size = 100;

	glBegin(GL_LINES);
	glColor3f(0.75f, 0.75f, 0.75f);
	for (int i = -size; i <= size; i++)
	{
		glVertex3f((float)i, 0, (float)-size);
		glVertex3f((float)i, 0, (float)size);

		glVertex3f((float)-size, 0, (float)i);
		glVertex3f((float)size, 0, (float)i);
	}
	glEnd();
}

update_status ModuleCamera::Update() {

	PintaGrid();


	// vv aixo podria modificar el frustrum i ja esta
	if (App->input->keyboard[SDL_SCANCODE_Q]) {
		cameraPos -= math::float3(0, camSpeed, 0);
		viewMatrix = App->camera->LookAt(math::float3(0, 0, 0), cameraPos, math::float3(0, 1, 0));
		projectionMatrix = CalcProjection();

		App->exercise->UpdateMatrix();
	}
	else if (App->input->keyboard[SDL_SCANCODE_E]) {
		cameraPos += math::float3(0, camSpeed, 0);
		viewMatrix = App->camera->LookAt(math::float3(0, 0, 0), cameraPos, math::float3(0, 1, 0));
		projectionMatrix = CalcProjection();

		App->exercise->UpdateMatrix();

	}

	return UPDATE_CONTINUE;
}

ModuleCamera::~ModuleCamera()
{
}

math::float4x4 ModuleCamera::LookAt(math::float3 & target, math::float3 & eye, math::float3 & up) {
	math::float4x4 matrix;

	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));
	matrix[0][0] = s.x; matrix[0][1] = s.y; matrix[0][2] = s.z;
	matrix[1][0] = u.x; matrix[1][1] = u.y; matrix[1][2] = u.z;
	matrix[2][0] = -f.x; matrix[2][1] = -f.y; matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye); matrix[1][3] = -u.Dot(eye); matrix[2][3] = f.Dot(eye);
	matrix[3][0] = matrix[3][1] = matrix[3][2] = 0;
	matrix[3][3] = 1;
	return matrix;
}

math::float4x4 ModuleCamera::CalcProjection() {
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atan(tan(frustum.verticalFov * 0.5f) * aspect);
	return frustum.ProjectionMatrix();
}