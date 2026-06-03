#pragma once

#include "spi_driver.h"

// SPI clock setup

void spi_clock_ctrl(const spi_reg_def_t* spix, const status_e status) {
    switch (status) {
        case STATUS_ENABLE:
        {
            if (spix == SPI1) {
                SPI1_PCLK_EN();
            } else if (spix == SPI2) {
                SPI2_PCLK_EN();
            } else if (spix == SPI3) {
                SPI3_PCLK_EN();
            }
        } break;

        case STATUS_DISABLE:
        default:
        {
            if (spix == SPI1) {
                SPI1_PCLK_DI();
            } else if (spix == SPI2) {
                SPI2_PCLK_DI();
            } else if (spix == SPI3) {
                SPI3_PCLK_DI();
            }
        } break;
    }
}

// Init/Deinit

void spi_init(const spi_handle_t* spi_handle) {}
void spi_deinit(const spi_reg_def_t* spix) {}

// Data send/receive

void spi_send(spi_reg_def_t* spix, const uint8_t* tx_buffer, const uint32_t len) {}
void spi_receive(const spi_reg_def_t* spix, uint8_t* tx_buffer, const uint32_t len) {}

// IRQ/ISR config/handling
void spi_irq_interrupt_config(const irq_no_e irq_no, const status_e status) {}
void spi_irq_priority_config(const irq_no_e irq_no, const nvic_irq_priority_e irq_priority) {}
void spi_irq_handling(const spi_handle_t* spi_handle) {}

// Other peripheral control APIs
