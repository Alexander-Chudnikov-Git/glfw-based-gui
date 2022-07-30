#version 330 compatibility

out vec4 normal;

void main()
{   
  gl_Position = gl_Vertex;
  normal =  vec4(gl_Normal.xyz, 0.0);
}