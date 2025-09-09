#version 410

out vec4 out_color;

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_tex_coord;
in vec3 frag_color;

uniform vec3 CameraPos;
uniform float Time;
uniform sampler2D Texture;

vec3 Shade() {
  float x = sin(Time);
  float y = cos(Time);

  vec3 LightDir = vec3(x, 1, y);
  LightDir = vec3(1, 1, 1);
  vec3 LightColor = vec3(1);
  vec3 Kd = frag_color;
  vec3 Ks = vec3(0.2);
  float Ph = 47.0;
  vec3 P = frag_pos;
  vec3 N = frag_normal;

  vec3 L = normalize(LightDir);
  vec3 color = vec3(0);
  vec3 V = normalize(P - CameraPos);

  N = faceforward(N, V, N);

  color += max(0, dot(N, L)) * Kd * LightColor;

  // Specular
  vec3 R = reflect(V, N);
  color += pow(max(0.1, dot(R, L)), Ph) * Ks * LightColor;
  return color;
}


void main() {
  vec3 color = vec3(0);
  color = Shade();
  color = texture(Texture, frag_tex_coord).xyz;
  out_color = vec4(color, 1);
  // out_color = vec4(1, 1, 1, 1);
}
