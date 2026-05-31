#pragma once

#include "stm32f407xx.h"

typedef enum {
    GPIO_PIN_NO_0,
    GPIO_PIN_NO_1,
    GPIO_PIN_NO_2,
    GPIO_PIN_NO_3,
    GPIO_PIN_NO_4,
    GPIO_PIN_NO_5,
    GPIO_PIN_NO_6,
    GPIO_PIN_NO_7,
    GPIO_PIN_NO_8,
    GPIO_PIN_NO_9,
    GPIO_PIN_NO_10,
    GPIO_PIN_NO_11,
    GPIO_PIN_NO_12,
    GPIO_PIN_NO_13,
    GPIO_PIN_NO_14,
    GPIO_PIN_NO_15
} gpio_pin_no_e;

typedef enum {
    GPIO_MODE_IN,
    GPIO_MODE_OUT,
    GPIO_MODE_ALFFN,
    GPIO_MODE_ANALOG,
    GPIO_MODE_IT_FT,
    GPIO_MODE_IT_RT,
    GPIO_MODE_IT_RFT
} gpio_mode_e;

typedef enum {
    GPIO_OP_TYPE_PP,
    GPIO_OP_TYPE_OD
} gpio_op_type_e;

typedef enum {
    GPIO_SPEED_LOW,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_FAST,
    GPIO_SPEED_HIGH
} gpio_speed_e;

typedef enum {
    GPIO_PIN_PUPD_NONE,
    GPIO_PIN_PU,
    GPIO_PIN_PD
} gpio_pin_pupd_e;

typedef struct {
    gpio_pin_no_e pin_no;
    gpio_mode_e mode;
    gpio_speed_e speed;
    gpio_pin_pupd_e pupd;
    gpio_op_type_e op_type;
    uint8_t alt_fn_mode;
} gpio_pin_config_t;

typedef struct {
    gpio_reg_def_t* gpiox;
    gpio_pin_config_t gpio_pin_config;
} gpio_handle_t;

// GPIO clock setup

void gpio_clock_ctrl(const gpio_reg_def_t* gpiox, const status_e status);

// Init/Deinit

void gpio_init(const gpio_handle_t* gpio_handle);
void gpio_deinit(const gpio_reg_def_t* gpiox);

// Data read/write

uint8_t gpio_read_input_pin(const gpio_reg_def_t* gpiox, const uint8_t pin_no);
uint16_t gpio_read_input_port(const gpio_reg_def_t* gpiox);
void gpio_write_output_pin(gpio_reg_def_t* gpiox, const uint8_t pin_no, const pin_status_e pin_status);
void gpio_write_output_port(gpio_reg_def_t* gpiox, const uint16_t value);
void gpio_toggle_output_pin(gpio_reg_def_t* gpiox, const uint8_t pin_no);

// IRQ/ISR config/handling
void gpio_irq_interrupt_config(const irq_no_e irq_no, const status_e status);
void gpio_irq_priority_config(const irq_no_e irq_no, const nvic_irq_priority_e irq_priority);
void gpio_irq_handling(const gpio_pin_no_e pin_no);
