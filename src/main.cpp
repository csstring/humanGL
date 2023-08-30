#define GL_SILENCE_DEPRECATION
#include "Window.h"
#include "shader.h"
#include "Skeleton.h"
#include "Animation.h"
#include "Simulator.h"
#include "Body/Ground.h"
#include "Body/BodyFactory.h"
#include "Camera.h"
#include "Body/Cube.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include "math/Math.h"
#include "Mygui.h"

Camera      _camera;
Mygui       mygui;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (_camera._isFirst)
    {
        _camera._lastX = xpos;
        _camera._lastY = ypos;
        _camera._isFirst = false;
    }

    float xoffset = xpos - _camera._lastX;
    float yoffset = _camera._lastY - ypos;

    _camera._lastX = xpos;
    _camera._lastY = ypos;

    _camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    _camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void leakCheck()
{
    system("leaks humanGL");
}

int main(int ac, char **av) 
{
    if (ac < 2){
        ft_exit("input error : cmu file path missing");
    } else if (ac > 2) {
        ft_exit("input error : to many argument");
    }
    // atexit(leakCheck);
    Window window;
    Shader shader("./shaderSource/VertexShader.glsl","./shaderSource/FragmentShader.glsl");
    
    window.initialize();
    _camera.initialize();
    shader.initialize();

    Simulator simulator;
    BodyFactory bodyFactory;

    mygui.initialize(window._window);
    simulator.fileLoad(av[1]);
    simulator.initialize();
    // camera mouse call
    // glfwSetFramebufferSizeCallback(window._window, framebuffer_size_callback);
    // glfwSetCursorPosCallback(window._window, mouse_callback);
    // glfwSetScrollCallback(window._window, scroll_callback);
    // glfwSetInputMode(window._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (window.isWindowClose() == false)
    {
        mygui.update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        window.processInput(simulator, _camera);
        math::Mat4 projection = math::perspective(math::radians(_camera._zoom), (float)WINDOW_WITH / (float)WINDOW_HEIGHT, 0.1f, 500.0f);
        _camera.update();
        shader.setMat4("projection", projection);
        shader.setMat4("view", _camera._view);
        simulator.update();
        simulator.draw();
        mygui.render();
        window.bufferSwap();
        glfwPollEvents();
    }

    glfwTerminate();
}
