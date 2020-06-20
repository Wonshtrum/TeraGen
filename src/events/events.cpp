#include "events.h"


EventType WindowCloseEvent::getType() { return WindowClose; }
EventType WindowCloseEvent::getStaticType() { return WindowClose; }

WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height): m_width(width), m_height(height) {}
EventType WindowResizeEvent::getType() { return WindowResize; }
EventType WindowResizeEvent::getStaticType() { return WindowResize; }
unsigned int WindowResizeEvent::getWidth() { return m_width; }
unsigned int WindowResizeEvent::getHeight() { return m_height; }

EventType WindowFocusEvent::getType() { return WindowFocus; }
EventType WindowFocusEvent::getStaticType() { return WindowFocus; }

EventType WindowLoseFocusEvent::getType() { return WindowLoseFocus; }
EventType WindowLoseFocusEvent::getStaticType() { return WindowLoseFocus; }

EventType WindowMoveEvent::getType() { return WindowMove; }
EventType WindowMoveEvent::getStaticType() { return WindowMove; }

KeyEvent::KeyEvent(int keyCode): m_keyCode(keyCode) {}
int KeyEvent::getKeyCode() { return m_keyCode; }

KeyPressEvent::KeyPressEvent(int keyCode, unsigned int repeatCount): KeyEvent(keyCode), m_repeatCount(repeatCount) {}
EventType KeyPressEvent::getType() { return KeyPress; }
EventType KeyPressEvent::getStaticType() { return KeyPress; }
unsigned int KeyPressEvent::getRepeatCount() { return m_repeatCount; }

KeyReleaseEvent::KeyReleaseEvent(int keyCode): KeyEvent(keyCode) {}
EventType KeyReleaseEvent::getType() { return KeyRelease; }
EventType KeyReleaseEvent::getStaticType() { return KeyRelease; }

MouseButtonEvent::MouseButtonEvent(int button): m_button(button) {}
int MouseButtonEvent::getButton() { return m_button; }

MouseButtonPressEvent::MouseButtonPressEvent(int button): MouseButtonEvent(button) {}
EventType MouseButtonPressEvent::getType() { return MouseButtonPress; }
EventType MouseButtonPressEvent::getStaticType() { return MouseButtonPress; }

MouseButtonReleaseEvent::MouseButtonReleaseEvent(int button): MouseButtonEvent(button) {}
EventType MouseButtonReleaseEvent::getType() { return MouseButtonRelease; }
EventType MouseButtonReleaseEvent::getStaticType() { return MouseButtonRelease; }

MouseMoveEvent::MouseMoveEvent(int x, int y): m_x(x), m_y(y) {}
EventType MouseMoveEvent::getType() { return MouseMove; }
EventType MouseMoveEvent::getStaticType() { return MouseMove; }
int MouseMoveEvent::getX() { return m_x; }
int MouseMoveEvent::getY() { return m_y; }

MouseScrollEvent::MouseScrollEvent(float dx, float dy): m_dx(dy), m_dy(dy) {}
EventType MouseScrollEvent::getType() { return MouseScroll; }
EventType MouseScrollEvent::getStaticType() { return MouseScroll; }
float MouseScrollEvent::getDx() { return m_dx; }
float MouseScrollEvent::getDy() { return m_dy; }

