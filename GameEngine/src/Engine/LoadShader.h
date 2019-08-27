#ifndef LOAD_SHADER
#define LOAD_SHADER
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
#endif
