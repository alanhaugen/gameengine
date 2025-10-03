#version 450 core

// ES requires setting precision qualifier
// Can be mediump or highp
precision highp float; // affects all floats (vec3, vec4 etc)

// Thanks to https://web.archive.org/web/20180816064924/http://www.sunandblackcat.com/tipFullView.php?l=eng&topicid=30

// attributes
/*layout(location = 0) in vec3 i_position; // xyz - position
layout(location = 1) in vec3 i_normal; // xyz - normal
layout(location = 2) in vec2 i_texcoord0; // xy - texture coords*/

layout(location = 0) in vec3 inPosition;        // object space vertex position
layout(location = 1) in vec3 inColor;	        // per-vertex colour
layout(location = 2) in vec3 inNormal;	        // per-vertex normals
layout(location = 3) in vec2 inTexcoord;	// per-vertex texcoord

#ifdef VULKAN
layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat4 modelMat;
    mat4 normalMat;
    vec4 lightPosition;
    vec4 cameraPosition;
    float time;
} ubo;

layout(location = 0) out vec3 o_normal;
layout(location = 1) out vec3 o_toLight;
layout(location = 2) out vec3 o_toCamera;
layout(location = 3) out vec2 o_texcoords;
layout(location = 4) out vec4 o_colour;

#else

// matrices
uniform mat4 u_modelMat;
uniform mat3 u_normalMat;

// position of light and camera
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

// data for fragment shader
out vec3 o_normal;
out vec3 o_toLight;
out vec3 o_toCamera;
out vec2 o_texcoords;

uniform vec4 colour;
out vec4 o_colour;
uniform mat4 MVP;	// combined modelview projection matrix
#endif

///////////////////////////////////////////////////////////////////

void main(void)
{
#ifdef VULKAN
    mat4 u_modelMat = ubo.modelMat;
    mat3 u_normalMat = mat3(ubo.normalMat);

    vec3 u_lightPosition = ubo.lightPosition.xyz;
    vec3 u_cameraPosition = ubo.cameraPosition.xyz;
    mat4 MVP = ubo.proj * ubo.view * ubo.model;
#endif
    // position in world space
    vec4 worldPosition = u_modelMat * vec4(inPosition, 1);

    // normal in world space
    o_normal = normalize(u_normalMat * inNormal);

    // direction to light
    o_toLight = normalize(u_lightPosition - worldPosition.xyz);

    // direction to camera
    o_toCamera = normalize(u_cameraPosition - worldPosition.xyz);

    // texture coordinates to fragment shader
    o_texcoords = inTexcoord;

    // screen space coordinates of the vertex
    gl_Position = MVP * worldPosition;
}
