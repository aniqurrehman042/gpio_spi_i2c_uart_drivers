#include "gpio_driver.h"
#include "stm32f407xx.h"

/**
 * @fn gpio_clock_ctrl
 * 
 * @brief Enables or disables the peripheral clock for the given GPIO port
 * 
 * @param[in] gpiox - GPIO peripheral handle
 * @param[in] status - Enable or disable
 * 
 * @return none
 * 
 * @note none
 */
void gpio_clock_ctrl(const gpio_reg_def_t* gpiox, const status_e status) {
    switch (status) {
        case STATUS_ENABLE:
        {
            if (gpiox == GPIOA) {
                GPIOA_PCLK_EN();
            } else if (gpiox == GPIOB) {
                GPIOB_PCLK_EN();
            } else if (gpiox == GPIOC) {
                GPIOC_PCLK_EN();
            } else if (gpiox == GPIOD) {
                GPIOD_PCLK_EN();
            } else if (gpiox == GPIOE) {
                GPIOE_PCLK_EN();
            } else if (gpiox == GPIOF) {
                GPIOF_PCLK_EN();
            } else if (gpiox == GPIOG) {
                GPIOG_PCLK_EN();
            } else if (gpiox == GPIOH) {
                GPIOH_PCLK_EN();
            } else if (gpiox == GPIOI) {
                GPIOI_PCLK_EN();
            }
        } break;

        case STATUS_DISABLE:
        default:
        {
            if (gpiox == GPIOA) {
                GPIOA_PCLK_DI();
            } else if (gpiox == GPIOB) {
                GPIOB_PCLK_DI();
            } else if (gpiox == GPIOC) {
                GPIOC_PCLK_DI();
            } else if (gpiox == GPIOD) {
                GPIOD_PCLK_DI();
            } else if (gpiox == GPIOE) {
                GPIOE_PCLK_DI();
            } else if (gpiox == GPIOF) {
                GPIOF_PCLK_DI();
            } else if (gpiox == GPIOG) {
                GPIOG_PCLK_DI();
            } else if (gpiox == GPIOH) {
                GPIOH_PCLK_DI();
            } else if (gpiox == GPIOI) {
                GPIOI_PCLK_DI();
            }
        } break;
    }
}

// Init/Deinit

void gpio_init(const gpio_handle_t* gpio_handle) {
    // Configure pin mode
    if (gpio_handle->gpio_pin_config.mode <= GPIO_MODE_ANALOG) {
        uint32_t mode_reg_val = gpio_handle->gpio_pin_config.mode << (2 * gpio_handle->gpio_pin_config.pin_no);
        gpio_handle->gpiox->MODER &= ~(0x03 << (2 * gpio_handle->gpio_pin_config.pin_no));
        gpio_handle->gpiox->MODER |= mode_reg_val;
    } else {
        if (gpio_handle->gpio_pin_config.mode == GPIO_MODE_IT_FT) {
            EXTI->FTSR |= (1 << gpio_handle->gpio_pin_config.pin_no);
            EXTI->RTSR &= ~(1 << gpio_handle->gpio_pin_config.pin_no);
        } else if (gpio_handle->gpio_pin_config.mode == GPIO_MODE_IT_RT) {
            EXTI->RTSR |= (1 << gpio_handle->gpio_pin_config.pin_no);
            EXTI->FTSR &= ~(1 << gpio_handle->gpio_pin_config.pin_no);
        } else if (gpio_handle->gpio_pin_config.mode == GPIO_MODE_IT_RFT) {
            EXTI->FTSR |= (1 << gpio_handle->gpio_pin_config.pin_no);
            EXTI->RTSR |= (1 << gpio_handle->gpio_pin_config.pin_no);
        }

        // GPIO port selection in SYSCFG_EXTICR
        uint8_t syscfg_exticr_idx = gpio_handle->gpio_pin_config.pin_no / 4;
        uint8_t syscfg_exticr_pos = gpio_handle->gpio_pin_config.pin_no % 4;
        uint8_t port_code = GPIO_BASEADDR_TO_CODE(gpio_handle->gpiox);
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[syscfg_exticr_idx] = port_code << (syscfg_exticr_pos * 4);

        // Enable EXTI interrupt in IMR
        EXTI->IMR |= (1 << gpio_handle->gpio_pin_config.pin_no);
    }

    // Configure speed
    uint32_t speed_reg_val = gpio_handle->gpio_pin_config.speed << (2 * gpio_handle->gpio_pin_config.pin_no);
    gpio_handle->gpiox->OSPEEDR &= ~(0x03 << (2 * gpio_handle->gpio_pin_config.pin_no));
    gpio_handle->gpiox->OSPEEDR |= speed_reg_val;

    // Configure PuPd settings
    uint32_t pupd_reg_val = gpio_handle->gpio_pin_config.pupd << (2 * gpio_handle->gpio_pin_config.pin_no);
    gpio_handle->gpiox->PUPDR &= ~(0x03 << (2 * gpio_handle->gpio_pin_config.pin_no));
    gpio_handle->gpiox->PUPDR |= pupd_reg_val;

    // Configure output type
    uint32_t op_type_reg_val = gpio_handle->gpio_pin_config.op_type << gpio_handle->gpio_pin_config.pin_no;
    gpio_handle->gpiox->OTYPER &= ~(0x01 << gpio_handle->gpio_pin_config.pin_no);
    gpio_handle->gpiox->OTYPER |= op_type_reg_val;

    // Configure alt functionality
    if (gpio_handle->gpio_pin_config.mode <= GPIO_MODE_ALFFN) {
        uint8_t afr_idx = gpio_handle->gpio_pin_config.pin_no / 8;
        uint8_t afr_pos = gpio_handle->gpio_pin_config.pin_no % 8;
        gpio_handle->gpiox->AFR[afr_idx] &= ~(0x0F << (4 * afr_pos));
        gpio_handle->gpiox->AFR[afr_idx] |= (gpio_handle->gpio_pin_config.alt_fn_mode << (4 * afr_pos));
    }
}

void gpio_deinit(const gpio_reg_def_t* gpiox) {
    if (gpiox == GPIOA) {
        GPIOA_REG_RESET();
    } else if (gpiox == GPIOB) {
        GPIOB_REG_RESET();
    } else if (gpiox == GPIOC) {
        GPIOC_REG_RESET();
    } else if (gpiox == GPIOD) {
        GPIOD_REG_RESET();
    } else if (gpiox == GPIOE) {
        GPIOE_REG_RESET();
    } else if (gpiox == GPIOF) {
        GPIOF_REG_RESET();
    } else if (gpiox == GPIOG) {
        GPIOG_REG_RESET();
    } else if (gpiox == GPIOH) {
        GPIOH_REG_RESET();
    } else if (gpiox == GPIOI) {
        GPIOI_REG_RESET();
    }
}

// Data read/write

uint8_t gpio_read_input_pin(const gpio_reg_def_t* gpiox, const uint8_t pin_no) {
    return (gpiox->IDR >> pin_no) & 0x01;
}

uint16_t gpio_read_input_port(const gpio_reg_def_t* gpiox) {
    return gpiox->IDR;
}

void gpio_write_output_pin(gpio_reg_def_t* gpiox, const uint8_t pin_no, const pin_status_e pin_status) {
    if (pin_status == PIN_SET) {
        gpiox->ODR |= (0x01 << pin_no);
    } else {
        gpiox->ODR &= ~(0x01 << pin_no);
    }
}

void gpio_write_output_port(gpio_reg_def_t* gpiox, const uint16_t value) {
    gpiox->ODR = value;
}

void gpio_toggle_output_pin(gpio_reg_def_t* gpiox, const uint8_t pin_no) {
    gpiox->ODR ^= (1 << pin_no);
}

// IRQ/ISR config/handling

void gpio_irq_interrupt_config(const irq_no_e irq_no, const status_e status) {
    if (status == STATUS_ENABLE) {
        if (irq_no <= 31) {
            *NVIC_ISER0 |= (1 << irq_no);
        } else if (irq_no < 64) {
            *NVIC_ISER1 |= (1 << (irq_no % 32));
        } else if (irq_no < 96) {
            *NVIC_ISER2 |= (1 << (irq_no % 64));
        }
    } else {
        if (irq_no <= 31) {
            *NVIC_ICER0 |= (1 << irq_no);
        } else if (irq_no < 64) {
            *NVIC_ICER1 |= (1 << (irq_no % 32));
        } else if (irq_no < 96) {
            *NVIC_ICER2 |= (1 << (irq_no % 64));
        }
    }
}

void gpio_irq_priority_config(const irq_no_e irq_no, const nvic_irq_priority_e irq_priority) {
    uint8_t ipr_idx = irq_no / 4;
    uint8_t ipr_pos = irq_no % 4;

    *(NVIC_PR + ipr_idx) |= (irq_priority << ((ipr_pos * 8) + (8 - NO_PRIORITY_BITS_IMPLEMENTED)));
}

void gpio_irq_handling(const gpio_pin_no_e pin_no) {
    if (EXTI->PR & (1 << pin_no)) {
        EXTI->PR |= (1 << pin_no);
    }
}
