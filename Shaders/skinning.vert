#version 450

// Thanks to https://voxels.blogspot.com/2014/03/skinned-skeletal-animation-tutorial.html

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 colour;
    mat4 modelMat;
    mat4 normalMat;
    vec4 lightPosition;
    vec4 cameraPosition;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

uniform mat4 bones[100];
uniform int  use_skinning;
 
void main(void)
{
  mat4 mfinal = gl_ModelViewMatrix ;

  // skinning
  if(use_skinning==1)
  {
    vec3 weights= gl_Color.xyz;
    vec3 boneid = gl_Vertex.w * vec3( 1.0/128.0 , 1.0 , 128.0 );
    boneid = (boneid - floor(boneid))*128.0;

    mat4 mskin  = bones[int(boneid.x)]*weights.x+
                  bones[int(boneid.y)]*weights.y+
                  bones[int(boneid.z)]*weights.z;
    mfinal = mfinal * mskin;
  } 
  gl_Position = gl_ProjectionMatrix * mfinal * vec4(gl_Vertex.xyz,1.0);
}
