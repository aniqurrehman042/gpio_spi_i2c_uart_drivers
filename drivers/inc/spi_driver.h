#pragma once

#include "stm32f407xx.h"

typedef struct {
    spi_device_mode_e device_mode;
    spi_bus_config_e bus_config;
    spi_scl_speed_e scl_speed;
    spi_dff_e dff;
    spi_cpol_e cpol;
    spi_cpha_e cpha;
    spi_ssm_e ssm;
} spi_config_t;

typedef struct {
    spi_reg_def_t* spix;
    spi_config_t spi_config;
} spi_handle_t;
