#ifndef __COMMON_CMD_I2C_HONGSHI_H
#define __COMMON_CMD_I2C_HONGSHI_H
#include <linux/types.h>

int sensor_i2c_init(void);

int set_i2c_dev(char *dev_num);

int i2c_check_sensor(char *chip_addr,char *data_addr, char *len,char *sensor_id);
//int i2c_check_sensor(u_char chip,uint addr,uint alen, uint length);

#endif