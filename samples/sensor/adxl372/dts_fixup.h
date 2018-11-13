#if defined(CONFIG_HAS_DTS_I2C)

#ifndef DT_ADXL372_DEV_NAME
#define DT_ADXL372_DEV_NAME ""
#endif
#ifndef DT_ADXL372_I2C_ADDR
#define DT_ADXL372_I2C_ADDR 0
#define DT_ADXL372_I2C_MASTER_DEV_NAME ""
#endif

#endif /* CONFIG_HAS_DTS_I2C */

#if defined(CONFIG_HAS_DTS_SPI)

#ifndef DT_ADXL372_DEV_NAME
#define DT_ADXL372_DEV_NAME ""
#endif
#ifndef DT_ADXL372_SPI_DEV_NAME
#define DT_ADXL372_SPI_DEV_NAME ""
#define DT_ADXL372_SPI_DEV_SLAVE 0
#define DT_ADXL372_SPI_BUS_FREQ 8000000
#endif

#endif /* CONFIG_HAS_DTS_SPI */
