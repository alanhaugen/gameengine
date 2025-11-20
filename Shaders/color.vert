#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 modelMat;
    mat4 normalMat;
    vec4 lightPosition;
    vec4 cameraPosition;
    vec4 time;
    vec4 index;
    vec4 pos;
    vec4 scaleX;
    vec4 scaleY;
    vec4 width;
    vec4 height;
    vec4 totalWidth;
    vec4 totalHeight;
    vec4 screenWidth;
    vec4 screenHeight;
    vec4 flip;
    vec4 flipVertical;
    vec4 colour;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;
layout(location = 4) in float inGlyph;          // per-vertex text glyph

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    gl_PointSize = 5.0;
    fragColor = inColor + ubo.colour.rgb;
    fragTexCoord = inTexCoord;
}
