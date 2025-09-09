#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vec3 {
  float x, y, z;
};
struct Vec2 {
  float x, y;
};

class Model {
public:
  enum struct GeometryType { Cube, Sphere, Plane };

  struct BoundBox {
    Vec3 min, max;
  };

private:
public:
  struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec2 texture_coords;
    Vec3 color;
  };
  struct Rotation {
    glm::vec3 axis;
    float angle;
  };

  class ModelData {
    // opengl stuff
    uint32_t _vertex_array{};
    uint32_t _vertex_buffer{};
    uint32_t _index_buffer{};
    uint32_t _indexes_number = 0;

    uint32_t _texture{};
    int _texture_height{};
    int _texture_widht{};

  public:
    void load_texture(std::string_view filename);

    void draw();

    ModelData(std::vector<Vertex> &vertexes, std::vector<uint32_t> &indexes);
    ~ModelData();

    ModelData(const ModelData &other) = delete;
    ModelData &operator=(const ModelData &other) = delete;

    ModelData(ModelData &&other);
    ModelData &operator=(ModelData &&other);
  };

private:
  std::vector<ModelData> _model_datas;

  BoundBox _bound_box{};

  std::vector<Rotation> _rotates{};
  glm::vec3 _translate{};
  glm::vec3 _scale{};

  GeometryType _type{};
  bool _is_loaded = false;

  uint32_t _program_id{};

public:
  Model(std::string_view path, std::string_view filename);
  Model(GeometryType geom_type, const std::string &shader_path = "default");

  Model(const Model &other) = delete;
  Model &operator=(const Model &other) = delete;

  Model(Model &&other);
  Model &operator=(Model &&other);

  void load_texture(std::string_view path) {
    for (auto &data : _model_datas) {
      data.load_texture(path);
    }
  }
  ~Model();

private:
  void calculate_bound_box(const std::vector<Vertex> &vertexes);

  void load_sphere(std::vector<Vertex> &vertexes,
                   std::vector<uint32_t> &indexes, int W, int H);
  void load_cube(std::vector<Vertex> &vertexes, std::vector<uint32_t> &indexes,
                 const Vec3 &point0, const Vec3 &point1);
  void load_plane(std::vector<Vertex> &vertexes,
                  std::vector<uint32_t> &indexes);

  void load_shader(const std::string &shader_name);

public:
  void scale(const glm::vec3 &scale = {1, 1, 1});
  void rotate(const glm::vec3 &axis = {}, float angle = 0);
  void translate(const glm::vec3 &translate = {});
  void default_position();

  const BoundBox &get_bound_box();

  void draw();
};
