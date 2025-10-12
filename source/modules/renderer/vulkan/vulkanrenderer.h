#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#include <QWindow>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include "vulkantexture.h"
#include "../vertex.h"
#include "../renderer.h"
#include "../../../x-platform/scene.h"

//Forward declarations
struct SwapChainSupportDetails;
struct QueueFamilyIndices;

const int MAX_DRAWABLES = 4000;

class VulkanRenderer : public QWindow, public Renderer
{
    Q_OBJECT
public:
    void Init() override;
    void Update() override;

    explicit VulkanRenderer(QWindow* parent = nullptr);
    ~VulkanRenderer();

    void initVulkan();
    Drawable& CreateDrawable(std::vector<Vertex> vertices,
                             std::vector<uint32_t> indices,
                             const char* vertexShader,
                             const char* fragmentShader,
                             const int topology = TRIANGLES,
                             std::vector<std::string> textures) override;

    void Render();

    void SetViewMatrix(glm::mat4 view) override;
    void SetCameraPosition(glm::vec3 pos) override;
    void SetLightPos(glm::vec3 pos) override;

protected:
private:
    int drawablesQuantity = 0;
    int texturesQuantity = 0;
    Drawable drawables[MAX_DRAWABLES];
    VulkanTexture textures[MAX_DRAWABLES];
    glm::mat4 cameraView;
    glm::vec3 cameraPos;
    glm::vec3 lightPos;

    size_t PadUniformBufferSize(size_t originalSize);
    VkPhysicalDeviceProperties deviceProperties;
    // class GLFWwindow* window;
    //GLFWwindow* window{nullptr};
    //QWindow* window{ nullptr }; //this object IS a QWindow

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout uniformSetLayout;
    VkDescriptorSetLayout textureSetLayout;
    VkPipelineLayout pipelineLayout;

    VkCommandPool commandPool;

    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    bool framebufferResized = false;

    // void initWindow();

    // static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    // ---- Functions ----

    void cleanupSwapChain();
    void cleanup();
    void recreateSwapChain();
    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    VkDescriptorSet createTextureDescriptor(std::string filePath, int textureID);
    VkPipeline createGraphicsPipeline(const char *vertexShaderPath,
                                      const char *fragmentShaderPath,
                                      const int topology = TRIANGLES);
    void createFramebuffers();
    void createCommandPool();
    void createColorResources();
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void createTextureImage(int textureID, std::string filePath);
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
    VkSampleCountFlagBits getMaxUsableSampleCount();
    void createTextureImageView(int textureID);
    void createTextureSampler(int textureID);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples,
                     VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                     VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createVertexBuffer(std::vector<Vertex> vertices, Drawable &drawable);
    void createIndexBuffer(std::vector<uint32_t> indices, Drawable &drawable);
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createCommandBuffers();
    void createSyncObjects();
    void updateUniformBuffer(uint32_t currentImage, Drawable::UniformBufferObject ubo, int offset);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    static std::vector<char> readFile(const std::string& filename);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent *eventPress) override;
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mouseMoveEvent(QMouseEvent *eventMove) override;
};



#endif // VULKANRENDERER_H
