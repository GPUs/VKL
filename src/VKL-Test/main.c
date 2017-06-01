#include <VKL/VKL.h>
#include <GLFW/glfw3.h>
#include <math.h>

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "VKL Test", NULL, NULL);
	
	VkBool32 debug = 0;
	
#ifdef _DEBUG
	debug = 1;
#endif

	VKLInstance* instance;
	vklCreateInstance(&instance, NULL, debug, NULL);
	
	VKLSurface* surface;
	vklCreateGLFWSurface(instance, &surface, window);

	VKLDevice* device;
	VKLDeviceGraphicsContext** deviceContexts;
	vklCreateDevice(instance, &device, &surface, 1, &deviceContexts, 0, NULL);

	VKLDeviceGraphicsContext* devCon = deviceContexts[0];
	
	VKLSwapChain* swapChain;
	vklCreateSwapChain(devCon, &swapChain, VK_TRUE);

	float data[] = {
		-0.8f, -0.8f, 1.0f, 0.0f,
		 0.0f,  0.8f, 0.0f, 1.0f,
		 0.8f, -0.8f, 0.0f, 0.0f
	};
	
	VKLBuffer* buffer;
	vklCreateStagedBuffer(devCon, &buffer, data, sizeof(float) * 3 * 4, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

	char* shaderPaths[2];
	shaderPaths[0] = "res/basic-vert.spv";
	shaderPaths[1] = "res/basic-frag.spv";

	VkShaderStageFlagBits stages[2];
	stages[0] = VK_SHADER_STAGE_VERTEX_BIT;
	stages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;

	size_t offsets[2] = {0, sizeof(float) * 2};
	VkFormat formats[2] = { VK_FORMAT_R32G32_SFLOAT, VK_FORMAT_R32G32_SFLOAT };

	VkDescriptorSetLayoutBinding bindings[2];
	bindings[0].binding = 0;
	bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindings[0].descriptorCount = 1;
	bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	bindings[0].pImmutableSamplers = NULL;

	bindings[1].binding = 1;
	bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	bindings[1].descriptorCount = 1;
	bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	bindings[1].pImmutableSamplers = NULL;

	VKLShaderCreateInfo shaderCreateInfo;
	memset(&shaderCreateInfo, 0, sizeof(VKLShaderCreateInfo));
	shaderCreateInfo.shaderPaths = shaderPaths;
	shaderCreateInfo.shaderStages = stages;
	shaderCreateInfo.shaderCount = 2;
	shaderCreateInfo.bindings = bindings;
	shaderCreateInfo.bindingsCount = 2;
	shaderCreateInfo.vertexInputAttributeStride = sizeof(float) * 4;
	shaderCreateInfo.vertexInputAttributesCount = 2;
	shaderCreateInfo.vertexInputAttributeOffsets = offsets;
	shaderCreateInfo.vertexInputAttributeFormats = formats;

	VKLShader* shader;
	vklCreateShader(device, &shader, &shaderCreateInfo);

	VKLPipelineCreateInfo pipelineCreateInfo;
	memset(&pipelineCreateInfo, 0, sizeof(VKLPipelineCreateInfo));
	pipelineCreateInfo.shader = shader;
	pipelineCreateInfo.renderPass = swapChain->renderPass;
	pipelineCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	pipelineCreateInfo.cullMode = VK_CULL_MODE_NONE;
	pipelineCreateInfo.extent.width = swapChain->width;
	pipelineCreateInfo.extent.height = swapChain->height;

	VKLGraphicsPipeline* pipeline;
	vklCreateGraphicsPipeline(device, &pipeline, &pipelineCreateInfo);
	
	VkCommandBuffer cmdBuffer;
	vklAllocateCommandBuffer(devCon, &cmdBuffer, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1);

	VKLUniformObject* uniform;
	vklCreateUniformObject(device, &uniform, shader);

	float proj[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	VKLBuffer* uniformBuffer;
	vklCreateBuffer(device, &uniformBuffer, VK_FALSE, sizeof(float) * 16, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
	
	vklSetUniformBuffer(device, uniform, uniformBuffer, 0);

	uint8_t imageData[16] = {
		255,   0, 255, 255,      0, 255,   0, 255,
		  0, 255,   0, 255,    255,   0, 255, 255
	};

	VKLTextureCreateInfo textureCreateInfo;
	textureCreateInfo.width = 2;
	textureCreateInfo.height = 2;
	textureCreateInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	textureCreateInfo.tiling = VK_IMAGE_TILING_LINEAR;
	textureCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;

	VKLTexture* texture;
	vklCreateTexture(device, &texture, &textureCreateInfo, VK_FALSE);
	vklSetTextureData(device, texture, imageData);
	//vklCreateStagedTexture(devCon, &texture, &textureCreateInfo, imageData);

	vklSetUniformTexture(device, uniform, texture, 1);

	vklSetClearColor(swapChain, 0.25f, 0.45f, 1.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		vklClearScreen(swapChain);

		vklBeginRenderRecording(swapChain, cmdBuffer);
		
		VkViewport viewport = { 0, 0, swapChain->width, swapChain->height, 0, 1 };
		VkRect2D scissor = { 0, 0, swapChain->width, swapChain->height };
		VkDeviceSize offsets = 0;

		device->pvkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
		device->pvkCmdSetScissor(cmdBuffer, 0, 1, &scissor);
		
		device->pvkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipeline);
		device->pvkCmdBindVertexBuffers(cmdBuffer, 0, 1, &buffer->buffer, &offsets);

		proj[12] = glfwGetTime()/10.0f;

		vklWriteToMemory(device, uniformBuffer->memory, proj, sizeof(float) * 16);

		device->pvkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, 
			pipeline->pipelineLayout, 0, 1, &uniform->descriptorSet, 0, NULL);

		device->pvkCmdDraw(cmdBuffer, 3, 1, 0, 0);
		
		vklEndRenderRecording(swapChain, cmdBuffer);

		vklRenderRecording(swapChain, cmdBuffer);

		vklSwapBuffers(swapChain);
	}

	vklDestroyUniformObject(device, uniform);
	vklDestroyGraphicsPipeline(device, pipeline);
	vklDestroyShader(device, shader);
	vklDestroyBuffer(device, uniformBuffer);
	vklDestroyBuffer(device, buffer);
	vklDestroySwapChain(swapChain);
	vklDestroyDevice(device);
	vklDestroySurface(instance, surface);
	vklDestroyInstance(instance);

	glfwTerminate();
	
	printf("Enter a key to exit:");
	getchar();
	return 0;
}
