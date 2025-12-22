#include "image.hpp"
#include "resources.hpp"

using namespace pixanv;

Image Image::load(const std::string& filename) {
    const uint16_t MAX_TRANSP_COUNT = 1 << 15;

    ResHandle handle(filename);
    int width = handle.readU32();
    int height = handle.readU32();

    Image image(width, height);

    if (handle.getSize() == (width * height * 2 + 4 * 2)) {
        // The image has no transparent pixels and is therefore not compressed
        handle.readBlock(image.m_data.data(), sizeof(Color) * width * height);
        image.m_has_transparency = false;
    } else {
        int length = width * height;
        int index = 0;

        while (index < length) {
            uint16_t pixel = handle.readU16();
            if (pixel < MAX_TRANSP_COUNT) {
                for (int i = 0;i <= pixel;i++) {
                    image.m_data[index] = Color::TRANSPARENT;
                    index++;
                    if (index > length) {
                        throw std::runtime_error("The image file is corrupted or have wrong format");
                    }
                }
            } else {
                image.m_data[index] = Color(pixel);
                index++;
            }
        }
        image.m_has_transparency = true;
    }

    return image;
}
