
#include <sysutil/sysutil.h>
#include <sysutil/video.h>
#include <rsx/rsx.h>
#include <rsx/gcm_sys.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "bitmap.h"

void bitmapInit(Bitmap *bitmap, u32 width, u32 height) {
  s32 status;
  bitmap->pixels = rsxMemalign(128, width * height * 4);
  status = rsxAddressToOffset(bitmap->pixels, &bitmap->offset);
  assert(status==0);
  bitmap->width = width;
  bitmap->height = height;
}

void bitmapDestroy(Bitmap *bitmap) {
  rsxFree(bitmap->pixels);
  bitmap->pixels = NULL;
}

void bitmapSetXpm(Bitmap *bitmap, char * xpm[]) {
  u32 palette[256];
  u32 width, height, ncolors, depth;
  char *p;
  int ln;
  u32 x, y, *pix;

  width = atoi(xpm[0]);
  height = atoi(p = strchr(xpm[0], ' ') + 1);
  ncolors = atoi(p = strchr(p, ' ') + 1);
  depth = atoi(p = strchr(p, ' ') + 1);
  assert(depth == 1);

  bitmapInit(bitmap, width, height);

  /* read palette */
  memset(palette, 0, sizeof(palette));
  for (ln = 1; ln <= ncolors; ++ln)
    palette[(unsigned char)xpm[ln][0]] = strtol(&xpm[ln][5], NULL, 16);

  /* convert image */
  pix = bitmap->pixels;
  for (y = 0; y < height; ++y, ++ln)
    for (x = 0; x < width; ++x)
      *pix++ = palette[(unsigned char)xpm[ln][x]];
}
