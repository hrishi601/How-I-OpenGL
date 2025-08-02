#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debuger/Debuger.h"
#include "Shader/Shader.h"
#include "Primitives/ShapeGenerator.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "VertexArray/VertexBufferLayout.h"
#include "VertexArray/VertexArray.h"
#include "Camera/Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // kind of vsync
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        LOG("Error in initializing GLEW.\n");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);



    ShapeData Cube = ShapeGenerator::MakeCube();

    VertexArray Vao;

    VertexBuffer Vb(Cube);

    IndexBuffer Ib(Cube);

    VertexBufferLayout Layout;
	Layout.Push(3, GL_FLOAT, GL_FALSE);// Position
    Layout.Push(3, GL_FLOAT, GL_FALSE);// Color

	Vao.AddBuffers(Vb, Ib, Layout); 

    Shader Shader("Src/Shader/Shader.shader");
    Shader.Bind();

	Camera Camera(window);

    mat4 Proj = perspective(90.0f, 640.0f / 480.0f, 0.1f, 10.0f);
    mat4 Model = translate(mat4(1.0f), vec3(0, 0, 0));
    mat4 Rotation = rotate(mat4(1.0f), 45.0f, vec3(1, 0, 0));
    mat4 MVP = Proj *Camera.GetWorldToViewMatrix()* Model * Rotation;

    Shader.UpdateUniformMat4f("MVP", MVP);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        /* Render here */
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width, height);

        mat4 Proj = perspective(90.0f, 640.0f / 480.0f, 0.1f, 10.0f);
        mat4 Model = translate(mat4(1.0f), vec3(0, 0, 0));
        mat4 Rotation = rotate(mat4(1.0f), 45.0f, vec3(1, 0, 0));
        mat4 MVP = Proj * Camera.GetWorldToViewMatrix() * Model * Rotation;

        Shader.UpdateUniformMat4f("MVP", MVP);

        
        glDrawElements(GL_TRIANGLES, Cube.NumIndices, GL_UNSIGNED_SHORT, nullptr);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}