/*
 * Audio Overload SDK
 *
 * Debug GUI
 *
 * Author: Nmlgc
 */

#include <imgui.h>
#include "imgui/examples/opengl_example/imgui_impl_glfw.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "ao.h"
#include "debug.h"

GLFWwindow *window;
bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImColor(114, 144, 154);

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

ao_bool debug_start(void)
{
	// Setup window
	glfwSetErrorCallback(error_callback);
	if(!glfwInit()) {
		return false;
	}
 
	window = glfwCreateWindow(1280, 720, "ImGui OpenGL2 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Setup ImGui binding
	ImGui_ImplGlfw_Init(window, true);

	return true;
}

ao_bool debug_frame(void)
{
	glfwPollEvents();
	ImGui_ImplGlfw_NewFrame();

	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if(ImGui::Button("Test Window")) {
			show_test_window ^= 1;
		}
		if(ImGui::Button("Another Window")) {
			show_another_window ^= 1;
		}
		ImGui::Text(
			"Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate
		);
	}

	// 2. Show another simple window, this time using an explicit Begin/End pair
	if(show_another_window) {
		ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	// Rendering
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::Render();
	glfwSwapBuffers(window);
	
	return glfwWindowShouldClose(window);
}

ao_bool debug_stop(void)
{
	// Cleanup
	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();

	return true;
}