#include "GLM/glm.hpp"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "shader.h"
#include "Skeleton.h"
#include "Animation.h"
#include "CmuFileParser.h"
#include "Simulator.h"
#include "AMCFileParser.h"
#include "Body/Ground.h"
#include "AnimationCompressor.h"
#include "Body/BodyFactory.h"
#include "Camera.h"
#include "Body/Cube.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <unistd.h>

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
    std::vector<const char*> amcPathList = {"/goinfre/schoe/humanGL/amc/walk1.amc", 
    "/goinfre/schoe/humanGL/amc/run.amc","/goinfre/schoe/humanGL/amc/runJump2.amc","/goinfre/schoe/humanGL/amc/punch.amc",
    "/goinfre/schoe/humanGL/amc/idle.amc", "/goinfre/schoe/humanGL/amc/dance.amc", "/goinfre/schoe/humanGL/amc/drink.amc", 
    "/goinfre/schoe/humanGL/amc/roll.amc", "/goinfre/schoe/humanGL/amc/golf.amc"};
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

    AnimationCompressor compressor;
    AnimationData root = simulator._animations[0]._rootNode;
    for (int i = 0; i < simulator._animations.size(); ++i)
    {
        simulator._animations[i]._rootNode = root;
        AMCFileParser amcParser(amcPathList[i], &simulator._skeleton, &simulator._animations[i]);
        amcParser.loadAMCFile();
    }
}

int main() 
{
    Window window;
    std::cout << getcwd(NULL,0) << std::endl;
    Shader shader("/shaderSource/VertexShader.glsl","/shaderSource/FragmentShader.glsl");
    
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
        glm::mat4 projection = glm::perspective(math::radians(_camera._zoom), (float)WINDOW_WITH / (float)WINDOW_HEIGHT, 0.1f, 500.0f);
        _camera.update();
        shader.setMat4("projection", projection);
        shader.setMat4("view", _camera._view);
        simulator.update();
        simulator.draw();
        window.bufferSwap();
        glfwPollEvents();
    }
}