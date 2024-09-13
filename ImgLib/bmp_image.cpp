#include "bmp_image.h"
#include "pack_defines.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

PACKED_STRUCT_BEGIN BitmapFileHeader {
    unsigned char sign[2];
    unsigned int sum_size;
    int reserve;
    unsigned int padding;
}
PACKED_STRUCT_END

PACKED_STRUCT_BEGIN BitmapInfoHeader {
    unsigned int head_size;
    int width;
    int height;
    unsigned short planes_count;
    unsigned short bit_per_pixel;
    unsigned int type;
    unsigned int byte_count;
    int horizontal_resolution;
    int vertical_resolution;
    int colors_used;
    int major_colors;
}
PACKED_STRUCT_END

// функция вычисления отступа по ширине
static int GetBMPStride(int w) {
    return 4 * ((w * 3 + 3) / 4);
}

std::pair<BitmapFileHeader, BitmapInfoHeader> ConstructHeaders(const Image& image){
    BitmapInfoHeader info_header;
    BitmapFileHeader file_header;
    int height = image.GetHeight();
    int width = image.GetWidth();
    int padding = GetBMPStride(width);

    file_header.sign[0] = 'B';
    file_header.sign[1] = 'M';
    file_header.sum_size = sizeof(file_header) + sizeof(info_header) + padding * height;
    file_header.padding = sizeof(file_header) + sizeof(info_header);

    info_header.head_size = sizeof(info_header);
    info_header.width = width;
    info_header.height = height;
    info_header.planes_count = 1;
    info_header.bit_per_pixel = 24;
    info_header.type = 0;
    info_header.byte_count = padding * height;
    info_header.horizontal_resolution = 11811;
    info_header.vertical_resolution = 11811;
    info_header.colors_used = 0;
    info_header.major_colors = 0x1000000;

    return {file_header, info_header};
}

bool SaveBMP(const Path& file, const Image& image){
    ofstream out(file,ios::binary);
    int padding = GetBMPStride(image.GetWidth());
    int height = image.GetHeight();
    int width = image.GetWidth();

    auto [file_header, info_header] = ConstructHeaders(image);

    out.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    std::vector<char> buff(padding);

    for(int y = height - 1; y >= 0; --y){
        const Color* line = image.GetLine(y);
        for (int x = 0; x < width; ++x){
            buff[x * 3 + 0] = static_cast<char>(line[x].b);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 2] = static_cast<char>(line[x].r);
        }
        out.write(buff.data(), padding);
    }

    return out.good();
}

Image LoadBMP(const Path& file){
    ifstream ifs(file, ios::binary);
    BitmapFileHeader file_header;
    BitmapInfoHeader info_header;

    ifs.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (file_header.sign[0] != 'B' || file_header.sign[1] != 'M'){
        return {};
    }

    ifs.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    Image result(info_header.width, info_header.height, Color::Black());
    int padding = GetBMPStride(info_header.width);
    std::vector<char> buff(GetBMPStride(padding));

    for (int y = info_header.height - 1; y >= 0; --y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), padding);

        for (int x = 0; x < info_header.width; ++x) {
            line[x].b = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].r = static_cast<byte>(buff[x * 3 + 2]);
        }
    }
    
    return result;
}

}  // namespace img_lib