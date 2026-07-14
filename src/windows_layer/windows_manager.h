#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
    public: 
        Window(int width, int height, const std::string& title);
        ~Window();

        bool ShouldClose() {return glfwWindowShouldClose(m_window);}
        void PollEvents() {glfwPollEvents();}

    private:
        void InitWindow();
        
        int m_width;
        int m_height;
        std::string m_title;

        GLFWwindow* m_window = nullptr;
};