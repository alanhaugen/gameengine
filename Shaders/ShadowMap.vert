#version 450

layout(binding = 0) uniform LightUniformBufferObject {
    mat4 lightViewProj;
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
} pc;

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = ubo.lightViewProj * pc.model * vec4(aPos, 1.0);
}