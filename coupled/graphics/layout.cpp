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

	static unsigned int s_sizes[LayoutDataType::nbTypes] = {4, 2*4, 3*4, 4*4, 3*3*4, 4*4*4, 2*4, 3*4, 4*4, 1};
	static unsigned int s_counts[LayoutDataType::nbTypes] = {1, 2, 3, 4, 3*3, 4*4, 1, 2, 3, 4, 1};
	static GLenum s_GLTypes[LayoutDataType::nbTypes] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_INT, GL_INT, GL_INT, GL_INT, GL_BOOL};

	LayoutElement(LayoutDataType type, bool normalized = false): m_normalized(normalized), m_offset(0) {
		m_type = s_GLTypes[type];
		m_count = s_counts[type];
		m_size = s_sizes[type];
	}

	LayoutElement() {}
};

class Layout {
	private:
		LayoutElement* m_elements;
		unsigned int m_count;
		unsigned int m_stride;

	public:
		Layout(): m_elements(NULL), m_count(0), m_stride(0) {}

		Layout(std::initializer_list<LayoutElement> elements): m_count(elements.size()), m_stride(0) {
			m_elements = new LayoutElement[m_count];
			for (unsigned int i = 0 ; i < m_count ; i++) {
				m_elements[i] = elements.begin()[i];
				m_elements[i].m_offset = m_stride;
				m_stride += m_elements[i].m_size;
			}
		}

		Layout(LayoutElement* elements, unsigned int count): m_elements(elements), m_count(count), m_stride(0) {
			for (unsigned int i = 0 ; i < m_count ; i++) {
				m_elements[i].m_offset = m_stride;
				m_stride += m_elements[i].m_size;
			}
		}

		Layout(const Layout& other): m_count(other.m_count), m_stride(other.m_stride) {
			m_elements = new LayoutElement[m_count];
			for (unsigned int i = 0 ; i < m_count ; i++) {
				m_elements[i] = other.m_elements[i];
			}
		}

		~Layout() { delete[] m_elements; }
		
		unsigned int getStride() { return m_stride; }
		
		void bind() {
			for (unsigned int i = 0 ; i < m_count ; i++) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i,
						m_elements[i].m_count,
						m_elements[i].m_type,
						m_elements[i].m_normalized,
						m_stride,
						(const void*)(uintptr_t)(m_elements[i].m_offset));
			}
		}
};
