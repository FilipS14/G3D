#include <gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void renderFloor();
void renderScene();



int main()
{
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SubmarineG3D", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	Shader lightingShader("PhongLight.vs", "PhongLight.fs");
	Shader lampShader("Lamp.vs", "Lamp.fs");
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();
		lightingShader.SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
		renderScene();

		glm::mat4 model = glm::scale(glm::mat4(1.0), glm::vec3(3.0f));
		lightingShader.SetMat4("model", model);
		lightingShader.SetVec3("objectColor", 0.588f, 0.294f, 0.0f);
		renderFloor();
	}
}

void renderFloor()
{
	unsigned int planeVAO;
	unsigned int planeVBO;

	float planeVertices[] = {
		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

		25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
		25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
	};
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void renderScene()
{
	unsigned int VBO, cubeVAO, lightVAO;

	float vertices[] = {
	-25.0f, -25.0f, -25.0f,  0.0f,  0.0f, -1.0f,
	 25.0f, -25.0f, -25.0f,  0.0f,  0.0f, -1.0f,
	 25.0f,  25.0f, -25.0f,  0.0f,  0.0f, -1.0f,
	 25.0f,  25.0f, -25.0f,  0.0f,  0.0f, -1.0f,
    -25.0f,  25.0f, -25.0f,  0.0f,  0.0f, -1.0f,
    -25.0f, -25.0f, -25.0f,  0.0f,  0.0f, -1.0f,

	-25.0f, -25.0f,  25.0f,  0.0f,  0.0f,  1.0f,
	 25.0f, -25.0f,  25.0f,  0.0f,  0.0f,  1.0f,
  	 25.0f,  25.0f,  25.0f,  0.0f,  0.0f,  1.0f,
	 25.0f,  25.0f,  25.0f,  0.0f,  0.0f,  1.0f,
	-25.0f,  25.0f,  25.0f,  0.0f,  0.0f,  1.0f,
	-25.0f, -25.0f,  25.0f,  0.0f,  0.0f,  1.0f,

	-25.0f,  25.0f,  25.0f, -1.0f,  0.0f,  0.0f,
	-25.0f,  25.0f, -25.0f, -1.0f,  0.0f,  0.0f,
	-25.0f, -25.0f, -25.0f, -1.0f,  0.0f,  0.0f,
	-25.0f, -25.0f, -25.0f, -1.0f,  0.0f,  0.0f,
	-25.0f, -25.0f,  25.0f, -1.0f,  0.0f,  0.0f,
	-25.0f,  25.0f,  25.0f, -1.0f,  0.0f,  0.0f,

	 25.0f,  25.0f,  25.0f,  1.0f,  0.0f,  0.0f,
	 25.0f,  25.0f, -25.0f,  1.0f,  0.0f,  0.0f,
	 25.0f, -25.0f, -25.0f,  1.0f,  0.0f,  0.0f,
	 25.0f, -25.0f, -25.0f,  1.0f,  0.0f,  0.0f,
	 25.0f, -25.0f,  25.0f,  1.0f,  0.0f,  0.0f,
	 25.0f,  25.0f,  25.0f,  1.0f,  0.0f,  0.0f,

	-25.0f, -25.0f, -25.0f,  0.0f, -1.0f,  0.0f,
	 25.0f, -25.0f, -25.0f,  0.0f, -1.0f,  0.0f,
	 25.0f, -25.0f,  25.0f,  0.0f, -1.0f,  0.0f,
	 25.0f, -25.0f,  25.0f,  0.0f, -1.0f,  0.0f,
	-25.0f, -25.0f,  25.0f,  0.0f, -1.0f,  0.0f,
	 -25.0f, -25.0f, -25.0f,  0.0f, -1.0f, 0.0f,
	-25.0f, -25.0f, -25.0f,  0.0f, -1.0f,  0.0f,

	-25.0f,  25.0f, -25.0f,  0.0f,  1.0f,  0.0f,
	 25.0f,  25.0f, -25.0f,  0.0f,  1.0f,  0.0f,
	 25.0f,  25.0f,  25.0f,  0.0f,  1.0f,  0.0f,
	 25.0f,  25.0f,  25.0f,  0.0f,  1.0f,  0.0f,
	-25.0f,  25.0f,  25.0f,  0.0f,  1.0f,  0.0f,
	-25.0f,  25.0f, -25.0f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(2, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
