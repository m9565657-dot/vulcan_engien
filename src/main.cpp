#include <iostream>
#include "windows_layer/windows_manager.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

int main(){
    Window myWindow(680, 840, "HELLOW_WORLD");

    // Step 1: Vulkan Instance 

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

    // Step 2: change a videocard 

    uint32_t deviceCount = 0; 
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    std::vector<VkPhysicalDevice> gpu_list(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, gpu_list.data());

    VkPhysicalDevice physicalDevice = gpu_list[0];

    // LOOP

    while(!myWindow.ShouldClose()){
        myWindow.PollEvents();
    }

    vkDestroyInstance(instance, nullptr);
    return 0;
}