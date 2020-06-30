#ifndef __EVENTSCALLBACK_H__
#define __EVENTSCALLBACK_H__

#include "core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "events.h"
#include "graphics/view.h"

#define GET_HOOK GLFWHook& hook = *(GLFWHook*)glfwGetWindowUserPointer(window)

struct GLFWHook;

void setWindowEventsCallback(GLFWwindow* window);


#endif