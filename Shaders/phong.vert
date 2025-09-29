#version 450 core

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPosition;
    vec3 cameraPosition;
    float time;
} ubo;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoords;

layout(location = 0) out vec3 FragPos;
layout(location = 1) out vec3 Normal;
layout(location = 2) out vec2 TexCoords;
layout(location = 3) out vec3 lightPos;
layout(location = 4) out vec3 cameraPos;
layout(location = 5) out float time;

void main()
{
    FragPos = aPos;
    Normal = aNormal;
    lightPos = ubo.lightPosition;
    cameraPos = ubo.cameraPosition;
    TexCoords = aTexCoords;
    time = ubo.time;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(aPos, 1.0);
}
