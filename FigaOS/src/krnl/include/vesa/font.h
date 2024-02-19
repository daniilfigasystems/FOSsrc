#define PSF1_FONT_MAGIC 0x0436


typedef struct {
    unsigned short magic; // Magic bytes for identification.
    unsigned char fontMode; // PSF font mode.
    unsigned char characterSize; // PSF character size.
} PSF1_Header;
 
 
#define PSF_FONT_MAGIC 0x864ab572
 
typedef struct {
    unsigned int magic;         /* magic bytes to identify PSF */
    unsigned int version;       /* zero */
    unsigned int headersize;    /* offset of bitmaps in file, 32 */
    unsigned int flags;         /* 0 if there's no unicode table */
    unsigned int numglyph;      /* number of glyphs */
    unsigned int bytesperglyph; /* size of each glyph */
    unsigned int height;        /* height in pixels */
    unsigned int width;         /* width in pixels */
} PSF_font;

extern char _binary_src_fonts_ter_powerline_v28b_psf_start;
extern char _binary_src_fonts_ter_powerline_v28b_psf_end;
extern char _binary_src_fonts_ter_powerline_v28b_psf_size;