#include "spi_driver.h"
#include "stm32f407xx.h"

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

void spi_init(const spi_handle_t* spi_handle) {
    spi_clock_ctrl(spi_handle->spix, STATUS_ENABLE);

    uint32_t spi_cr1_reg_val = 0;
    spi_cr1_reg_val |= (spi_handle->spi_config.device_mode << SPI_CR1_MSTR);
    if (spi_handle->spi_config.bus_config == SPI_BUS_CONFIG_FD) {
        // Clear BIDIMODE
        spi_cr1_reg_val &= ~(1 << SPI_CR1_BIDIMODE);
    } else if (spi_handle->spi_config.bus_config == SPI_BUS_CONFIG_HD) {
        // Set BIDIMODE
        spi_cr1_reg_val |= (1 << SPI_CR1_BIDIMODE);
    } else if (spi_handle->spi_config.bus_config == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY) {
        // Set BIDIMODE
        spi_cr1_reg_val |= (1 << SPI_CR1_BIDIMODE);

        // Set RXONLY
        spi_cr1_reg_val |= (1 << SPI_CR1_RXONLY);
    }

    // Set baud rate
    spi_cr1_reg_val |= (spi_handle->spi_config.sclk_speed << SPI_CR1_BR);

    // Set DFF
    spi_cr1_reg_val |= (spi_handle->spi_config.dff << SPI_CR1_DFF);

    // Set CPOL
    spi_cr1_reg_val |= (spi_handle->spi_config.cpol << SPI_CR1_CPOL);

    // Set CPHA
    spi_cr1_reg_val |= (spi_handle->spi_config.cpha << SPI_CR1_CPHA);

    spi_handle->spix->CR1 = spi_cr1_reg_val;
}

void spi_deinit(const spi_reg_def_t* spix) {}

// Data send/receive

void spi_send(spi_reg_def_t* spix, const uint8_t* tx_buffer, const uint32_t len) {
    uint32_t curr_len = len;
    while (curr_len > 0) {
        while (!(spix->SR & (1 << SPI_SR_TXE)));
        if (spix->CR1 & (1 << SPI_CR1_DFF)) {
            // 16 bit data per cycle
            spix->DR = *(uint16_t*)(tx_buffer);
            tx_buffer += 2;
            curr_len -= 2;
        } else {
            // 8 bit data per cycle
            spix->DR = *tx_buffer;
            tx_buffer++;
            curr_len--;
        }
    }
}

void spi_receive(const spi_reg_def_t* spix, uint8_t* tx_buffer, const uint32_t len) {}

// IRQ/ISR config/handling
void spi_irq_interrupt_config(const irq_no_e irq_no, const status_e status) {}

void spi_irq_priority_config(const irq_no_e irq_no, const nvic_irq_priority_e irq_priority) {}

void spi_irq_handling(const spi_handle_t* spi_handle) {}

// Other peripheral control APIs

void spi_ctrl(spi_reg_def_t* spix, const status_e status) {
    if (status == STATUS_ENABLE) {
        spix->CR1 |= (1 << SPI_CR1_SPE);
    } else {
        spix->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}
