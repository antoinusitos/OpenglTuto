#ifndef DEF_PICOPNG
#define DEF_PICOPNG

#include "UserIncludes.h"

extern int decodePNG(vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

#endif