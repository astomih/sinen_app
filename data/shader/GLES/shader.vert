#version 300 es
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inRgba;
out vec2 outUV;
out vec4 outRgba;
uniform Matrices
{
  mat4 world;
  mat4 view;
  mat4 proj;
};
// Normal (in world space)
out vec3 fragNormal;
// Position (in world space)
out vec3 fragWorldPos;
void main()
{
  vec4 worldpos = vec4(inPos,1.0) * world;
	fragWorldPos = worldpos.xyz;
  gl_Position = proj * view * world * vec4(inPos,1.0);
	fragNormal = (world*vec4(inNormal, 0.0)).xyz;
  outUV = inUV;
  outRgba = inRgba;
}