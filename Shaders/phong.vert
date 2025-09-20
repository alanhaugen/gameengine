#version 330 core

// ES requires setting precision qualifier
// Can be mediump or highp
precision highp float; // affects all floats (vec3, vec4 etc)

// Thanks to https://web.archive.org/web/20180816064924/http://www.sunandblackcat.com/tipFullView.php?l=eng&topicid=30

// attributes
/*layout(location = 0) in vec3 i_position; // xyz - position
layout(location = 1) in vec3 i_normal; // xyz - normal
layout(location = 2) in vec2 i_texcoord0; // xy - texture coords*/

layout(location = 0) in vec3 i_position;        // object space vertex position
layout(location = 1) in vec4 vColor;	        // per-vertex colour
layout(location = 2) in vec3 i_normal;	        // per-vertex normals
layout(location = 3) in vec2 i_texcoord0;	// per-vertex texcoord

#ifdef VULKAN
layout(set = 0, binding = 0) uniform UniformBlock
{
  mat4 MVP;	// combined modelview projection matrix
  vec4 colour;
  vec4 time;
  vec4 i_index;
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
  vec4 colourTint;
  mat4 modelMat;
  mat4 normalMat;
  vec4 lightPosition;
  vec4 cameraPosition;
} uniformBuffer;

layout(location = 0) out vec3 o_normal;
layout(location = 1) out vec3 o_toLight;
layout(location = 2) out vec3 o_toCamera;
layout(location = 3) out vec2 o_texcoords;
layout(location = 4) out vec4 o_colour;
layout(location = 5) out float vTime;

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
    mat4 u_modelMat = uniformBuffer.modelMat;
    mat3 u_normalMat = mat3(uniformBuffer.normalMat);

    vec3 u_lightPosition = uniformBuffer.lightPosition.xyz;
    vec3 u_cameraPosition = uniformBuffer.cameraPosition.xyz;
    mat4 MVP = uniformBuffer.MVP;
    vec4 colour = uniformBuffer.colour;
    vTime = uniformBuffer.time.x;
#endif
    // position in world space
    vec4 worldPosition = u_modelMat * vec4(i_position, 1);

    // normal in world space
    o_normal = normalize(u_normalMat * i_normal);

    vec3 lightPos = u_lightPosition;
    lightPos.x += cos(vTime) * 1.0f;
    lightPos.y += cos(vTime) * 1.0f;
    lightPos.z += cos(vTime) * 1.0f;

    if (lightPos.z < 0)
    {
        lightPos.z *= -1.0f;
    }
    if (lightPos.x < 0)
    {
        lightPos.x *= -1.0f;
    }
    if (lightPos.y < 0)
    {
        lightPos.y *= -1.0f;
    }

    // direction to light
    o_toLight = normalize(lightPos - worldPosition.xyz);

    // direction to camera
    o_toCamera = normalize(u_cameraPosition - worldPosition.xyz);

    // texture coordinates to fragment shader
    o_texcoords = i_texcoord0;

    // screen space coordinates of the vertex
    gl_Position = MVP * worldPosition;

    // Set colour
    o_colour = colour;
}
