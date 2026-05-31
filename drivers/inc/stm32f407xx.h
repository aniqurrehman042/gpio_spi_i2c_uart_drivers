#pragma once

#include "arm_cortex_m4.h"

// Generic macros

#define NO_PRIORITY_BITS_IMPLEMENTED 4

// Memories

#define FLASH_BASEADDR 0x08000000U
#define ROM_BASEADDR 0x1FFF0000U
#define SRAM1_BASEADDR 0x20000000U
#define SRAM2_BASEADDR 0x20001C00U
#define SRAM SRAM1_BASEADDR

// Buses

#define PERIPH_BASE 0x40000000U
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 0x40010000U
#define AHB1PERIPH_BASE 0x40020000U
#define AHB2PERIPH_BASE 0x50000000U

// AHB1 peripherals

#define GPIOA_BASEADDR (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR (AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR (AHB1PERIPH_BASE + 0x2000)

#define RCC_BASEADDR (AHB1PERIPH_BASE + 0x3800)

// APB1 peripherals

#define I2C1_BASEADDR (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR (APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR (APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR (APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR (APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR (APB1PERIPH_BASE + 0x5000)

// APB2 peripherals

#define EXTI_BASEADDR (APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR (APB2PERIPH_BASE + 0x3000)
#define SYSCFG_BASEADDR (APB2PERIPH_BASE + 0x3800)
#define USART1_BASEADDR (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR (APB2PERIPH_BASE + 0x1400)

// Peripheral registers

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2]; // ARF[0]: AFRL, ARF[1]: AFRH
} gpio_reg_def_t;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} rcc_reg_def_t;

typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} exti_reg_def_t;

typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t RESERVED1[2];
    volatile uint32_t CMPCR;
    volatile uint32_t RESERVED2[2];
    volatile uint32_t CFGR;
} syscfg_reg_def_t;

// Peripheral definitions

#define GPIOA ((gpio_reg_def_t*)GPIOA_BASEADDR)
#define GPIOB ((gpio_reg_def_t*)GPIOB_BASEADDR)
#define GPIOC ((gpio_reg_def_t*)GPIOC_BASEADDR)
#define GPIOD ((gpio_reg_def_t*)GPIOD_BASEADDR)
#define GPIOE ((gpio_reg_def_t*)GPIOE_BASEADDR)
#define GPIOF ((gpio_reg_def_t*)GPIOF_BASEADDR)
#define GPIOG ((gpio_reg_def_t*)GPIOG_BASEADDR)
#define GPIOH ((gpio_reg_def_t*)GPIOH_BASEADDR)
#define GPIOI ((gpio_reg_def_t*)GPIOI_BASEADDR)

#define RCC ((rcc_reg_def_t*)RCC_BASEADDR)

#define EXTI ((exti_reg_def_t*)EXTI_BASEADDR)

#define SYSCFG ((syscfg_reg_def_t*)SYSCFG_BASEADDR)

// GPIO clock enable

#define GPIOA_PCLK_EN() RCC->AHB1ENR |= (1 << 0)
#define GPIOB_PCLK_EN() RCC->AHB1ENR |= (1 << 1)
#define GPIOC_PCLK_EN() RCC->AHB1ENR |= (1 << 2)
#define GPIOD_PCLK_EN() RCC->AHB1ENR |= (1 << 3)
#define GPIOE_PCLK_EN() RCC->AHB1ENR |= (1 << 4)
#define GPIOF_PCLK_EN() RCC->AHB1ENR |= (1 << 5)
#define GPIOG_PCLK_EN() RCC->AHB1ENR |= (1 << 6)
#define GPIOH_PCLK_EN() RCC->AHB1ENR |= (1 << 7)
#define GPIOI_PCLK_EN() RCC->AHB1ENR |= (1 << 8)

// I2C clock enable

#define I2C1_PCLK_EN() RCC->APB1ENR |= (1 << 21)
#define I2C2_PCLK_EN() RCC->APB1ENR |= (1 << 22)
#define I2C3_PCLK_EN() RCC->APB1ENR |= (1 << 23)

// SPI clock enable

#define SPI1_PCLK_EN() RCC->APB2ENR |= (1 << 12)
#define SPI2_PCLK_EN() RCC->APB1ENR |= (1 << 14)
#define SPI3_PCLK_EN() RCC->APB1ENR |= (1 << 15)
#define SPI4_PCLK_EN() RCC->APB2ENR |= (1 << 13)

// USART/UART clock enable

#define USART1_PCLK_EN() RCC->APB2ENR |= (1 << 4)
#define USART2_PCLK_EN() RCC->APB1ENR |= (1 << 17)
#define USART3_PCLK_EN() RCC->APB1ENR |= (1 << 18)
#define UART4_PCLK_EN() RCC->APB1ENR |= (1 << 19)
#define UART5_PCLK_EN() RCC->APB1ENR |= (1 << 20)
#define USART6_PCLK_EN() RCC->APB1ENR |= (1 << 5)

// SYSCFG clock enable

#define SYSCFG_PCLK_EN() RCC->APB2ENR |= (1 << 14)

// GPIO clock disable

#define GPIOA_PCLK_DI() RCC->AHB1ENR &= ~(1 << 0)
#define GPIOB_PCLK_DI() RCC->AHB1ENR &= ~(1 << 1)
#define GPIOC_PCLK_DI() RCC->AHB1ENR &= ~(1 << 2)
#define GPIOD_PCLK_DI() RCC->AHB1ENR &= ~(1 << 3)
#define GPIOE_PCLK_DI() RCC->AHB1ENR &= ~(1 << 4)
#define GPIOF_PCLK_DI() RCC->AHB1ENR &= ~(1 << 5)
#define GPIOG_PCLK_DI() RCC->AHB1ENR &= ~(1 << 6)
#define GPIOH_PCLK_DI() RCC->AHB1ENR &= ~(1 << 7)
#define GPIOI_PCLK_DI() RCC->AHB1ENR &= ~(1 << 8)

// I2C clock disable

#define I2C1_PCLK_DI() RCC->APB1ENR &= ~(1 << 21)
#define I2C2_PCLK_DI() RCC->APB1ENR &= ~(1 << 22)
#define I2C3_PCLK_DI() RCC->APB1ENR &= ~(1 << 23)

// SPI clock disable

#define SPI1_PCLK_DI() RCC->APB2ENR &= ~(1 << 12)
#define SPI2_PCLK_DI() RCC->APB1ENR &= ~(1 << 14)
#define SPI3_PCLK_DI() RCC->APB1ENR &= ~(1 << 15)
#define SPI4_PCLK_DI() RCC->APB2ENR &= ~(1 << 13)

// USART/UART clock disable

#define USART1_PCLK_DI() RCC->APB2ENR &= ~(1 << 4)
#define USART2_PCLK_DI() RCC->APB1ENR &= ~(1 << 17)
#define USART3_PCLK_DI() RCC->APB1ENR &= ~(1 << 18)
#define UART4_PCLK_DI() RCC->APB1ENR &= ~(1 << 19)
#define UART5_PCLK_DI() RCC->APB1ENR &= ~(1 << 20)
#define USART6_PCLK_DI() RCC->APB1ENR &= ~(1 << 5)

// SYSCFG clock disable

#define SYSCFG_PCLK_DI() RCC->APB2ENR &= ~(1 << 14)

// Reset GPIOx Peripherals

#define GPIOA_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 0); \
        RCC->AHB1RSTR &= ~(1 << 0); \
    } while(0)

#define GPIOB_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 1); \
        RCC->AHB1RSTR &= ~(1 << 1); \
    } while(0)

#define GPIOC_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 2); \
        RCC->AHB1RSTR &= ~(1 << 2); \
    } while(0)

#define GPIOD_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 3); \
        RCC->AHB1RSTR &= ~(1 << 3); \
    } while(0)

#define GPIOE_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 4); \
        RCC->AHB1RSTR &= ~(1 << 4); \
    } while(0)

#define GPIOF_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 5); \
        RCC->AHB1RSTR &= ~(1 << 5); \
    } while(0)

#define GPIOG_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 6); \
        RCC->AHB1RSTR &= ~(1 << 6); \
    } while(0)

#define GPIOH_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 7); \
        RCC->AHB1RSTR &= ~(1 << 7); \
    } while(0)

#define GPIOI_REG_RESET() do { \
        RCC->AHB1RSTR |= (1 << 8); \
        RCC->AHB1RSTR &= ~(1 << 8); \
    } while(0)

#define GPIO_BASEADDR_TO_CODE(x) (x == GPIOA) ? 0 : \
    (x == GPIOB) ? 1 : \
    (x == GPIOC) ? 2 : \
    (x == GPIOD) ? 3 : \
    (x == GPIOE) ? 4 : \
    (x == GPIOF) ? 5 : \
    (x == GPIOG) ? 6 : \
    (x == GPIOH) ? 7 : \
    (x == GPIOI) ? 8 : 0

// Generic enums

typedef enum {
    NVIC_IRQ_PRIORITY_0,
    NVIC_IRQ_PRIORITY_1,
    NVIC_IRQ_PRIORITY_2,
    NVIC_IRQ_PRIORITY_3,
    NVIC_IRQ_PRIORITY_4,
    NVIC_IRQ_PRIORITY_5,
    NVIC_IRQ_PRIORITY_6,
    NVIC_IRQ_PRIORITY_7,
    NVIC_IRQ_PRIORITY_8,
    NVIC_IRQ_PRIORITY_9,
    NVIC_IRQ_PRIORITY_10,
    NVIC_IRQ_PRIORITY_11,
    NVIC_IRQ_PRIORITY_12,
    NVIC_IRQ_PRIORITY_13,
    NVIC_IRQ_PRIORITY_14,
    NVIC_IRQ_PRIORITY_15
} nvic_irq_priority_e;

typedef enum {
    STATUS_DISABLE,
    STATUS_ENABLE
} status_e;

typedef enum {
    PIN_RESET,
    PIN_SET
} pin_status_e;

typedef enum {
    IRQ_NO_EXTI0 = 6,
    IRQ_NO_EXTI1 = 7,
    IRQ_NO_EXTI2 = 8,
    IRQ_NO_EXTI3 = 9,
    IRQ_NO_EXTI4 = 10,
    IRQ_NO_EXTI9_5 = 23,
    IRQ_NO_EXTI15_10 = 40
} irq_no_e;
