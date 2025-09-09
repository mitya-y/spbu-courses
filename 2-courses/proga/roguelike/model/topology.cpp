#include "application.hpp"
#include "model.h"

void Model::load_sphere(std::vector<Vertex> &vertexes,
                        std::vector<uint32_t> &index, int W, int H) {
  vertexes.resize(W * H);
  index.resize((H - 1) * (W * 2 + 1) - 1);

  float pi = 3.14159265359;
  int i, j, k;
  float theta = 0, phi;
  for (i = 0; i < H; i++, theta += pi / (H - 1))
    for (j = 0, phi = 0; j < W; j++, phi += 2 * pi / (W - 1)) {
      vertexes[i * W + j].normal = {
        std::sin(theta) * std::sin(phi),
        std::cos(theta),
        std::sin(theta) * std::cos(phi)
      };
      vertexes[i * W + j].position = {
        vertexes[i * W + j].normal.x,
        vertexes[i * W + j].normal.y,
        vertexes[i * W + j].normal.z
      };
      vertexes[i * W + j].texture_coords = {j / (W - 1.0f), i / (H - 1.0f)};
      vertexes[i * W + j].color = {1, 1, 1};
    }

  for (i = 0, k = 0; i < H - 1; i++) {
    for (j = 0; j < W; j++) {
      index[k++] = i * W + j;
      index[k++] = (i + 1) * W + j;
    }
    if (i != H - 2)
      index[k++] = -1;
  }
}

void Model::load_cube(std::vector<Vertex> &vertexes,
                      std::vector<uint32_t> &index, const Vec3 &point0,
                      const Vec3 &point1) {
  vertexes.resize(24);
  index.resize(29);

  Vec3 normals[6] = {{0, -1, 0}, {0, 1, 0},  {-1, 0, 0},
                     {1, 0, 0},  {0, 0, -1}, {0, 0, 1}};

  vertexes[0].position = point0;
  vertexes[0].normal = normals[0];
  vertexes[0].texture_coords = {0, 2};
  vertexes[0].color = {1, 1, 1};

  vertexes[1].position = {point0.x, point0.y, point1.z};
  vertexes[1].normal = normals[0];
  vertexes[1].texture_coords = {0, 3};
  vertexes[1].color = {1, 1, 1};

  vertexes[2].position = {point1.x, point0.y, point1.z};
  vertexes[2].normal = normals[0];
  vertexes[2].texture_coords = {1, 3};
  vertexes[2].color = {1, 1, 1};

  vertexes[3].position = {point1.x, point0.y, point0.z};
  vertexes[3].normal = normals[0];
  vertexes[3].texture_coords = {1, 2};
  vertexes[3].color = {1, 1, 1};

  vertexes[4].position = point1;
  vertexes[4].normal = normals[1];
  vertexes[4].texture_coords = {1, 0};
  vertexes[4].color = {1, 1, 1};

  vertexes[5].position = {point1.x, point1.y, point0.z};
  vertexes[5].normal = normals[1];
  vertexes[5].texture_coords = {1, 1};
  vertexes[5].color = {1, 1, 1};

  vertexes[6].position = {point0.x, point1.y, point1.z};
  vertexes[6].normal = normals[1];
  vertexes[6].texture_coords = {0, 0};
  vertexes[6].color = {1, 1, 1};

  vertexes[7].position = {point0.x, point1.y, point0.z};
  vertexes[7].normal = normals[1];
  vertexes[7].texture_coords = {0, 1};
  vertexes[7].color = {1, 1, 1};

  vertexes[8].position = point0;
  vertexes[8].normal = normals[2];
  vertexes[8].texture_coords = {0, 3};
  vertexes[8].color = {1, 1, 1};

  vertexes[9].position = {point0.x, point0.y, point1.z};
  vertexes[9].normal = normals[2];
  vertexes[9].texture_coords = {0, 2};
  vertexes[9].color = {1, 1, 1};

  vertexes[10].position = {point0.x, point1.y, point1.z};
  vertexes[10].normal = normals[2];
  vertexes[10].texture_coords = {-1, 2};
  vertexes[10].color = {1, 1, 1};

  vertexes[11].position = {point0.x, point1.y, point0.z};
  vertexes[11].normal = normals[2];
  vertexes[11].texture_coords = {-1, 3};
  vertexes[11].color = {1, 1, 1};

  vertexes[12].position = {point1.x, point0.y, point1.z};
  vertexes[12].normal = normals[3];
  vertexes[12].texture_coords = {2, 3};
  vertexes[12].color = {1, 1, 1};

  vertexes[13].position = {point1.x, point0.y, point0.z};
  vertexes[13].normal = normals[3];
  vertexes[13].texture_coords = {2, 2};
  vertexes[13].color = {1, 1, 1};

  vertexes[14].position = point1;
  vertexes[14].normal = normals[3];
  vertexes[14].texture_coords = {1, 3};
  vertexes[14].color = {1, 1, 1};

  vertexes[15].position = {point1.x, point1.y, point0.z};
  vertexes[15].normal = normals[3];
  vertexes[15].texture_coords = {1, 2};
  vertexes[15].color = {1, 1, 1};

  vertexes[16].position = point0;
  vertexes[16].normal = normals[4];
  vertexes[16].texture_coords = {0, 2};
  vertexes[16].color = {1, 1, 1};

  vertexes[17].position = {point1.z, point0.y, point0.z};
  vertexes[17].normal = normals[4];
  vertexes[17].texture_coords = {1, 2};
  vertexes[17].color = {1, 1, 1};

  vertexes[18].position = {point1.z, point1.y, point0.z};
  vertexes[18].normal = normals[4];
  vertexes[18].texture_coords = {1, 1};
  vertexes[18].color = {1, 1, 1};

  vertexes[19].position = {point0.z, point1.y, point0.z};
  vertexes[19].normal = normals[4];
  vertexes[19].texture_coords = {0, 1};
  vertexes[19].color = {1, 1, 1};

  vertexes[20].position = {point0.z, point0.y, point1.z};
  vertexes[20].normal = normals[5];
  vertexes[20].texture_coords = {0, 3};
  vertexes[20].color = {1, 1, 1};

  vertexes[21].position = {point1.z, point0.y, point1.z};
  vertexes[21].normal = normals[5];
  vertexes[21].texture_coords = {1, 3};
  vertexes[21].color = {1, 1, 1};

  vertexes[22].position = point1;
  vertexes[22].normal = normals[5];
  vertexes[22].texture_coords = {1, 4};
  vertexes[22].color = {1, 1, 1};

  vertexes[23].position = {point0.z, point1.y, point1.z};
  vertexes[23].normal = normals[5];
  vertexes[23].texture_coords = {0, 4};
  vertexes[23].color = {1, 1, 1};

  index[0] = 0;
  index[1] = 1;
  index[2] = 3;
  index[3] = 2;
  index[4] = -1;

  index[5] = 7;
  index[6] = 6;
  index[7] = 5;
  index[8] = 4;
  index[9] = -1;

  index[10] = 8;
  index[11] = 9;
  index[12] = 11;
  index[13] = 10;
  index[14] = -1;

  index[15] = 15;
  index[16] = 14;
  index[17] = 13;
  index[18] = 12;
  index[19] = -1;

  index[20] = 16;
  index[21] = 17;
  index[22] = 19;
  index[23] = 18;
  index[24] = -1;

  index[25] = 20;
  index[26] = 21;
  index[27] = 23;
  index[28] = 22;
}

void Model::load_plane(std::vector<Vertex> &vertexes,
                       std::vector<uint32_t> &indexes) {
  vertexes.resize(4);

  for (auto &vert : vertexes) {
    vert.normal = {0, 1, 0};
    vert.color = {1, 1, 0};
  }

  float scale = 0.5;

  vertexes[0].position = {scale, 0, scale};
  vertexes[1].position = {scale, 0, -scale};
  vertexes[2].position = {-scale, 0, -scale};
  vertexes[3].position = {-scale, 0, scale};

  vertexes[0].texture_coords = {1, 1};
  vertexes[1].texture_coords = {1, 0};
  vertexes[2].texture_coords = {0, 0};
  vertexes[3].texture_coords = {0, 1};

  indexes = {0, 1, 2, 2, 3, 0};
}
