

typedef struct {
  u16 indices[4];
  struct {
    f32 x, y, z, t;
  } vertices[4];
} BitQuad;

typedef struct {
  u32 width;
  u32 height;
  u32 *pixels;
  u32 offset;
  BitQuad *quad;
} Bitmap;

void bitmapInit(Bitmap *bitmap, u32 width, u32 height);

void bitmapDestroy(Bitmap *bitmap);

void bitmapSetXpm(Bitmap *bitmap, char * xpm[]);
