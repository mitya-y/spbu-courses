#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "model.h"

Model::ModelData::ModelData(std::vector<Vertex> &vertexes,
                            std::vector<uint32_t> &indexes) {
  // // create and bind vertex array
  glGenVertexArrays(1, &_vertex_array);
  glBindVertexArray(_vertex_array);

  // generate vertex buffer and bind it to vertex
  glGenBuffers(1, &_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);

  // fill buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexes.size(),
               vertexes.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer); // hz nado li

  // set vertex attributes
  char *offset = 0;
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), offset);
  offset += sizeof(Vec3);
  glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), offset);
  offset += sizeof(Vec3);
  glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), offset);
  offset += sizeof(Vec2);
  glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), offset);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindVertexArray(0);

  if (indexes.empty()) {
    return;
  }

  // generate index buffer and activate it
  glGenBuffers(1, &_index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);

  // fill data
  uint32_t index_buffer_size = sizeof(uint32_t) * indexes.size();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, indexes.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer); // hz nado li

  _indexes_number = indexes.size();
}

Model::ModelData::~ModelData() {
  if (_vertex_array != 0) {
    // enable vertex array for deleting vertex buffer
    glBindVertexArray(_vertex_array);
    // delete vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (_vertex_buffer != 0) {
      glDeleteBuffers(1, &_vertex_buffer);
    }
    // disable vertex array and delete it
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &_vertex_array);
  }

  if (_index_buffer != 0) {
    glDeleteBuffers(1, &_index_buffer);
  }
}

Model::ModelData & Model::ModelData::operator=(ModelData &&other) {
  if (this == &other) {
    return *this;
  }

  std::swap(_vertex_array, other._vertex_array);
  std::swap(_vertex_buffer, other._vertex_buffer);
  std::swap(_index_buffer, other._index_buffer);

  std::swap(_indexes_number, other._indexes_number);

  std::swap(_texture, other._texture);
  std::swap(_texture_height, other._texture_height);
  std::swap(_texture_widht, other._texture_widht);

  return *this;
}

Model::ModelData::ModelData(Model::ModelData &&other) {
  std::swap(_vertex_array, other._vertex_array);
  std::swap(_vertex_buffer, other._vertex_buffer);
  std::swap(_index_buffer, other._index_buffer);

  std::swap(_indexes_number, other._indexes_number);

  std::swap(_texture, other._texture);
  std::swap(_texture_height, other._texture_height);
  std::swap(_texture_widht, other._texture_widht);
}

void Model::ModelData::load_texture(std::string_view filename) {
  //  load and generate the texture
  int channels;
  unsigned char *data = stbi_load(filename.data(), &_texture_widht,
                                  &_texture_height, &channels, 0);
  if (data) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, _texture_widht, _texture_height, 0,
                 format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

void Model::ModelData::draw() {
  glBindVertexArray(_vertex_array);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
  glBindTexture(GL_TEXTURE_2D, _texture);
  glDrawElements(GL_TRIANGLE_STRIP, _indexes_number, GL_UNSIGNED_INT, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}