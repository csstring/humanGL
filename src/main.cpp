#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include "Window.h"
#include "shader.h"
#include "Skeleton.h"
#include "Animation.h"
#include "CmuFileParser.h"
#include "Simulator.h"
#include "AMCFileParser.h"
#include "Body/Ground.h"
#include "Body/BodyFactory.h"
#include "Camera.h"
#include "Body/Cube.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include "math/Math.h"

Camera      _camera;

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

void fileLoad(Simulator& simulator)
{//fixme path
    std::vector<const char*> amcPathList = {"/Users/schoe/Desktop/humanGL/amc/walk1.amc", 
    "/Users/schoe/Desktop/humanGL/amc/run.amc","/Users/schoe/Desktop/humanGL/amc/runJump2.amc","/Users/schoe/Desktop/humanGL/amc/punch.amc",
    "/Users/schoe/Desktop/humanGL/amc/idle.amc", "/Users/schoe/Desktop/humanGL/amc/dance.amc", "/Users/schoe/Desktop/humanGL/amc/drink.amc", 
    "/Users/schoe/Desktop/humanGL/amc/roll.amc", "/Users/schoe/Desktop/humanGL/amc/golf.amc"};
    simulator._animations.push_back(Animation("walk", 1));
    simulator._animations.push_back(Animation("run", 1));
    simulator._animations.push_back(Animation("runJump2", 1));
    simulator._animations.push_back(Animation("punch", 1));
    simulator._animations.push_back(Animation("idle", 1));
    simulator._animations.push_back(Animation("dance", 1));
    simulator._animations.push_back(Animation("drink", 1));
    simulator._animations.push_back(Animation("roll", 1));
    simulator._animations.push_back(Animation("golf", 1));
    CmuFileParser parser(asfPath,&simulator._skeleton, &simulator._animations[0]);
    parser.loadCmuFile();

    AnimationData root = simulator._animations[0]._rootNode;
    for (int i = 0; i < simulator._animations.size(); ++i)
    {
        simulator._animations[i]._rootNode = root;
        AMCFileParser amcParser(amcPathList[i], &simulator._skeleton, &simulator._animations[i]);
        amcParser.loadAMCFile();
    }
}

void leakCheck()
{
    system("leaks humanGL");
}

int main() 
{
    // atexit(leakCheck);
    Window window;
    Shader shader("./shaderSource/VertexShader.glsl","./shaderSource/FragmentShader.glsl");
    
    window.initialize();
    _camera.initialize();
    shader.initialize();

    Simulator simulator;
    BodyFactory bodyFactory;
    fileLoad(simulator);
    simulator.initialize();
    // camera mouse call
    glfwSetFramebufferSizeCallback(window._window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window._window, mouse_callback);
    glfwSetScrollCallback(window._window, scroll_callback);
    glfwSetInputMode(window._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (window.isWindowClose() == false)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        window.processInput(simulator, _camera);
        math::Mat4 projection = math::perspective(math::radians(_camera._zoom), (float)WINDOW_WITH / (float)WINDOW_HEIGHT, 0.1f, 500.0f);
        _camera.update();
        shader.setMat4("projection", projection);
        shader.setMat4("view", _camera._view);
        simulator.update();
        simulator.draw();
        window.bufferSwap();
        glfwPollEvents();
    }
}
