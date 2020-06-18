#include "layout.h"


unsigned int LayoutElement::s_sizes[LayoutDataType::nbTypes] = {4, 2*4, 3*4, 4*4, 3*3*4, 4*4*4, 2*4, 3*4, 4*4, 1};
unsigned int LayoutElement::s_counts[LayoutDataType::nbTypes] = {1, 2, 3, 4, 3*3, 4*4, 1, 2, 3, 4, 1};
GLenum LayoutElement::s_GLTypes[LayoutDataType::nbTypes] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_INT, GL_INT, GL_INT, GL_INT, GL_BOOL};

LayoutElement::LayoutElement(LayoutDataType type, bool normalized): m_normalized(normalized), m_offset(0) {
	m_type = s_GLTypes[type];
	m_count = s_counts[type];
	m_size = s_sizes[type];
}

LayoutElement::LayoutElement() {}

Layout::Layout() {}

Layout::Layout(std::initializer_list<LayoutElement> elements): m_count(elements.size()), m_stride(0) {
	m_elements = new LayoutElement[m_count];
	for (unsigned int i = 0 ; i < m_count ; i++) {
		m_elements[i] = elements.begin()[i];
		m_elements[i].m_offset = m_stride;
		m_stride += m_elements[i].m_size;
	}
}

Layout::Layout(LayoutElement* elements, unsigned int count): m_elements(elements), m_count(count), m_stride(0) {
	for (unsigned int i = 0 ; i < m_count ; i++) {
		m_elements[i].m_offset = m_stride;
		m_stride += m_elements[i].m_size;
	}
}

Layout::Layout(const Layout& other): m_count(other.m_count), m_stride(other.m_stride) {
	m_elements = new LayoutElement[m_count];
	for (unsigned int i = 0 ; i < m_count ; i++) {
		m_elements[i] = other.m_elements[i];
	}
}

Layout::~Layout() { delete[] m_elements; }

unsigned int Layout::getStride() { return m_stride; }

void Layout::bind() {
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
