// PNG->raw converter
// first 64bits are w/h, unsigned (32 each)
// g++ png2raw.cpp -o png2raw -lpng -Wall -O2

// doesn't do indexed PNGs

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <inttypes.h>

#define RGB15(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define BIT(n) (1 << (n))

bool png2raw(char *path, char *opath)
{
    FILE *f = fopen(path, "rb");
    if(!f)
        return false;

    png_byte header[8];
    fread(header, 1, 8, f);
    if(png_sig_cmp((png_byte *) header, 0, 8)) {
        fclose(f);
        return false;
    }

    png_struct *pngfile = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
            NULL, NULL);
    if(!pngfile) {
        fclose(f);
        return false;
    }

    png_info *pnginfo = png_create_info_struct(pngfile);
    if(!pnginfo) {
        png_destroy_read_struct(&pngfile, NULL, NULL);
        fclose(f);
        return false;
    }

    if(setjmp(png_jmpbuf(pngfile))) { // IO init error
        png_destroy_read_struct(&pngfile, &pnginfo, NULL);
        fclose(f);
        return false;
    }
    png_init_io(pngfile, f);

    png_set_sig_bytes(pngfile, 8);
    png_read_info(pngfile, pnginfo);

    // TODO: support Adam7 interlacing
    if(pnginfo->interlace_type != PNG_INTERLACE_NONE) {
        fclose(f);
        return false;
    }

    png_set_interlace_handling(pngfile);
    png_read_update_info(pngfile, pnginfo);

    // allocate row buffer
    png_byte *row = (png_byte *) malloc(pnginfo->rowbytes);

    if(setjmp(png_jmpbuf(pngfile))) { // decompression/read error
        free(row);
        png_destroy_read_struct(&pngfile, &pnginfo, NULL);
        fclose(f);
        return false;
    }

    // does not support alpha, use SetColorKey()
    int pxinc = (pnginfo->color_type == PNG_COLOR_TYPE_RGBA) ? 4 : 3;
    FILE *fo = fopen(opath, "w+");
    if(!fo) {        free(row);
        png_destroy_read_struct(&pngfile, &pnginfo, NULL);
        fclose(f);
        return false;
    }

    uint32_t res = 0;
    res = (uint32_t) pnginfo->width;
    fwrite(&res, 1, 4, fo);
    res = (uint32_t) pnginfo->height;
    fwrite(&res, 1, 4, fo);

    for(unsigned int y = 0; y < pngfile->height; y++) {
        png_read_row(pngfile, row, NULL);

        for(unsigned int x = 0; x < pngfile->width; x++) {
            uint16_t rgb = RGB15(row[(x * pxinc)] / 8, row[(x
                        * pxinc) + 1] / 8, row[(x * pxinc) + 2] / 8);
            if(rgb == RGB15(31, 0, 31))
                rgb &= ~BIT(15);
            else
                rgb |= BIT(15);

            fwrite(&rgb, 1, 2, fo);
        }
    }

    free(row);
    png_read_end(pngfile, NULL);
    png_destroy_read_struct(&pngfile, &pnginfo, NULL);
    fclose(f);
    fclose(fo);

    return true;
}

int main(int argc, char *argv[])
{
    if(argc < 3)
        return 1;

    if(!png2raw(argv[1], argv[2]))
        printf("*** conversion failed\n");

    return 0;
}
