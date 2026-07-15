#include "Windows_manager.h"
#include <stdexcept>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title){
        InitWindow();
}

void Window::InitWindow() {
    if(!glfwInit()){
        throw std::runtime_error("glfw_failed");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if(!m_window){
        throw std::runtime_error("window_created_falled");
    }
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

std::vector<const char*> Window::GetRequiredExtensions(){
    uint32_t glfwExtensionCout = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCout);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCout);
    return extensions;
}

void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface){
    VkResult surface_result = glfwCreateWindowSurface(instance, m_window, nullptr, surface);
    if(surface_result != VK_SUCCESS){
        throw std::runtime_error("glfwCreateSurface failed"); 
    }
}
