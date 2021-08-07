#ifndef LIGHTMODBUS_ESP_CONFIG_H
#define LIGHTMODBUS_ESP_CONFIG_H

#include "sdkconfig.h"

#ifdef CONFIG_LIGHTMODBUS_DEBUG
#define LIGHTMODBUS_DEBUG
#endif

#ifdef CONFIG_LIGHTMODBUS_FULL
#define LIGHTMODBUS_FULL
#endif

#ifdef CONFIG_LIGHTMODBUS_SLAVE
#define LIGHTMODBUS_SLAVE
#endif

#ifdef CONFIG_LIGHTMODBUS_F01S
#define LIGHTMODBUS_F01S
#endif

#ifdef CONFIG_LIGHTMODBUS_F02S
#define LIGHTMODBUS_F02S
#endif

#ifdef CONFIG_LIGHTMODBUS_F03S
#define LIGHTMODBUS_F03S
#endif

#ifdef CONFIG_LIGHTMODBUS_F04S
#define LIGHTMODBUS_F04S
#endif

#ifdef CONFIG_LIGHTMODBUS_F05S
#define LIGHTMODBUS_F05S
#endif

#ifdef CONFIG_LIGHTMODBUS_F06S
#define LIGHTMODBUS_F06S
#endif

#ifdef CONFIG_LIGHTMODBUS_F15S
#define LIGHTMODBUS_F15S
#endif

#ifdef CONFIG_LIGHTMODBUS_F16S
#define LIGHTMODBUS_F16S
#endif

#ifdef CONFIG_LIGHTMODBUS_F22S
#define LIGHTMODBUS_F22S
#endif

#ifdef CONFIG_LIGHTMODBUS_MASTER
#define LIGHTMODBUS_MASTER
#endif

#ifdef CONFIG_LIGHTMODBUS_MASTER_OMIT_REQUEST_CRC
#define LIGHTMODBUS_MASTER_OMIT_REQUEST_CRC
#endif

#ifdef CONFIG_LIGHTMODBUS_F01M
#define LIGHTMODBUS_F01M
#endif

#ifdef CONFIG_LIGHTMODBUS_F02M
#define LIGHTMODBUS_F02M
#endif

#ifdef CONFIG_LIGHTMODBUS_F03M
#define LIGHTMODBUS_F03M
#endif

#ifdef CONFIG_LIGHTMODBUS_F04M
#define LIGHTMODBUS_F04M
#endif

#ifdef CONFIG_LIGHTMODBUS_F05M
#define LIGHTMODBUS_F05M
#endif

#ifdef CONFIG_LIGHTMODBUS_F06M
#define LIGHTMODBUS_F06M
#endif

#ifdef CONFIG_LIGHTMODBUS_F15M
#define LIGHTMODBUS_F15M
#endif

#ifdef CONFIG_LIGHTMODBUS_F16M
#define LIGHTMODBUS_F16M
#endif

#ifdef CONFIG_LIGHTMODBUS_F22M
#define LIGHTMODBUS_F22M
#endif

#endif
