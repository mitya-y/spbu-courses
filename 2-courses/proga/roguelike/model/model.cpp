#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

// #define OBJL_CONSOLE_OUTPUT
#include "OBJ-Loader/Source/OBJ_Loader.h"

#include "application.hpp"
#include "model.h"

void Model::load_shader(const std::string &shader_name) {
  // open files
  constexpr auto shaders_base_directory = ASSETS_DIRECTORY "/shaders/";
  std::string shader_directory = shaders_base_directory + shader_name + '/';

  std::string vertex_file_path = shader_directory + "vert.glsl";
  std::ifstream vert_file(vertex_file_path.data());
  if (not vert_file) {
    throw std::runtime_error("cant open shader" + vertex_file_path);
  }

  std::string fragment_file_path = shader_directory + "frag.glsl";
  std::ifstream fraq_file(fragment_file_path.data());
  if (not fraq_file) {
    throw std::runtime_error("cant open shader" + fragment_file_path);
  }

  // load data
  std::stringstream sstr_vert;
  sstr_vert << vert_file.rdbuf();
  std::string vert_code = sstr_vert.str();

  std::stringstream sstr_frag;
  sstr_frag << fraq_file.rdbuf();
  std::string frag_code = sstr_frag.str();

  // compile shaders
  int error_info_lenght = 0;

  // Compile Vertex Shader
  GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
  char const *vert_data = vert_code.c_str();
  glShaderSource(vert_id, 1, &vert_data, nullptr);
  glCompileShader(vert_id);

  // Check Vertex Shader
  glGetShaderiv(vert_id, GL_INFO_LOG_LENGTH, &error_info_lenght);
  if (error_info_lenght > 0) {
    std::vector<char> error_msg(error_info_lenght + 1);
    glGetShaderInfoLog(vert_id, error_info_lenght, nullptr, error_msg.data());
    printf("%s\n", error_msg.data());
    // throw std::runtime_error("shader compile error");
  }

  // Compile Fragment Shader
  GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
  char const *frag_data = frag_code.c_str();
  glShaderSource(frag_id, 1, &frag_data, nullptr);
  glCompileShader(frag_id);

  // Check Fragment Shader
  glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &error_info_lenght);
  if (error_info_lenght > 0) {
    std::vector<char> error_msg(error_info_lenght + 1);
    glGetShaderInfoLog(frag_id, error_info_lenght, nullptr, error_msg.data());
    printf("%s\n", error_msg.data());
    // throw std::runtime_error("shader compile error");
  }

  // Link the program
  _program_id = glCreateProgram();
  glAttachShader(_program_id, vert_id);
  glAttachShader(_program_id, frag_id);
  glLinkProgram(_program_id);

  // Check the program
  glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &error_info_lenght);
  if (error_info_lenght > 0) {
    std::vector<char> error_msg(error_info_lenght + 1);
    glGetProgramInfoLog(_program_id, error_info_lenght, nullptr,
                        error_msg.data());
    printf("%s\n", error_msg.data());
    // throw std::runtime_error("shader compile error");
  }

  glDetachShader(_program_id, vert_id);
  glDetachShader(_program_id, frag_id);

  glDeleteShader(vert_id);
  glDeleteShader(frag_id);
}

static constexpr float float_threshold = 0.000001;

Model::Model(std::string_view path, std::string_view filename) {
  default_position();
  _is_loaded = true;

  objl::Loader loader;
  std::string full_filename =
      std::string(ASSETS_DIRECTORY) + '/' + path.data() + '/' + filename.data();
  if (!loader.LoadFile(full_filename)) {
    throw std::runtime_error("file not exists");
  }

  _model_datas.reserve(loader.LoadedMeshes.size());
  for (auto &mesh : loader.LoadedMeshes) {
    const auto &mesh_verts = mesh.Vertices;
    std::vector<Vertex> vertexes(mesh_verts.size());
    for (int i = 0; i < mesh_verts.size(); i++) {
      vertexes[i].position.x = mesh_verts[i].Position.X;
      vertexes[i].position.y = mesh_verts[i].Position.Y;
      vertexes[i].position.z = mesh_verts[i].Position.Z;

      vertexes[i].normal.x = mesh_verts[i].Normal.X;
      vertexes[i].normal.y = mesh_verts[i].Normal.Y;
      vertexes[i].normal.z = mesh_verts[i].Normal.Z;

      vertexes[i].texture_coords.x = mesh_verts[i].TextureCoordinate.X;
      vertexes[i].texture_coords.y = mesh_verts[i].TextureCoordinate.Y;

      vertexes[i].color = {1, 1, 1};
    }

    _model_datas.emplace_back(vertexes, mesh.Indices);
    auto tex_name = mesh.MeshMaterial.map_Kd;
    if (tex_name.back() == '\r') {
      tex_name.resize(tex_name.size() - 1);
    }
    auto full_name =
        std::string(ASSETS_DIRECTORY) + '/' + path.data() + '/' + tex_name;
    // std::cout << full_name << std::endl;
    _model_datas.back().load_texture(full_name);
  }

  auto shader_path = "default";
  load_shader(shader_path);
  // load_texture(ASSETS_DIRECTORY "/textures/image_2024-08-04_00-57-12.png");

  // calculate_bound_box(vertexes);
}

Model::Model(GeometryType geom_type, const std::string &shader_path)
    : _type(geom_type) {
  default_position();
  _is_loaded = false;

  std::vector<Vertex> vertexes;
  std::vector<uint32_t> indexes;

  switch (geom_type) {
  case GeometryType::Cube:
    load_cube(vertexes, indexes, {0, 0, 0}, {});
    break;
  case GeometryType::Sphere:
    load_sphere(vertexes, indexes, 100, 100);
    break;
  case GeometryType::Plane:
    load_plane(vertexes, indexes);
    break;
  default:
    throw std::runtime_error("invalid GeometryType enum value");
  }

  _model_datas.emplace_back(vertexes, indexes);
  _model_datas.back().load_texture(ASSETS_DIRECTORY
                                   "/textures/image_2024-08-04_00-57-12.png");

  load_shader(shader_path);

  calculate_bound_box(vertexes);
}

void Model::scale(const glm::vec3 &scale) {
  _scale.x = abs(scale.x) < float_threshold ? 1 : scale.x;
  _scale.y = abs(scale.y) < float_threshold ? 1 : scale.y;
  _scale.z = abs(scale.z) < float_threshold ? 1 : scale.z;
}

void Model::rotate(const glm::vec3 &axis, float angle) {
  if (abs(angle) < float_threshold) {
    return;
  }

  _rotates.push_back({axis, angle});
}

void Model::translate(const glm::vec3 &translate) {
  _translate.x = translate.x;
  _translate.y = translate.y;
  _translate.z = translate.z;
}

void Model::default_position() {
  _scale = {1, 1, 1};
  _rotates.clear();
  // _rotate = {{0, 1, 0}, 0};
  _translate = {0, 0, 0};
}

void Model::calculate_bound_box(const std::vector<Vertex> &vertexes) {
  if (vertexes.empty()) {
    _bound_box = {{}, {}};
  }

  _bound_box.min = _bound_box.max = vertexes[0].position;
  for (const auto &v : vertexes) {
    const auto &p = v.position;

    _bound_box.min.x = std::min(_bound_box.min.x, p.x);
    _bound_box.min.y = std::min(_bound_box.min.y, p.y);
    _bound_box.min.z = std::min(_bound_box.min.z, p.z);

    _bound_box.max.x = std::max(_bound_box.max.x, p.x);
    _bound_box.max.y = std::max(_bound_box.max.y, p.y);
    _bound_box.max.z = std::max(_bound_box.max.z, p.z);
  }
}

const Model::BoundBox &Model::get_bound_box() { return _bound_box; }

Model::Model(Model &&other) {
  _bound_box = other._bound_box;

  _rotates = other._rotates;
  _translate = other._translate;
  _scale = other._scale;

  _type = other._type;
  _is_loaded = other._is_loaded;

  _model_datas = std::move(other._model_datas);
}

Model &Model::operator=(Model &&other) {
  if (this == &other) {
    return *this;
  }

  _bound_box = other._bound_box;

  _rotates = other._rotates;
  _translate = other._translate;
  _scale = other._scale;

  _type = other._type;
  _is_loaded = other._is_loaded;

  _model_datas = std::move(other._model_datas);

  return *this;
}

void Model::draw() {
  glUseProgram(_program_id);

  auto transform = Application::get_app().view_projection();
  transform = glm::translate(transform, _translate);
  for (auto &rot : _rotates) {
    transform = glm::rotate(transform, rot.angle, rot.axis);
  }
  transform = glm::scale(transform, _scale);

  uint32_t vp_id = glGetUniformLocation(_program_id, "MVP");
  glUniformMatrix4fv(vp_id, 1, false, &transform[0][0]);

  auto cam_pos = Application::get_app().camera_position();
  uint32_t cam_pos_id = glGetUniformLocation(_program_id, "CameraPos");
  glUniform3f(cam_pos_id, cam_pos[0], cam_pos[1], cam_pos[2]);

  float time = Application::get_app().timer();
  uint32_t time_id = glGetUniformLocation(_program_id, "Time");
  glUniform1f(time_id, time);

  for (auto &data_model : _model_datas) {
    data_model.draw();
  }
}

Model::~Model() {
  // delete shaders
  if (_program_id == 0 || not glIsProgram(_program_id)) {
    return;
  }

  const uint32_t shaders_size = 2;
  std::array<uint32_t, shaders_size> shaders{};
  int real_shader_number;

  glGetAttachedShaders(_program_id, shaders_size, &real_shader_number,
                       shaders.data());

  for (uint32_t shader : shaders) {
    if (shader != 0 && glIsShader(shader)) {
      glDetachShader(_program_id, shader);
      glDeleteShader(shader);
    }
  }
  glDeleteProgram(_program_id);
}
