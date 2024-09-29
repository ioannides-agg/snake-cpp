#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    GLFWwindow* window;
    if(!glfwInit()) {
        std::cout << "GLFW could not start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Snake Game", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.25f, 0.6f, 0.70f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    
    return 0;
}