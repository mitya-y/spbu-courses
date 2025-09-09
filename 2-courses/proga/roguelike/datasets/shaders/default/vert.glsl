#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 color;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_tex_coord;
out vec3 frag_color;

uniform mat4 MVP;

void main() {
  vec4 pos = vec4(position, 1);
  gl_Position = MVP * pos;

  frag_color = color;
  frag_pos = position;
  frag_normal = normal;
  frag_tex_coord = tex_coord;
}
