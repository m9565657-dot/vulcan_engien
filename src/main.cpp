#include <iostream>
#include "windows_layer/windows_manager.h"
#include <vulkan/vulkan.h>
#include <stdexcept>

int main(){
    Window myWindow(680, 840, "HELLOW_WORLD");

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "My Engien";
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if(result != VK_SUCCESS){
        throw std::runtime_error("FAILED TO CREATE VULCAN INSTANCE!");
    }
    
    while(!myWindow.ShouldClose()){
        myWindow.PollEvents();
    }

    vkDestroyInstance(instance, nullptr);
    return 0;
}