#ifndef GEMA_H
# define GEMA_H

# include <GL/glew.h>
# define GL3_PROTOTYPES 1
# ifdef __APPLE__
#  include <OpenGL/gl.h>
# else
#  include <GL/gl.h>
# endif
# include <GLFW/glfw3.h>
# include "engine.h"
# include "window.h"
# include "renderer.h"
# include "input.h"
# include "resourcesmanager.h"

#endif
