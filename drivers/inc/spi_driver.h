#pragma once

#include "stm32f407xx.h"

typedef enum {
    SPI_DEVICE_MODE_SLAVE,
    SPI_DEVICE_MODE_MASTER
} spi_device_mode_e;

typedef enum {
    SPI_BUS_CONFIG_FD,
    SPI_BUS_CONFIG_HD,
    SPI_BUS_CONFIG_SIMPLEX_RX_ONLY
} spi_bus_config_e;

typedef enum {
    SPI_SCLK_SPEED_DIV_2,
    SPI_SCLK_SPEED_DIV_4,
    SPI_SCLK_SPEED_DIV_8,
    SPI_SCLK_SPEED_DIV_16,
    SPI_SCLK_SPEED_DIV_32,
    SPI_SCLK_SPEED_DIV_64,
    SPI_SCLK_SPEED_DIV_128,
    SPI_SCLK_SPEED_DIV_256
} spi_sclk_speed_e;

typedef enum {
    SPI_DFF_8_BITS,
    SPI_DFF_16_BITS
} spi_dff_e;

typedef enum {
    SPI_CPOL_LOW,
    SPI_CPOL_HIGH
} spi_cpol_e;

typedef enum {
    SPI_CPHA_LOW,
    SPI_CPHA_HIGH
} spi_cpha_e;

typedef enum {
    SPI_SSM_DI,
    SPI_SSM_EN
} spi_ssm_e;

typedef struct {
    spi_device_mode_e device_mode;
    spi_bus_config_e bus_config;
    spi_sclk_speed_e sclk_speed;
    spi_dff_e dff;
    spi_cpol_e cpol;
    spi_cpha_e cpha;
    spi_ssm_e ssm;
} spi_config_t;

typedef struct {
    spi_reg_def_t* spix;
    spi_config_t spi_config;
} spi_handle_t;

// SPI clock setup

void spi_clock_ctrl(const spi_reg_def_t* spix, const status_e status);

// Init/Deinit

void spi_init(const spi_handle_t* spi_handle);
void spi_deinit(const spi_reg_def_t* spix);

// Data send/receive

void spi_send(spi_reg_def_t* spix, const uint8_t* tx_buffer, const uint32_t len);
void spi_receive(const spi_reg_def_t* spix, uint8_t* tx_buffer, const uint32_t len);

// IRQ/ISR config/handling
void spi_irq_interrupt_config(const irq_no_e irq_no, const status_e status);
void spi_irq_priority_config(const irq_no_e irq_no, const nvic_irq_priority_e irq_priority);
void spi_irq_handling(const spi_handle_t* spi_handle);

// Other peripheral control APIs
