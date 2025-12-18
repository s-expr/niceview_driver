#include <stdint.h>
#include <stdio.h>
#include "freertos/idf_additions.h"
#include "opcodes.h"
#include "niceview.h"
#include "nv_spi.h"
#include "spi_config.h"

static uint8_t nv_fb[NICEVIEW_FB_SIZE];

//TODO: MOVE INTO SPI  OR OWN PROTOCOL FILE
nv_spi_err nv_clr(const nv_panel pl){
  nv_cmd_clr cmd = {
    .dummy = 0,
    .mode = NICEVIEW_CLEAR_INV
  };
  return nv_send_cmd(pl, &cmd, sizeof(nv_cmd_clr));
}

nv_spi_err nv_clr_inv(const nv_panel pl){
  nv_cmd_clr cmd = {
    .dummy = 0,
    .mode = NICEVIEW_CLEAR
  };
  return nv_send_cmd(pl, &cmd, sizeof(nv_cmd_clr));
}

nv_spi_err nv_write_buffer(const nv_panel pl, const scanline* lines, int count, int invert) {
  return 0;
}

nv_spi_err nv_sclns(const nv_panel pl, const scanline* lines, int count, int invert) {
  return 0;
}

nv_spi_err nv_send_cmd(const nv_panel pl, const nv_cmd cmd, int size) {
  return nv_spi_write_buffer(pl, cmd, size);
}

//spi_test
void app_main() {
  int in = 2;
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  const nv_panel panel = nv_panel_init(
    SPI_GPIO_MOSI,
    SPI_GPIO_SCLK,
    SPI_GPIO_CS,
    SPI_SCLK_FREQ
  );

  while (1) {
    nv_clr(panel);
    vTaskDelay(50);
    printf("%i\n", in);
    nv_clr_inv(panel);
    vTaskDelay(50);
  }

}
