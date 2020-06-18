#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include <GL/glew.h>
#include <initializer_list>

enum LayoutDataType {
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool,
	nbTypes	
};

struct LayoutElement {
	GLenum m_type;
	bool m_normalized;
	unsigned int m_count;
	unsigned int m_size;
	unsigned int m_offset;

	static unsigned int s_sizes[LayoutDataType::nbTypes];
	static unsigned int s_counts[LayoutDataType::nbTypes];
	static GLenum s_GLTypes[LayoutDataType::nbTypes];

	LayoutElement(LayoutDataType type, bool normalized = false);

	LayoutElement();
};

class Layout {
	private:
		LayoutElement* m_elements;
		unsigned int m_count;
		unsigned int m_stride;

	public:
		Layout();

		Layout(std::initializer_list<LayoutElement> elements);

		Layout(LayoutElement* elements, unsigned int count);

		Layout(const Layout& other);

		~Layout();

		unsigned int getStride();

		void bind();
};


#endif