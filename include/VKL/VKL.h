#pragma once

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void VLKCheck(VkResult result, char *msg);
void* malloc_c(size_t size);
void free_c(void* block);
void* realloc_c(void* pOriginal, size_t size);

struct VKLInstance;
struct VKLDevice;
struct VKLDeviceGraphicsContext;
struct VKLDeviceComputeContext;
struct VKLSwapChain;

typedef struct VKLInstance VKLInstance;
typedef struct VKLDevice VKLDevice;
typedef struct VKLDeviceGraphicsContext VKLDeviceGraphicsContext;
typedef struct VKLDeviceComputeContext VKLDeviceComputeContext;
typedef struct VKLSwapChain VKLSwapChain;

typedef struct VKLInstance {
	PFN_vkCreateInstance pvkCreateInstance;
	PFN_vkDestroyInstance pvkDestroyInstance;
	PFN_vkEnumeratePhysicalDevices pvkEnumeratePhysicalDevices;
	PFN_vkGetPhysicalDeviceFeatures pvkGetPhysicalDeviceFeatures;
	PFN_vkGetPhysicalDeviceFormatProperties pvkGetPhysicalDeviceFormatProperties;
	PFN_vkGetPhysicalDeviceImageFormatProperties pvkGetPhysicalDeviceImageFormatProperties;
	PFN_vkGetPhysicalDeviceProperties pvkGetPhysicalDeviceProperties;
	PFN_vkGetPhysicalDeviceQueueFamilyProperties pvkGetPhysicalDeviceQueueFamilyProperties;
	PFN_vkGetPhysicalDeviceMemoryProperties pvkGetPhysicalDeviceMemoryProperties;
	PFN_vkGetInstanceProcAddr pvkGetInstanceProcAddr;
	PFN_vkCreateDevice pvkCreateDevice;
	PFN_vkDestroyDevice pvkDestroyDevice;
	PFN_vkEnumerateInstanceExtensionProperties pvkEnumerateInstanceExtensionProperties;
	PFN_vkEnumerateDeviceExtensionProperties pvkEnumerateDeviceExtensionProperties;
	PFN_vkEnumerateInstanceLayerProperties pvkEnumerateInstanceLayerProperties;
	PFN_vkEnumerateDeviceLayerProperties pvkEnumerateDeviceLayerProperties;

	PFN_vkCreateDebugReportCallbackEXT pvkCreateDebugReportCallbackEXT;
	PFN_vkDestroyDebugReportCallbackEXT pvkDestroyDebugReportCallbackEXT;

	PFN_vkDestroySurfaceKHR pvkDestroySurfaceKHR;
	PFN_vkGetPhysicalDeviceSurfaceSupportKHR pvkGetPhysicalDeviceSurfaceSupportKHR;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pvkGetPhysicalDeviceSurfaceCapabilitiesKHR;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pvkGetPhysicalDeviceSurfaceFormatsKHR;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pvkGetPhysicalDeviceSurfacePresentModesKHR;

	PFN_vkGetPhysicalDeviceDisplayPropertiesKHR pvkGetPhysicalDeviceDisplayPropertiesKHR;
	PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR pvkGetPhysicalDeviceDisplayPlanePropertiesKHR;
	PFN_vkGetDisplayPlaneSupportedDisplaysKHR pvkGetDisplayPlaneSupportedDisplaysKHR;
	PFN_vkGetDisplayModePropertiesKHR pvkGetDisplayModePropertiesKHR;
	PFN_vkCreateDisplayModeKHR pvkCreateDisplayModeKHR;
	PFN_vkGetDisplayPlaneCapabilitiesKHR pvkGetDisplayPlaneCapabilitiesKHR;
	PFN_vkCreateDisplayPlaneSurfaceKHR pvkCreateDisplayPlaneSurfaceKHR;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	VkAllocationCallbacks* allocator;

	int layerCount;
	char** layers;

	VkBool32 debug;
} VKLInstance;

typedef struct VKLDevice {
	PFN_vkGetDeviceProcAddr pvkGetDeviceProcAddr;
	PFN_vkGetDeviceQueue pvkGetDeviceQueue;
	PFN_vkQueueSubmit pvkQueueSubmit;
	PFN_vkQueueWaitIdle pvkQueueWaitIdle;
	PFN_vkDeviceWaitIdle pvkDeviceWaitIdle;
	PFN_vkAllocateMemory pvkAllocateMemory;
	PFN_vkFreeMemory pvkFreeMemory;
	PFN_vkMapMemory pvkMapMemory;
	PFN_vkUnmapMemory pvkUnmapMemory;
	PFN_vkFlushMappedMemoryRanges pvkFlushMappedMemoryRanges;
	PFN_vkInvalidateMappedMemoryRanges pvkInvalidateMappedMemoryRanges;
	PFN_vkGetDeviceMemoryCommitment pvkGetDeviceMemoryCommitment;
	PFN_vkBindBufferMemory pvkBindBufferMemory;
	PFN_vkBindImageMemory pvkBindImageMemory;
	PFN_vkGetBufferMemoryRequirements pvkGetBufferMemoryRequirements;
	PFN_vkGetImageMemoryRequirements pvkGetImageMemoryRequirements;
	PFN_vkGetImageSparseMemoryRequirements pvkGetImageSparseMemoryRequirements;
	PFN_vkGetPhysicalDeviceSparseImageFormatProperties pvkGetPhysicalDeviceSparseImageFormatProperties;
	PFN_vkQueueBindSparse pvkQueueBindSparse;
	PFN_vkCreateFence pvkCreateFence;
	PFN_vkDestroyFence pvkDestroyFence;
	PFN_vkResetFences pvkResetFences;
	PFN_vkGetFenceStatus pvkGetFenceStatus;
	PFN_vkWaitForFences pvkWaitForFences;
	PFN_vkCreateSemaphore pvkCreateSemaphore;
	PFN_vkDestroySemaphore pvkDestroySemaphore;
	PFN_vkCreateEvent pvkCreateEvent;
	PFN_vkDestroyEvent pvkDestroyEvent;
	PFN_vkGetEventStatus pvkGetEventStatus;
	PFN_vkSetEvent pvkSetEvent;
	PFN_vkResetEvent pvkResetEvent;
	PFN_vkCreateQueryPool pvkCreateQueryPool;
	PFN_vkDestroyQueryPool pvkDestroyQueryPool;
	PFN_vkGetQueryPoolResults pvkGetQueryPoolResults;
	PFN_vkCreateBuffer pvkCreateBuffer;
	PFN_vkDestroyBuffer pvkDestroyBuffer;
	PFN_vkCreateBufferView pvkCreateBufferView;
	PFN_vkDestroyBufferView pvkDestroyBufferView;
	PFN_vkCreateImage pvkCreateImage;
	PFN_vkDestroyImage pvkDestroyImage;
	PFN_vkGetImageSubresourceLayout pvkGetImageSubresourceLayout;
	PFN_vkCreateImageView pvkCreateImageView;
	PFN_vkDestroyImageView pvkDestroyImageView;
	PFN_vkCreateShaderModule pvkCreateShaderModule;
	PFN_vkDestroyShaderModule pvkDestroyShaderModule;
	PFN_vkCreatePipelineCache pvkCreatePipelineCache;
	PFN_vkDestroyPipelineCache pvkDestroyPipelineCache;
	PFN_vkGetPipelineCacheData pvkGetPipelineCacheData;
	PFN_vkMergePipelineCaches pvkMergePipelineCaches;
	PFN_vkCreateGraphicsPipelines pvkCreateGraphicsPipelines;
	PFN_vkCreateComputePipelines pvkCreateComputePipelines;
	PFN_vkDestroyPipeline pvkDestroyPipeline;
	PFN_vkCreatePipelineLayout pvkCreatePipelineLayout;
	PFN_vkDestroyPipelineLayout pvkDestroyPipelineLayout;
	PFN_vkCreateSampler pvkCreateSampler;
	PFN_vkDestroySampler pvkDestroySampler;
	PFN_vkCreateDescriptorSetLayout pvkCreateDescriptorSetLayout;
	PFN_vkDestroyDescriptorSetLayout pvkDestroyDescriptorSetLayout;
	PFN_vkCreateDescriptorPool pvkCreateDescriptorPool;
	PFN_vkDestroyDescriptorPool pvkDestroyDescriptorPool;
	PFN_vkResetDescriptorPool pvkResetDescriptorPool;
	PFN_vkAllocateDescriptorSets pvkAllocateDescriptorSets;
	PFN_vkFreeDescriptorSets pvkFreeDescriptorSets;
	PFN_vkUpdateDescriptorSets pvkUpdateDescriptorSets;
	PFN_vkCreateFramebuffer pvkCreateFramebuffer;
	PFN_vkDestroyFramebuffer pvkDestroyFramebuffer;
	PFN_vkCreateRenderPass pvkCreateRenderPass;
	PFN_vkDestroyRenderPass pvkDestroyRenderPass;
	PFN_vkGetRenderAreaGranularity pvkGetRenderAreaGranularity;
	PFN_vkCreateCommandPool pvkCreateCommandPool;
	PFN_vkDestroyCommandPool pvkDestroyCommandPool;
	PFN_vkResetCommandPool pvkResetCommandPool;
	PFN_vkAllocateCommandBuffers pvkAllocateCommandBuffers;
	PFN_vkFreeCommandBuffers pvkFreeCommandBuffers;
	PFN_vkBeginCommandBuffer pvkBeginCommandBuffer;
	PFN_vkEndCommandBuffer pvkEndCommandBuffer;
	PFN_vkResetCommandBuffer pvkResetCommandBuffer;
	PFN_vkCmdBindPipeline pvkCmdBindPipeline;
	PFN_vkCmdSetViewport pvkCmdSetViewport;
	PFN_vkCmdSetScissor pvkCmdSetScissor;
	PFN_vkCmdSetLineWidth pvkCmdSetLineWidth;
	PFN_vkCmdSetDepthBias pvkCmdSetDepthBias;
	PFN_vkCmdSetBlendConstants pvkCmdSetBlendConstants;
	PFN_vkCmdSetDepthBounds pvkCmdSetDepthBounds;
	PFN_vkCmdSetStencilCompareMask pvkCmdSetStencilCompareMask;
	PFN_vkCmdSetStencilWriteMask pvkCmdSetStencilWriteMask;
	PFN_vkCmdSetStencilReference pvkCmdSetStencilReference;
	PFN_vkCmdBindDescriptorSets pvkCmdBindDescriptorSets;
	PFN_vkCmdBindIndexBuffer pvkCmdBindIndexBuffer;
	PFN_vkCmdBindVertexBuffers pvkCmdBindVertexBuffers;
	PFN_vkCmdDraw pvkCmdDraw;
	PFN_vkCmdDrawIndexed pvkCmdDrawIndexed;
	PFN_vkCmdDrawIndirect pvkCmdDrawIndirect;
	PFN_vkCmdDrawIndexedIndirect pvkCmdDrawIndexedIndirect;
	PFN_vkCmdDispatch pvkCmdDispatch;
	PFN_vkCmdDispatchIndirect pvkCmdDispatchIndirect;
	PFN_vkCmdCopyBuffer pvkCmdCopyBuffer;
	PFN_vkCmdCopyImage pvkCmdCopyImage;
	PFN_vkCmdBlitImage pvkCmdBlitImage;
	PFN_vkCmdCopyBufferToImage pvkCmdCopyBufferToImage;
	PFN_vkCmdCopyImageToBuffer pvkCmdCopyImageToBuffer;
	PFN_vkCmdUpdateBuffer pvkCmdUpdateBuffer;
	PFN_vkCmdFillBuffer pvkCmdFillBuffer;
	PFN_vkCmdClearColorImage pvkCmdClearColorImage;
	PFN_vkCmdClearDepthStencilImage pvkCmdClearDepthStencilImage;
	PFN_vkCmdClearAttachments pvkCmdClearAttachments;
	PFN_vkCmdResolveImage pvkCmdResolveImage;
	PFN_vkCmdSetEvent pvkCmdSetEvent;
	PFN_vkCmdResetEvent pvkCmdResetEvent;
	PFN_vkCmdWaitEvents pvkCmdWaitEvents;
	PFN_vkCmdPipelineBarrier pvkCmdPipelineBarrier;
	PFN_vkCmdBeginQuery pvkCmdBeginQuery;
	PFN_vkCmdEndQuery pvkCmdEndQuery;
	PFN_vkCmdResetQueryPool pvkCmdResetQueryPool;
	PFN_vkCmdWriteTimestamp pvkCmdWriteTimestamp;
	PFN_vkCmdCopyQueryPoolResults pvkCmdCopyQueryPoolResults;
	PFN_vkCmdPushConstants pvkCmdPushConstants;
	PFN_vkCmdBeginRenderPass pvkCmdBeginRenderPass;
	PFN_vkCmdNextSubpass pvkCmdNextSubpass;
	PFN_vkCmdEndRenderPass pvkCmdEndRenderPass;
	PFN_vkCmdExecuteCommands pvkCmdExecuteCommands;

	PFN_vkCreateSwapchainKHR pvkCreateSwapchainKHR;
	PFN_vkDestroySwapchainKHR pvkDestroySwapchainKHR;
	PFN_vkGetSwapchainImagesKHR pvkGetSwapchainImagesKHR;
	PFN_vkAcquireNextImageKHR pvkAcquireNextImageKHR;
	PFN_vkQueuePresentKHR pvkQueuePresentKHR;

	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties physicalDeviceProperties;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	VkDevice device;

	VKLInstance* instance;
	uint32_t deviceGraphicsContextCount;
	uint32_t deviceComputeContextCount;
	VKLDeviceGraphicsContext** deviceGraphicsContexts;
	VKLDeviceComputeContext** deviceComputeContexts;
} VKLDevice;

typedef struct VKLDeviceGraphicsContext {
	GLFWwindow* window;
	VkSurfaceKHR surface;

	uint32_t queueIdx;
	VkQueue queue;
	VkCommandPool commandPool;
	VkCommandBuffer setupCmdBuffer;

	VKLDevice* device;
} VKLDeviceGraphicsContext;

typedef struct VKLDeviceComputeContext {
	uint32_t queueIdx;
	VkQueue queue;
	VkCommandPool commandPool;
	VkCommandBuffer setupCmdBuffer;

	VKLDevice* device;
} VKLDeviceComputeContext;

typedef struct VKLSwapChain {
	VkSwapchainKHR swapChain;
	VkImage* presentImages;
	VkImageView *presentImageViews;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	VkRenderPass renderPass;
	VkFramebuffer* frameBuffers;
	VkSemaphore presentCompleteSemaphore, renderingCompleteSemaphore;
	
	uint32_t width, height, nextImageIdx, imageCount;

	VKLDeviceGraphicsContext* context;
} VKLSwapChain;

int vklCreateInstance(VKLInstance** pInstace, VkAllocationCallbacks* allocator, VkBool32 debug);
int vklDestroyInstance(VKLInstance* instance);

int vklCreateDevice(VKLInstance* instance, VKLDevice** pDevice, GLFWwindow** pWindows,
	uint32_t deviceGraphicsContextCount, VKLDeviceGraphicsContext*** pDeviceGraphicsContexts,
	uint32_t deviceComputeContextCount, VKLDeviceComputeContext*** pDeviceComputeContexts);

int vklDestroyDevice(VKLDevice* device);

int vklAllocateCommandBuffer(VKLDeviceGraphicsContext* context, VkCommandBuffer* cmdBuffer, VkCommandBufferLevel level, uint32_t count);
int vklAllocateMemory(VKLDevice* device, VkDeviceMemory* memory, VkMemoryPropertyFlags desiredMemoryFlags, VkMemoryRequirements memoryRequirements);
int vklAllocateImageMemory(VKLDevice* device, VkDeviceMemory* memory, VkImage image, VkMemoryPropertyFlags desiredMemoryFlags);

int vklCreateSwapChain(VKLDeviceGraphicsContext* context, VKLSwapChain** swapChain, VkBool32 vSync);
int vklDestroySwapChain(VKLSwapChain* swapChain);