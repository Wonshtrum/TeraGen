#ifndef __EVENT_H__
#define __EVENT_H__

#include "core.h"
enum EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
	KeyPress, KeyRelease,
	MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
};

class Event {
	public:
		virtual EventType getType() = 0;
		bool m_handled = false;
};

class WindowCloseEvent: public Event {
	public:
		virtual EventType getType();
		static EventType getStaticType();
};

class WindowResizeEvent: public Event {
	private:
		unsigned int m_width;
		unsigned int m_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);
		virtual EventType getType();
		static EventType getStaticType();
		unsigned int getWidth();
		unsigned int getHeight();
};

class WindowFocusEvent: public Event {
	public:
		virtual EventType getType();
		static EventType getStaticType();
};

class WindowLoseFocusEvent: public Event {
	public:
		virtual EventType getType();
		static EventType getStaticType();
};

class WindowMoveEvent: public Event {
	private:
		int m_x;
		int m_y;
	public:
		WindowMoveEvent(int x, int y);
		virtual EventType getType();
		static EventType getStaticType();
		int getX();
		int getY();
};

class KeyEvent: public Event {
	protected:
		int m_keyCode;
		KeyEvent(int keyCode);
	public:
		int getKeyCode();
};

class KeyPressEvent: public KeyEvent {
	private:
		unsigned int m_repeatCount;
	public:
		KeyPressEvent(int keyCode, unsigned int repeatCount);
		virtual EventType getType();
		static EventType getStaticType();
		unsigned int getRepeatCount();
};

class KeyReleaseEvent: public KeyEvent {
	public:
		KeyReleaseEvent(int keyCode);
		virtual EventType getType();
		static EventType getStaticType();
};

class MouseButtonEvent: public Event {
	protected:
		int m_button;
		MouseButtonEvent(int button);
	public:
		int getButton();
};

class MouseButtonPressEvent: public MouseButtonEvent {
	public:
		MouseButtonPressEvent(int button);
		virtual EventType getType();
		static EventType getStaticType();
};

class MouseButtonReleaseEvent: public MouseButtonEvent {
	public:
		MouseButtonReleaseEvent(int button);
		virtual EventType getType();
		static EventType getStaticType();
};

class MouseMoveEvent: public Event {
	private:
		int m_x;
		int m_y;
	public:
		MouseMoveEvent(int x, int y);
		virtual EventType getType();
		static EventType getStaticType();
		int getX();
		int getY();
};

class MouseScrollEvent: public Event {
	private:
		float m_dx;
		float m_dy;
	public:
		MouseScrollEvent(float dx, float dy);
		virtual EventType getType();
		static EventType getStaticType();
		float getDx();
		float getDy();
};

template<typename T>
bool dispatch(Event& event, std::function<bool(T&)> func) {
	if (event.getType() == T::getStaticType()) {
		event.m_handled = func(*(T*)&event);
		return true;
	}
	return false;
}


#endif