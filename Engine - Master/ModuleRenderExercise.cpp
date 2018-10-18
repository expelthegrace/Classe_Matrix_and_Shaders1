#include "Application.h"

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"

#include "GL/glew.h"
#include "SDL.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

math::float4x4 ModuleRenderExercise::LookAt(math::float3 & target, math::float3 & eye, math::float3 & up) {
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

math::float4x4 ModuleRenderExercise::CalcProjection() {
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	Frustum frustum;
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

bool ModuleRenderExercise::Init()
{

	viewMatrix = LookAt(math::float3(0, 0, 0), math::float3(0, 0, 5), math::float3(0, 1, 0));
	projectionMatrix = CalcProjection();

	math::float4 point1 = projectionMatrix * viewMatrix * math::float4(-1, -1, 0, 1);
	math::float4 point2 = projectionMatrix * viewMatrix * math::float4(1, -1, 0, 1);
	math::float4 point3 = projectionMatrix * viewMatrix * math::float4(0, 1, 0, 1);

	float vertex_buffer_data[] = {
		point1.x / point1.w, point1.y / point1.w, point1.z / point1.w,
		point2.x / point2.w, point2.y / point2.w, point2.z / point2.w,
		point3.x / point3.w, point3.y / point3.w, point3.z / point3.w,
	};
	// falta multiplicar cada vertex ^ per la project view matrix


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

update_status ModuleRenderExercise::Update()
{


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            0,                  // attribute 0
            3,                  // number of componentes (3 floats)
            GL_FLOAT,           // data type
            GL_FALSE,           // should be normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	return true;
}

