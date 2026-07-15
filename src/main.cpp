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


    // Step 3: 

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    int graphicsFamilyIndex = -1;

    for(int x=0; x<queueFamilyCount; x++){
        if(queueFamilies[x].queueFlags & VK_QUEUE_GRAPHICS_BIT){
            graphicsFamilyIndex = x;
            break;
        }
    }

    std::cout << "Шаг 3 пройден! Графическая очередь найдена под индексом: " << graphicsFamilyIndex << std::endl;

    // Step 4:

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex =  graphicsFamilyIndex;
    queueCreateInfo.queueCount = 1;

    float queueProperties = 1.0f;
    queueCreateInfo.pQueuePriorities = &queueProperties;

    VkPhysicalDeviceFeatures deviceFeaturs{};
    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.pEnabledFeatures = &deviceFeaturs;
    deviceCreateInfo.enabledExtensionCount = 0;
    
    VkDevice device; 
    VkResult device_result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);

    if(device_result != VK_SUCCESS){
        throw std::runtime_error("vkDeviceCreate failed");
    }

    // LOOP

    while(!myWindow.ShouldClose()){
        myWindow.PollEvents();
    }

    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);
    return 0;
}