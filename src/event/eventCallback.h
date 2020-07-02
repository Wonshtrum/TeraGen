#ifndef __EVENTCALLBACK_H__
#define __EVENTCALLBACK_H__

#include "core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "event.h"
#include "graphics/view.h"

#define GET_HOOK GLFWHook& hook = *(GLFWHook*)glfwGetWindowUserPointer(window)

void setWindowEventsCallback(GLFWwindow* window);


#endif