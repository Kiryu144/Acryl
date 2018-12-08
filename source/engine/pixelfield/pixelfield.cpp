#include "pixelfield.h"

namespace Acryl {

PixelField::PixelField(int width, int height)
    : mWidth(width), mHeight(height) {
    mData = new glm::tvec4<unsigned char>[width*height];
}

PixelField::~PixelField() {
    delete[] mData;
}

PixelField::PixelField(const PixelField& other) {
    *this = other;
}

PixelField& PixelField::operator=(const PixelField& other) {
    delete[] mData;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mData = new glm::tvec4<unsigned char>[mWidth*mHeight];
    memcpy(mData, other.mData, mWidth*mHeight);
    return *this;
}

int PixelField::getWidth() const {
    return mWidth;
}

int PixelField::getHeight() const {
    return mHeight;
}

void PixelField::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    mData[(y * mWidth) + x] = glm::tvec4<unsigned char>(r, g, b, a);
}

glm::tvec4<unsigned char>* PixelField::getData() {
    return mData;
}

}