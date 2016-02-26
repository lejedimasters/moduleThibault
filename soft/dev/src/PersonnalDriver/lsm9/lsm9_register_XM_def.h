/******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
*
* File Name	: lsm9ds0_acc_mag.c
* Authors	: AMS - Motion Sensors Div - Application Team
*		: Matteo Dameno (matteo.dameno@st.com)
*		: Denis Ciocca (denis.ciocca@st.com)
*		: Both authors are willing to be considered the contact
*		: and update points for the driver.
* Version       : V.1.0.5
* Date          : 2013/Oct/23
* Description   : LSM9DS0 accelerometer & magnetometer driver
*
*******************************************************************************
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* THE PRESENT SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES
* OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, FOR THE SOLE
* PURPOSE TO SUPPORT YOUR APPLICATION DEVELOPMENT.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
******************************************************************************/
/******************************************************************************/


#ifndef LSM9_REGISTER_XM_DEF_H
#define LSM9_REGISTER_XM_DEF_H


#define REG_WHOAMI_ADDR		(0x0F)	/** Who am i address register */
#define REG_CNTRL0_ADDR		(0x1F)	/** CNTRL0 address register */
#define REG_CNTRL1_ADDR		(0x20)	/** CNTRL1 address register */
#define REG_CNTRL2_ADDR		(0x21)	/** CNTRL2 address register */
#define REG_CNTRL3_ADDR		(0x22)	/** CNTRL3 address register */
#define REG_CNTRL4_ADDR		(0x23)	/** CNTRL4 address register */
#define REG_CNTRL5_ADDR		(0x24)	/** CNTRL5 address register */
#define REG_CNTRL6_ADDR		(0x25)	/** CNTRL6 address register */
#define REG_CNTRL7_ADDR		(0x26)	/** CNTRL7 address register */

#define REG_ACC_DATA_ADDR	(0x28)	/** Acc. data low address register */
#define REG_MAG_DATA_ADDR	(0x08)	/** Mag. data low address register */
#define REG_TEMP_DATA_ADDR	(0x05)	/** Temp. data low address register */

#define REG_GEN_MAG_ADDR	(0x12)	/** INT_CTRL_REG_M address register */
#define INT_SRC_REG_M_ADDR	(0x13)	/** INT_SRC_REG_M address register */
#define REG_GEN_MAG_THR_ADDR	(0x14)	/** INT_THS_L_M address register */
#define MIG_THRESHOLD_ADDR_H	(0x15)	/** INT_THS_H_M address register */
#define REG_GEN1_AXIS_ADDR	(0x30)	/** INT_GEN1_REG address register */
#define INT_GEN1_SRC_ADDR	(0x31)	/** INT_GEN1_SRC address register */
#define REG_GEN1_THR_ADDR	(0x32)	/** INT_GEN1_THS address register */
#define REG_GEN1_DUR_ADDR	(0x33)	/** INT_GEN1_DUR address register */
#define REG_GEN2_AXIS_ADDR	(0x34)	/** INT_GEN2_REG address register */
#define INT_GEN2_SRC_ADDR	(0x35)	/** INT_GEN2_SRC address register */
#define REG_GEN2_THR_ADDR	(0x36)	/** INT_GEN2_THS address register */
#define REG_GEN2_DUR_ADDR	(0x37)	/** INT_GEN2_DUR address register */

/* Sensitivity */
#define SENSITIVITY_ACC_2G	60	/**	ug/LSB	*/
#define SENSITIVITY_ACC_4G	120	/**	ug/LSB	*/
#define SENSITIVITY_ACC_8G	240	/**	ug/LSB	*/
#define SENSITIVITY_ACC_16G	730	/**	ug/LSB	*/

#define SENSITIVITY_MAG_2G	80	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_4G	160	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_8G	320	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_12G	480	/**	ugauss/LSB	*/

/* ODR */
#define ODR_ACC_MASK		(0XF0)	/* Mask for odr change on acc */
#define LSM9DS0_ACC_ODR_OFF	(0x00)  /* Power down */
#define LSM9DS0_ACC_ODR3_125	(0x10)  /* 3.25Hz output data rate */
#define LSM9DS0_ACC_ODR6_25	(0x20)  /* 6.25Hz output data rate */
#define LSM9DS0_ACC_ODR12_5	(0x30)  /* 12.5Hz output data rate */
#define LSM9DS0_ACC_ODR25	(0x40)  /* 25Hz output data rate */
#define LSM9DS0_ACC_ODR50	(0x50)  /* 50Hz output data rate */
#define LSM9DS0_ACC_ODR100	(0x60)  /* 100Hz output data rate */
#define LSM9DS0_ACC_ODR200	(0x70)  /* 200Hz output data rate */
#define LSM9DS0_ACC_ODR400	(0x80)  /* 400Hz output data rate */
#define LSM9DS0_ACC_ODR800	(0x90)  /* 800Hz output data rate */
#define LSM9DS0_ACC_ODR1600	(0xA0)  /* 1600Hz output data rate */

#define ODR_MAG_MASK		(0X1C)	/* Mask for odr change on mag */
#define LSM9DS0_MAG_ODR3_125	(0x00)  /* 3.25Hz output data rate */
#define LSM9DS0_MAG_ODR6_25	(0x04)  /* 6.25Hz output data rate */
#define LSM9DS0_MAG_ODR12_5	(0x08)  /* 12.5Hz output data rate */
#define LSM9DS0_MAG_ODR25	(0x0C)  /* 25Hz output data rate */
#define LSM9DS0_MAG_ODR50	(0x10)  /* 50Hz output data rate */
#define LSM9DS0_MAG_ODR100	(0x14)  /* 100Hz output data rate */

/* Magnetic sensor mode */
#define MSMS_MASK		(0x03)	/* Mask magnetic sensor mode */
#define POWEROFF_MAG		(0x02)	/* Power Down */
#define CONTINUOS_CONVERSION	(0x00)	/* Continuos Conversion */

/* Default values loaded in probe function */
#define WHOIAM_VALUE		(0x49)	/** Who Am I default value */
#define REG_DEF_CNTRL0		(0x00)	/** CNTRL0 default value */
#define REG_DEF_CNTRL1		(0x0F)	/** CNTRL1 default value */
#define REG_DEF_CNTRL2		(0x00)	/** CNTRL2 default value */
#define REG_DEF_CNTRL3		(0x00)	/** CNTRL3 default value */
#define REG_DEF_CNTRL4		(0x00)	/** CNTRL4 default value */
#define REG_DEF_CNTRL5		(0x18)	/** CNTRL5 default value */
#define REG_DEF_CNTRL6		(0x20)	/** CNTRL6 default value */
#define REG_DEF_CNTRL7		(0x02)	/** CNTRL7 default value */

#define REG_DEF_INT_CNTRL_MAG	(0x00)	/** INT_CTRL_REG_M default value */
#define REG_DEF_INT_GEN1	(0x00)	/** INT_GEN1_REG default value */
#define REG_DEF_INT_GEN2	(0x00)	/** INT_GEN2_REG default value */
#define REG_DEF_IIG1_DURATION	(0x00)	/** INT_GEN1_DUR default value */
#define REG_DEF_IIG2_DURATION	(0x00)	/** INT_GEN2_DUR default value */
#define REG_DEF_IIG1_THRESHOLD	(0x00)	/** INT_GEN1_THS default value */
#define REG_DEF_IIG2_THRESHOLD	(0x00)	/** INT_GEN2_THS default value */
#define REG_DEF_MIG_THRESHOLD_L	(0x00)	/** INT_THS_L_M default value */
#define REG_DEF_MIG_THRESHOLD_H	(0x00)	/** INT_THS_H_M default value */

#define REG_DEF_ALL_ZEROS	(0x00)

/* Accelerometer Filter */
#define LSM9DS0_ACC_FILTER_MASK	(0xC0)	/* Mask for filter band change on acc */
#define FILTER_773		773	/* Anti-Aliasing 773 Hz */
#define FILTER_362		362	/* Anti-Aliasing 362 Hz */
#define FILTER_194		194	/* Anti-Aliasing 194 Hz */
#define FILTER_50		50	/* Anti-Aliasing 50 Hz */

/* Temperature */
#define TEMP_MASK		(0x80)	/* Mask for temperature change */
#define TEMP_ON			(0x80)	/* Enable temperature */
#define TEMP_OFF		(0x00)	/* Disable temperature */
#define TEMP_SENSITIVITY	8	/* Sensitivity temperature */
#define OFFSET_TEMP		25	/* Offset temperature */
#define NDTEMP			1000	/* Not Available temperature */

/* Interrupt */
#define GEN1_PIN1_MASK		(0x20)
#define GEN1_PIN2_MASK		(0x40)
#define GEN2_PIN1_MASK		(0x10)
#define GEN2_PIN2_MASK		(0x20)
#define GEN_MAG_PIN1_MASK	(0x08)
#define GEN_MAG_PIN2_MASK	(0x10)
#define GEN_MAG_EN_MASK		(0x01)
#define MAX_DUR_TH		127
#define MAX_TH_MAG		131071
#define GEN_X_HIGH_MASK		(0x02)
#define GEN_X_LOW_MASK		(0x01)
#define GEN_Y_HIGH_MASK		(0x08)
#define GEN_Y_LOW_MASK		(0x04)
#define GEN_Z_HIGH_MASK		(0x20)
#define GEN_Z_LOW_MASK		(0x10)
#define GEN_X_MAG_MASK		(0x80)
#define GEN_Y_MAG_MASK		(0x40)
#define GEN_Z_MAG_MASK		(0x20)

#define GEN1_AND_OR_MASK	(0x80)
#define GEN2_AND_OR_MASK	(0x83)

#define INT_PIN_CONF_MASK	(0x10)
#define INT_POLARITY_MASK	(0x80)


#endif
