// This code is to draw a triangle within the window. The code is using opengl programmable
// pipeline with Shader class. 
// Copyright by Rui @njupt.
// 2022.9

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Minicore.h"
#include "Windows.h"
#include "Tutorial.h"





static void SetViewport(GLFWwindow* window)
{
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
}

int main()
{
	Tutorial tutorial;
	tutorial.InitWindow("Tutorial4");
	tutorial.initUI();
	tutorial.CreateObjects();
	tutorial.CreateShaders();
	while (!glfwWindowShouldClose(tutorial.window))
	{
		SetViewport(tutorial.window);
		tutorial.RenderScreen();
	}

	return 0;
}