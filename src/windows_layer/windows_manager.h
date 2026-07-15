#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Window {
    public: 
        Window(int width, int height, const std::string& title);
        ~Window();

        bool ShouldClose() {return glfwWindowShouldClose(m_window);}
        void PollEvents() {glfwPollEvents();}

        std::vector<const char*> GetRequiredExtensions();
        void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

    private:
        void InitWindow();
        
        int m_width;
        int m_height;
        std::string m_title;

        GLFWwindow* m_window = nullptr;
};