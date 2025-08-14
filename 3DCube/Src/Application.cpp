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



   
    ShapeData Plane = ShapeGenerator::MakePlane(5);

    VertexArray Vao;

    VertexBuffer Vb(Plane);

    IndexBuffer Ib(Plane);

    VertexBufferLayout Layout;
	Layout.Push(3, GL_FLOAT, GL_FALSE);// Position
    Layout.Push(3, GL_FLOAT, GL_FALSE);// Color
    Layout.Push(3, GL_FLOAT, GL_FALSE);// Normal

	Vao.AddBuffers(Vb, Ib, Layout); 

    Shader Shader("Src/Shader/Shader.shader");
    Shader.Bind();

	Camera Camera(window);

    vec3 LightLocation = vec3(0.0f, 0.5f, 0.0f);
    Shader.UpdateUniformVec3f("LightLocation", LightLocation);
    
    
    Plane.CleanUp();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        /* Render here */
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width, height);

		Camera.UpdateCameraPosition(window);

        mat4 Proj = perspective(glm::radians(90.0f), 640.0f / 480.0f, 0.1f, 10.0f);
        mat4 Model = translate(mat4(1.0f), vec3(0, 0, 0));
        mat4 Rotation = rotate(mat4(1.0f), glm::radians(90.f), vec3(1, 0, 0));
        mat4 ModelToWorld = Model * Rotation;
        mat4 MVP = Proj  * Camera.GetWorldToViewMatrix() * ModelToWorld;
        
        Shader.UpdateUniformMat4f("MVP", MVP);
        Shader.UpdateUniformMat4f("ModelToWorldMat", ModelToWorld);

        
        glDrawElements(GL_TRIANGLES, Plane.NumIndices, GL_UNSIGNED_SHORT, nullptr);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}