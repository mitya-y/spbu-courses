#include <stdio.h>

#include <GL/gl.h>

#include "application.hpp"

void APIENTRY Application::glDebugOutput(GLenum Source, GLenum Type, GLuint Id, GLenum Severity,
                                         GLsizei Length, const GLchar *Message, const void *UserParam) {
  int len = 0;
  static char Buf[10000];

  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204) {
    return;
  }

  len += sprintf(Buf + len, "Debug message (%i) %s\n", Id, Message);
  switch (Source) {
  case GL_DEBUG_SOURCE_API:
    len += sprintf(Buf + len, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf(Buf + len, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf(Buf + len, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf(Buf + len, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf(Buf + len, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf(Buf + len, "Source: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Type) {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf(Buf + len, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf(Buf + len, "Type: Undefined Behaviour");
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf(Buf + len, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf(Buf + len, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf(Buf + len, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf(Buf + len, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf(Buf + len, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf(Buf + len, "Type: Other");
    break;
  }
  len += sprintf(Buf + len, "\n");

  switch (Severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf(Buf + len, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf(Buf + len, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf(Buf + len, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf(Buf + len, "Severity: notification");
    break;
  }
  len += sprintf(Buf + len, "\n\n");

  printf(Buf);
}

