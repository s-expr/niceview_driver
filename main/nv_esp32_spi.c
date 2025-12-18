#include <stdint.h>
#include <driver/spi_master.h>
#include "nv_spi.h"

#define SPI_TRANS_BUFFER_SIZE 12

nv_panel nv_panel_init(uint8_t mosi, uint8_t sclk, uint8_t cs, int freq) {

  spi_bus_config_t bus_cfg = {
    .mosi_io_num = mosi,
    .miso_io_num = -1, 
    .sclk_io_num = sclk,
  };

  //spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
 
  spi_device_interface_config_t dev_cfg = {
    .spics_io_num = cs, 
    .address_bits = 0,
    .dummy_bits = 0,
    .mode = 1,
    .clock_speed_hz = (int)freq,
    .queue_size = 4,
    .flags = SPI_DEVICE_3WIRE,
  };
  spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);

  spi_device_handle_t dev;
  spi_bus_add_device(SPI2_HOST, &dev_cfg, &dev);

  return dev; 
}

spi_transaction_t nv_spi_build_trans(const uint8_t* buf, int count) {
  return (spi_transaction_t){
    .length = count * 8, //length must be in bits
    .rx_buffer = NULL,
    .tx_buffer = buf,
  };
}

nv_spi_err nv_spi_write_buffer(const nv_panel pl, uint8_t* buf, int count) {
  spi_transaction_t trans = nv_spi_build_trans(buf, count);
  return spi_device_transmit(pl, &trans);
}
