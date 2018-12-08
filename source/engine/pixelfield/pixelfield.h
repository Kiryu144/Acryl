#ifndef ACRYL_PIXELFIELD_H
#define ACRYL_PIXELFIELD_H

#include <GLM/vec4.hpp>
#include <memory>

namespace Acryl{

class PixelField {
private:
    int mWidth, mHeight;
    glm::tvec4<unsigned char>* mData = nullptr;
public:
    PixelField(int width, int height);
    ~PixelField();

    PixelField(const PixelField& other);
    PixelField& operator=(const PixelField& other);

    void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    int getWidth() const;
    int getHeight() const;
    glm::tvec4<unsigned char>* getData();
};

}

#endif
