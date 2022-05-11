#include <iostream>
#include <format>

#include <GLFW/glfw3.h>

#include "gui.h"

static GLFWwindow* window = nullptr;

static void GLFWErrorCallback(int error, const char* description)
{
	std::cout << std::format("GLFW Error {} Code {}", description, error);
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!\n";
		std::cin.get();
	}

	glfwSetErrorCallback(GLFWErrorCallback);

	window = glfwCreateWindow(windowWidth, windowHeight, "ImGUI", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

	SetupStyle();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
		ImGui::SetNextWindowBgAlpha(0.8f);

		Render(window);

		ImGui::End();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwWaitEvents();
		glfwSwapBuffers(window);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (window) glfwDestroyWindow(window);
	glfwTerminate();
}