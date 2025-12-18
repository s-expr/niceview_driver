#include <stdint.h>

#define NV_SPI_SCLK_FREQ 1000000

typedef void* nv_panel;
typedef void* nv_spi_host;
typedef int nv_spi_err;

nv_panel nv_panel_init(uint8_t mosi, uint8_t sclk, uint8_t cs, int freq);
nv_spi_err nv_spi_write_buffer(const nv_panel pl, uint8_t* buf, int count);
