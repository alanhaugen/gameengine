#ifndef RENDERER_H
#define RENDERER_H

#include <QWindow>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include "Editor/MainWindow.h"
#include "QDirIterator"
#include "AssetManager/AssetManager.h"
#include "AssetManager/Texture.h"
#include "AssetManager/Mesh.h"
#include "ECS/Components.h"
#include "Vertex.h"
#include "Camera.h"

//Forward declarations
struct SwapChainSupportDetails;
struct QueueFamilyIndices;

class Renderer : public QWindow
{
    Q_OBJECT
public:
    explicit Renderer(QWindow* parent = nullptr);
    ~Renderer();

    void initVulkan();
    ObjAsset* obj_asset{nullptr};
    AssetManager<ObjAsset>* objManager=new AssetManager<ObjAsset>();
    bool filesImported=false;
    void drawFrame();
    void initComponents(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents,
                        std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures);
    void updateCompoments(std::vector<gea::RenderComponent> renderComponents, std::vector<gea::TransformComponent> transformComponents);
    gea::RenderComponent CreateComponent(std::string, std::string, int);

    std::vector<gea::RenderComponent> mRenderComponents;
    std::vector<gea::RenderComponent> mDynamicRenderComponents;
    std::vector<gea::RenderComponent> mStaticRenderComponents;

    gea::Engine* mEngine{nullptr};
    Camera mCamera; //probably should be a pointer to this
    class MainWindow* mMainWindow{nullptr};

protected:
    //Qt event handlers - called when requestUpdate(); is called
    void exposeEvent(QExposeEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool event(QEvent* event) override;

    //Qts input functions - just forward it to MainWindow for now
    //This way the samt thing will happen if the focus is in the Renderer or MainWindow widgets
    void keyPressEvent(QKeyEvent *event) override           {mMainWindow->keyPressEvent(event);};
    void keyReleaseEvent(QKeyEvent *event) override         {mMainWindow->keyReleaseEvent(event);};
    void mousePressEvent(QMouseEvent *event) override       {mMainWindow->mousePressEvent(event);};
    void mouseReleaseEvent(QMouseEvent *event) override     {mMainWindow->mouseReleaseEvent(event);};
    void mouseMoveEvent(QMouseEvent *event) override        {mMainWindow->mouseMoveEvent(event);};
    void wheelEvent(QWheelEvent *event) override            {mMainWindow->wheelEvent(event);};

private:

    friend class MainWindow;
    // class GLFWwindow* window;
    //GLFWwindow* window{nullptr};
    //QWindow* window{ nullptr }; //this object IS a QWindow

    //These variables are not renamed to mInstance etc, to be similar to
    //https://vulkan-tutorial.com/ where they came from
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
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

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

    std::vector<VkCommandBuffer> staticCommandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    bool framebufferResized = false;

    //Bias version
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    //QSet<QString> filesSet=objManager->filesNamesSet;
    std::vector<gea::Mesh> mMeshes;
    std::vector<gea::Texture> mTextures;
    //this is done for testing sake. in the real ecs there would only be one vector of transform components
    std::vector<gea::TransformComponent> mDynamicTransformComponents;
    std::vector<gea::TransformComponent> mStaticTransformComponents;



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
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createColorResources();
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void createTextureImage(gea::Texture* texture);
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
    VkSampleCountFlagBits getMaxUsableSampleCount();
    void createTextureImageView(gea::Texture* texture);
    void createTextureSampler(gea::Texture* texture);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples,
                     VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties,
                     VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void loadModel(QString MODEL_PATH);
    void importObjects();;
    void createVertexBuffer();
    void createIndexBuffer();
    void createVertexBuffer(gea::Mesh* mesh);
    void createIndexBuffer(gea::Mesh* mesh);
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets(gea::Texture texture);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createCommandBuffers();
    void createSyncObjects();
    void updateUniformBuffer(uint32_t currentImage);
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
};



#endif // RENDERER_H
