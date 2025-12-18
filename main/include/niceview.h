#ifndef NICEVIEW

#include <stdint.h>
#include "opcodes.h"
#include "nv_spi.h"

#define NICEVIEW_HEIGHT 68
#define NICEVIEW_WIDTH 160
#define NICEVIEW_FB_SIZE NICEVIEW_HEIGHT*NICEVIEW_WIDTH / 8

typedef void* nv_cmd;

typedef struct {
  uint8_t addr;
  uint8_t pixels[10];
} scanline;

typedef struct nv_cmd_clr{
  uint8_t dummy;
  uint8_t mode; 
} nv_cmd_clr;


//TODO: Implement all clear, inv,  hold, single and multiline modes 
nv_spi_err nv_clr(const nv_panel pl);
nv_spi_err nv_clr_inv(const nv_panel dev);
nv_spi_err nv_sclns(const nv_panel dev, const scanline* lines, int count, int invert);
nv_spi_err nv_scln(const nv_panel dev, const scanline line, int count, int invert);
nv_spi_err nv_send_cmd(const nv_panel dev, const nv_cmd cmd, int size);

#define NICEVIEW
#endif
