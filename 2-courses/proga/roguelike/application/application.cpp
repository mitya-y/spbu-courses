#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "application.hpp"
#include "scene.h"

Application::Application() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // set scene
  _window = glfwCreateWindow(800, 600, "roguelike", nullptr, nullptr);
  if (_window == nullptr) {
    throw std::runtime_error("Failed to create GLFW window");
    glfwTerminate();
  }
  glfwSetWindowSizeCallback(_window, window_size_callback);
  glfwMakeContextCurrent(_window);

  // init OpenGL
  GLenum glewStatus = glewInit();

  if (glewStatus != GLEW_OK) {
    std::cerr << "Error initializing GLEW: " << glewGetErrorString(glewStatus)
              << std::endl;
    exit(0);
  }

  glClearColor(0.30, 0.47, 0.8, 1);
  // glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // wglSwapIntervalEXT - vertical sync
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  /*glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
  GL_TRUE);*/
}

Application::~Application() {}

void Application::window_size_callback(GLFWwindow *window, int width,
                                       int height) {
  glViewport(0, 0, width, height);
}

void Application::start(std::unique_ptr<Scene> scene) {

  int width, height;
  glfwGetWindowSize(_window, &width, &height);
  glViewport(0, 0, width, height);

  float rx, ry;
  rx = ry = 0.1;
  if (width > height) {
    rx *= float(width) / float(height);
  } else {
    ry *= float(height) / float(width);
  }

  _projection = glm::frustum(-rx / 2, rx / 2, -ry / 2, ry / 2, 0.1f, 1500.0f);
  _camera_position = glm::vec3(2.3, 1.5, 0);
  _view =
      glm::lookAt(_camera_position, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
  _view_projection = _projection * _view;

  // set Camera
  //  wglSwapIntervalEXT - enable vertical sync

  _scene = std::move(scene);
  //scene->create_unit<field>("field");

  while (not glfwWindowShouldClose(_window)) {
    // render scene
    render();
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }

  glfwTerminate();
}

bool Application::key_pressed(int key) {
  if (_window == nullptr) {
    return false;
  }
  return glfwGetKey(_window, key) == GLFW_PRESS;
}

void Application::render() {
  // clear frame
  int modes[2];
  glGetIntegerv(GL_POLYGON_MODE, modes);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float time = timer();

  /*
  static int posx = 0, posy = 0;

  if (key_pressed(GLFW_KEY_W)) {
    posy++;
  }
  if (key_pressed(GLFW_KEY_S)) {
    posy--;
  }
  if (key_pressed(GLFW_KEY_A)) {
    posx--;
  }
  if (key_pressed(GLFW_KEY_D)) {
    posx++;
  }

  */
 /* _camera_position = glm::vec3(100);
  _camera_position = glm::vec3(0 + posx, 150, 200 - posy);
  auto at = glm::vec3(posx, 0, posy);*/

  auto at = glm::vec3(0, 0, 0);
  _camera_position = glm::vec3(0, 50, 40);
  at = glm::vec3(0, 0, 0);

  _view =
    glm::lookAt(_camera_position, at, glm::vec3(0.0, 1.0, 0.0));
  _view_projection = _projection * _view;

  // Render all units
  /*
  static Model box("models/box", "box.obj");
  for (int x = -5; x <= 5; x++) {
    for (int y = -5; y <= 5; y++) {
      box.default_position();
      box.scale({10, 10, 10});
      box.translate({x * 15, 0, y * 15});
      box.draw();
    }
  }
  */
  //static Model boxes("models/box", "box.obj");
  //boxes.default_position();
  //boxes.scale({10, 10, 10});
  //boxes.draw();
/*
  static Model model("models/monach", "Man.obj");

  float scale = 0.035;
  model.default_position();
  model.scale({scale, scale, scale});
  model.rotate({0, 1, 0}, M_PI);
  model.translate({0, 10, 0});
  model.translate({posx, 0, posy});
  model.draw();

  static Model chair("models/chair", "chair.obj");
  chair.default_position();
  chair.scale({0.3, 0.3, 0.3});
  chair.rotate({0, 1, 1}, M_PI);
  chair.rotate({0, 0, 1}, M_PI);
  chair.rotate({0, 0, 1}, sin(time) * 10);
  chair.translate({50, 10, 50});
  chair.draw();

  static Model table("models/table", "table.obj");
  table.default_position();
  table.scale({0.2, 0.2, 0.12});
  table.rotate({0, 1, 0}, M_PI / 2);
  table.translate({-16, 15, -3});
  table.draw();

  static Model book("models/book", "book.obj");
  book.default_position();
  book.scale({2, 2, 2});
  book.translate({-15, 30, 0});
  book.draw();
  */

  //static Model model("models/chair", "chair.obj");
  //static Model model(Model::GeometryType::Cube);
  //model.scale({2, 2, 2});
  //model.draw();

  _scene->update();
  _scene->draw();

  //model.default_position();
  //model.scale({0.9999, 0.99999, 0.9999});
  //model.rotate({0, 1, 1}, M_PI);
  //model.rotate({0, 0, 1}, M_PI);
  //model.rotate({0, 0, 1}, sin(time) * 10);
  //model.draw();

  // static Model model("models/table", "table.obj");

  glFinish();
}

Scene &Application::get_scene() { return *_scene; }

const glm::highp_mat4 &Application::view_projection() {
  return _view_projection;
}

const glm::vec3 &Application::camera_position() { return _camera_position; }

void Application::set_scene(std::unique_ptr<Scene> scene) {}

double Application::timer() { return clock() / 100000.0; }

std::shared_ptr<Model> Application::create_model() { return {}; }

void Application::delete_model(std::shared_ptr<Model> model) {}
