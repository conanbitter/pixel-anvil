#pragma once
#include <fstream>

template <typename T>
struct ResourceLoader;

namespace pixanv {
    class ResHandle {
    public:
        ResHandle(const std::string& filename);

        int32_t readI32();
        uint32_t readU32();
        uint8_t readU8();

        void readBlock(void* target, size_t size);

        uint32_t getTypeId() const { return m_type_id; }
        uint32_t getSize() const { return m_data_size; }
    private:
        std::ifstream m_handle;
        uint32_t m_data_size;
        uint32_t m_type_id;
    };
}