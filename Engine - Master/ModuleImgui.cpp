#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleImgui.h"
#include "ModuleRender.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"




ModuleImgui::ModuleImgui()
{
}


ModuleImgui::~ModuleImgui()
{

}

bool ModuleImgui::Init() {




	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	return true;

}

update_status ModuleImgui::PreUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleImgui::Update() {

	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);

	return UPDATE_CONTINUE;
}



update_status ModuleImgui::PostUpdate() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleImgui::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}