#include "pixelfield.h"

namespace Acryl {

PixelField::PixelField(int width, int height)
    : m_width(width), m_height(height) {
    m_data = new glm::tvec4<unsigned char>[width*height];
}

PixelField::~PixelField() {
    delete[] m_data;
}

PixelField::PixelField(const PixelField& other) {
    *this = other;
}

PixelField& PixelField::operator=(const PixelField& other) {
    delete[] m_data;
    m_width = other.m_width;
    m_height = other.m_height;
    m_data = new glm::tvec4<unsigned char>[m_width*m_height];
    memcpy(m_data, other.m_data, m_width*m_height);
    return *this;
}

int PixelField::getWidth() const {
    return m_width;
}

int PixelField::getHeight() const {
    return m_height;
}

void PixelField::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    m_data[(y * m_width) + x] = glm::tvec4<unsigned char>(r, g, b, a);
}

glm::tvec4<unsigned char>* PixelField::getData() {
    return m_data;
}

}