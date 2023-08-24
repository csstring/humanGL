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
        math::Mat4 projection = math::perspective(math::radians(_camera._zoom), (float)WINDOW_WITH / (float)WINDOW_HEIGHT, 0.1f, 500.0f);
        glm::mat4 pro = glm::perspective(math::radians(_camera._zoom), (float)WINDOW_WITH / (float)WINDOW_HEIGHT, 0.1f, 500.0f);
        math::Mat4 transPose;
        glm::mat4 transPro = glm::transpose(pro);
        // {
		// 	transPose[0][0] = projection[0][0];
		// 	transPose[0][1] = projection[1][0];
		// 	transPose[0][2] = projection[2][0];
		// 	transPose[0][3] = projection[3][0];

		// 	transPose[1][0] = projection[0][1];
		// 	transPose[1][1] = projection[1][1];
		// 	transPose[1][2] = projection[2][1];
		// 	transPose[1][3] = projection[3][1];

		// 	transPose[2][0] = projection[0][2];
		// 	transPose[2][1] = projection[1][2];
		// 	transPose[2][2] = projection[2][2];
		// 	transPose[2][3] = projection[3][2];

		// 	transPose[3][0] = projection[0][3];
		// 	transPose[3][1] = projection[1][3];
		// 	transPose[3][2] = projection[2][3];
		// 	transPose[3][3] = projection[3][3];
        // }
        // {
        //     std::cout << transPose[0][0] << " "<< transPro[0][0]<< std::endl;
        //     std::cout << transPose[1][1] << " "<<transPro[1][1]<< std::endl; 
        //     std::cout << transPose[2][2] << " "<<transPro[2][2]<<  std::endl; 
        //     std::cout << transPose[2][3] << " "<<transPro[2][3]<<  std::endl; 
        //     std::cout << transPose[3][2] << " "<<transPro[3][2] << std::endl; 
        //     std::cout << transPose[0][1] << transPose[0][2] << transPose[0][3] << std::endl;
        //     std::cout << transPose[1][0] << transPose[1][2] << transPose[1][3] << std::endl;
        //     std::cout << transPose[2][0] << transPose[2][1] << std::endl;
        //     std::cout << transPose[3][0] << transPose[3][1] << transPose[3][3] << std::endl;
        //     std::cout << "math end" <<std::endl;
        //     std::cout << transPro[0][1] << transPro[0][2] << transPro[0][3] << std::endl;
        //     std::cout << transPro[1][0] << transPro[1][2] << transPro[1][3] << std::endl;
        //     std::cout << transPro[2][0] << transPro[2][1] << std::endl;
        //     std::cout << transPro[3][0] << transPro[3][1] << transPro[3][3] << std::endl;
        //     std::cout << "glm end" <<std::endl;
        // }

        _camera.update();
        shader.setMat4("projection", pro);
        shader.setMat4("view", _camera._view);
        simulator.update();
        simulator.draw();
        window.bufferSwap();
        glfwPollEvents();
    }
}