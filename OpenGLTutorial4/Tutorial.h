#pragma once
class Tutorial : public Window {
public:
	Tutorial()
	{
		glEnable(GL_CULL_FACE);

	}
	~Tutorial()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		delete pshader;
	}
	inline void RenderScreen() override final
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->pshader->UseProgram();
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		this->pshader->Set4Float("Color", 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(this->window);
	}
	void initUI()
	{
		glfwSetKeyCallback(this->window, KeyCallback);
		glfwSetFramebufferSizeCallback(this->window, FramebufferSizeCallback);
	}
	void CreateObjects()
	{
		this->CreateTriangle();
	}
	
	void CreateShaders()
	{
		pshader = new Shader("res/shaders/core.vs", "res/shaders/core.fs");

	}
	bool IsWindowClosed()
	{
		return glfwWindowShouldClose(window);
	}
private:
	GLuint VAO=-1;
	GLuint VBO=-1;
	Shader* pshader;
	void CreateTriangle()
	{
		GLfloat vertices[] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f };
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	static void FramebufferSizeCallback(GLFWwindow
		* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

};