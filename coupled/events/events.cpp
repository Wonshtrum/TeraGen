#include <functional>

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
		virtual EventType getType() override { return WindowClose; }
		static EventType getStaticType() { return WindowClose; }
};

class WindowResizeEvent: public Event {
	private:
		unsigned int m_width;
		unsigned int m_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height): m_width(width), m_height(height) {}
		virtual EventType getType() override { return WindowResize; }
		static EventType getStaticType() { return WindowResize; }
		unsigned int getWidth() { return m_width; }
		unsigned int getHeight() { return m_height; }
};

class WindowFocusEvent: public Event {
	public:
		virtual EventType getType() override { return WindowFocus; }
		static EventType getStaticType() { return WindowFocus; }
};

class WindowLoseFocusEvent: public Event {
	public:
		virtual EventType getType() override { return WindowLoseFocus; }
		static EventType getStaticType() { return WindowLoseFocus; }
};

class WindowMoveEvent: public Event {
	public:
		virtual EventType getType() override { return WindowMove; }
		static EventType getStaticType() { return WindowMove; }
};

class KeyEvent: public Event {
	protected:
		int m_keyCode;
		KeyEvent(int keyCode): m_keyCode(keyCode) {}
	public:
		int getKeyCode() { return m_keyCode; }
};

class KeyPressEvent: public KeyEvent {
	private:
		unsigned int m_repeatCount;
	public:
		KeyPressEvent(int keyCode, unsigned int repeatCount): KeyEvent(keyCode), m_repeatCount(repeatCount) {}
		virtual EventType getType() override { return KeyPress; }
		static EventType getStaticType() { return KeyPress; }
		unsigned int getRepeatCount() { return m_repeatCount; }
};

class KeyReleaseEvent: public KeyEvent {
	public:
		KeyReleaseEvent(int keyCode): KeyEvent(keyCode) {}
		virtual EventType getType() override { return KeyRelease; }
		static EventType getStaticType() { return KeyRelease; }
};

class MouseButtonEvent: public Event {
	protected:
		int m_button;
		MouseButtonEvent(int button): m_button(button) {}
	public:
		int getButton() { return m_button; }
};

class MouseButtonPressEvent: public MouseButtonEvent {
	public:
		MouseButtonPressEvent(int button): MouseButtonEvent(button) {}
		virtual EventType getType() override { return MouseButtonPress; }
		static EventType getStaticType() { return MouseButtonPress; }
};

class MouseButtonReleaseEvent: public MouseButtonEvent {
	public:
		MouseButtonReleaseEvent(int button): MouseButtonEvent(button) {}
		virtual EventType getType() override { return MouseButtonRelease; }
		static EventType getStaticType() { return MouseButtonRelease; }
};

class MouseMoveEvent: public Event {
	private:
		int m_x;
		int m_y;
	public:
		MouseMoveEvent(int x, int y): m_x(x), m_y(y) {}
		virtual EventType getType() override { return MouseMove; }
		static EventType getStaticType() { return MouseMove; }
		int getX() { return m_x; }
		int getY() { return m_y; }
};

class MouseScrollEvent: public Event {
	private:
		float m_dx;
		float m_dy;
	public:
		MouseScrollEvent(float dx, float dy): m_dx(dy), m_dy(dy) {}
		virtual EventType getType() override { return MouseScroll; }
		static EventType getStaticType() { return MouseScroll; }
		float getDx() { return m_dx; }
		float getDy() { return m_dy; }
};

template<typename T>
bool dispatch(Event& event, std::function<bool(T&)> func) {
	if (event.getType() == T::getStaticType()) {
		return true;
	}
	return false;
}
