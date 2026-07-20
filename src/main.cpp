#include <iostream>
#include "windows_layer/windows_manager.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>

int main(){
    Window myWindow(680, 840, "HELLOW_WORLD");
    std::vector<const char*> extensions = myWindow.GetRequiredExtensions();

    // Step 1: Vulkan Instance 

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "My Engien";
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = 0;

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
    const char* deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    deviceCreateInfo.enabledExtensionCount = 1;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

    VkDevice device; 
    VkResult device_result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);

    if(device_result != VK_SUCCESS){
        throw std::runtime_error("vkDeviceCreate failed");
    }

    //Step 5:

    VkSurfaceKHR surface;
    myWindow.CreateWindowSurface(instance, &surface);

    //Step 6: 

    VkSwapchainCreateInfoKHR swapChainCreateInfo{};
    swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainCreateInfo.surface = surface;
    swapChainCreateInfo.minImageCount = 2; 
    swapChainCreateInfo.imageExtent = VkExtent2D{680, 840};
    swapChainCreateInfo.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
    swapChainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapChainCreateInfo.queueFamilyIndexCount = 0;
    swapChainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapChainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    swapChainCreateInfo.clipped = VK_TRUE;
    swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapChain;
    if(vkCreateSwapchainKHR(device, &swapChainCreateInfo, nullptr, &swapChain) != VK_SUCCESS){
        throw std::runtime_error("FAILED TO CREATE SWAPCHAIN");
    };

    uint32_t ImageCount = 0; 
    vkGetSwapchainImagesKHR(device, swapChain, &ImageCount, nullptr);

    std::vector<VkImage> swapChainImages(ImageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &ImageCount, swapChainImages.data());
    // LOOP

    while(!myWindow.ShouldClose()){
        myWindow.PollEvents();
    }
    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    return 0;
}