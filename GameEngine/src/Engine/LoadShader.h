#ifndef LOAD_SHADER_H
#define LOAD_SHADER_H
#ifndef __glew_h__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif // !__glew_h__
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
#endif