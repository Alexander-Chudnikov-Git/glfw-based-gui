#version 330 compatibility

layout(triangles) in;
layout(triangle_strip, max_vertices=6) out;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

in vec4 normal[];

out vec4 vertex_color;

void main()
{   
  mat4 modelViewMatrix = viewMatrix * modelMatrix;
  mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
  int i;
  
  //====== First triangle - identical to the input one.
  //
  for(i=0; i<3; i++)
  {
    vec4 view_pos = modelViewMatrix * gl_in[i].gl_Position;
    gl_Position = projectionMatrix * view_pos;
    vertex_color = vec4(0.0, 1.0, 0.0, 1.0);
    EmitVertex();
  }
  EndPrimitive();
  
  //====== Second triangle - translated version of the 
  // input triangle.
  //
  for(i=0; i<3; i++)
  {
    vec4 N =  normal[i];
    vec4 world_pos = modelMatrix * (gl_in[i].gl_Position + normalize(N) * 10.0);
    gl_Position = viewProjectionMatrix * world_pos;
    vertex_color = vec4(1.0, 1.0, 0.0, 1.0);
    EmitVertex();
  }
  EndPrimitive();
}