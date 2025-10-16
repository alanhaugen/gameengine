#version 450
layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 lightPos;
    vec3 viewPos;
} ubo;

layout(set = 1, binding = 0) uniform LightUniformBufferObject {
    mat4 lightViewProj;
} lightUniformBufferObject;

layout(push_constant) uniform PushConstants {
    mat4 model;
} pc;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec2 outTexCoords;
layout(location = 3) out vec3 outLightPos;
layout(location = 4) out vec3 outViewPos;
layout(location = 5) out vec4 fragPosLightSpace;

void main()
{
    outPos = aPos;
    outNormal = aNormal;
    outTexCoords = aTexCoords;
    outLightPos = ubo.lightPos;
    outViewPos = ubo.viewPos;
    fragPosLightSpace = lightUniformBufferObject.lightViewProj * pc.model * vec4(aPos, 1.0);
    gl_Position = ubo.proj * ubo.view * pc.model * vec4(aPos, 1.0);
}
