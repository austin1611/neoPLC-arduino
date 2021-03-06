/***************************************************************************
neoPLC-ENV Library

A library for BME280 by Bosch Sensortec

Copyright (c) 2017, Deft Dynamics
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by Deft Dynamics.
4. Neither the name of Deft Dynamics nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY DEFT DYNAMICS ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DEFT DYNAMICS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/

// elements of this library are based on code by Adafruit Industries,
// released under the following license:
/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
 
// elements of this library are based on code by Bosch Sensortec GmbH,
// released under the following license:
/***************************************************************************
 * Copyright (C) 2016 - 2017 Bosch Sensortec GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of the
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 * The information provided is believed to be accurate and reliable.
 * The copyright holder assumes no responsibility
 * for the consequences of use
 * of such information nor for any infringement of patents or
 * other rights of third parties which may result from its use.
 * No license is granted by implication or otherwise under any patent or
 * patent rights of the copyright holder.
 *
 * File		bme280.c
 * Date		13 Jul 2017
 * Version	3.3.0
 *
 ***************************************************************************/

#ifndef __NEOENV_H__
#define __NEOENV_H__

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#define SEALEVELPRESSURE_HPA 1013.25

    enum
    {
        BME280_REGISTER_DIG_T1              = 0x88,
        BME280_REGISTER_DIG_T2              = 0x8A,
        BME280_REGISTER_DIG_T3              = 0x8C,

        BME280_REGISTER_DIG_P1              = 0x8E,
        BME280_REGISTER_DIG_P2              = 0x90,
        BME280_REGISTER_DIG_P3              = 0x92,
        BME280_REGISTER_DIG_P4              = 0x94,
        BME280_REGISTER_DIG_P5              = 0x96,
        BME280_REGISTER_DIG_P6              = 0x98,
        BME280_REGISTER_DIG_P7              = 0x9A,
        BME280_REGISTER_DIG_P8              = 0x9C,
        BME280_REGISTER_DIG_P9              = 0x9E,

        BME280_REGISTER_DIG_H1              = 0xA1,
        BME280_REGISTER_DIG_H2              = 0xE1,
        BME280_REGISTER_DIG_H3              = 0xE3,
        BME280_REGISTER_DIG_H4              = 0xE4,
        BME280_REGISTER_DIG_H5              = 0xE5,
        BME280_REGISTER_DIG_H6              = 0xE7,

        BME280_REGISTER_CHIPID             = 0xD0,
        BME280_REGISTER_VERSION            = 0xD1,
        BME280_REGISTER_SOFTRESET          = 0xE0,

        BME280_REGISTER_CAL26              = 0xE1,

        BME280_REGISTER_CONTROLHUMID       = 0xF2,
        BME280_REGISTER_STATUS             = 0XF3,
        BME280_REGISTER_CONTROL            = 0xF4,
        BME280_REGISTER_CONFIG             = 0xF5,
        BME280_REGISTER_PRESSUREDATA       = 0xF7,
        BME280_REGISTER_TEMPDATA           = 0xFA,
        BME280_REGISTER_HUMIDDATA          = 0xFD
    };

    typedef struct
    {
        uint16_t dig_T1;
        int16_t  dig_T2;
        int16_t  dig_T3;

        uint16_t dig_P1;
        int16_t  dig_P2;
        int16_t  dig_P3;
        int16_t  dig_P4;
        int16_t  dig_P5;
        int16_t  dig_P6;
        int16_t  dig_P7;
        int16_t  dig_P8;
        int16_t  dig_P9;

        uint8_t  dig_H1;
        int16_t  dig_H2;
        uint8_t  dig_H3;
        int16_t  dig_H4;
        int16_t  dig_H5;
        int8_t   dig_H6;
    } bme280_calib_data;
    
class neoENV {
    public:
        enum sensor_sampling {
            SAMPLING_NONE = 0b000,
            SAMPLING_X1   = 0b001,
            SAMPLING_X2   = 0b010,
            SAMPLING_X4   = 0b011,
            SAMPLING_X8   = 0b100,
            SAMPLING_X16  = 0b101
        };

        enum sensor_mode {
            MODE_SLEEP  = 0b00,
            MODE_FORCED = 0b01,
            MODE_NORMAL = 0b11
        };

        enum sensor_filter {
            FILTER_OFF = 0b000,
            FILTER_X2  = 0b001,
            FILTER_X4  = 0b010,
            FILTER_X8  = 0b011,
            FILTER_X16 = 0b100
        };

        // standby durations in ms 
        enum standby_duration {
            STANDBY_MS_0_5  = 0b000,
            STANDBY_MS_10   = 0b110,
            STANDBY_MS_20   = 0b111,
            STANDBY_MS_62_5 = 0b001,
            STANDBY_MS_125  = 0b010,
            STANDBY_MS_250  = 0b011,
            STANDBY_MS_500  = 0b100,
            STANDBY_MS_1000 = 0b101
        };
    
        // constructors
        neoENV(uint8_t addr=0x77);
        
        bool begin();

	void setSampling(sensor_mode mode              = MODE_NORMAL,
			 sensor_sampling tempSampling  = SAMPLING_X16,
			 sensor_sampling pressSampling = SAMPLING_X16,
			 sensor_sampling humSampling   = SAMPLING_X16,
			 sensor_filter filter          = FILTER_OFF,
			 standby_duration duration     = STANDBY_MS_0_5
			 );
      
        void takeForcedMeasurement();
        float readTemperature(void);
        float readPressure(void);
        float readHumidity(void);
        float readAltitude();

    private:
        void readCoefficients(void);
        bool isReadingCalibration(void);

        void      write8(byte reg, byte value);
        uint8_t   read8(byte reg);
        uint16_t  read16(byte reg);
        uint32_t  read24(byte reg);
        int16_t   readS16(byte reg);
        uint16_t  read16_LE(byte reg); // little endian
        int16_t   readS16_LE(byte reg); // little endian

        uint8_t   _i2caddr = 0x77;
        int32_t   _sensorID;
        int32_t   t_fine;

        bme280_calib_data _bme280_calib;

        // The config register
        struct config {
            // inactive duration (standby time) in normal mode
            // 000 = 0.5 ms
            // 001 = 62.5 ms
            // 010 = 125 ms
            // 011 = 250 ms
            // 100 = 500 ms
            // 101 = 1000 ms
            // 110 = 10 ms
            // 111 = 20 ms
            unsigned int t_sb : 3;

            // filter settings
            // 000 = filter off
            // 001 = 2x filter
            // 010 = 4x filter
            // 011 = 8x filter
            // 100 and above = 16x filter
            unsigned int filter : 3;

            // unused - don't set
            unsigned int none : 1;
            unsigned int spi3w_en : 1;

            unsigned int get() {
                return (t_sb << 5) | (filter << 3) | spi3w_en;
            }
        };
        config _configReg;

        
        // The ctrl_meas register
        struct ctrl_meas {
            // temperature oversampling
            // 000 = skipped
            // 001 = x1
            // 010 = x2
            // 011 = x4
            // 100 = x8
            // 101 and above = x16
            unsigned int osrs_t : 3;

            // pressure oversampling
            // 000 = skipped
            // 001 = x1
            // 010 = x2
            // 011 = x4
            // 100 = x8
            // 101 and above = x16
            unsigned int osrs_p : 3;

            // device mode
            // 00       = sleep
            // 01 or 10 = forced
            // 11       = normal
            unsigned int mode : 2;

            unsigned int get() {
                return (osrs_t << 5) | (osrs_p << 3) | mode;
            }
        };
        ctrl_meas _measReg;

        
        // The ctrl_hum register
        struct ctrl_hum {
            // unused - don't set
            unsigned int none : 5;

            // pressure oversampling
            // 000 = skipped
            // 001 = x1
            // 010 = x2
            // 011 = x4
            // 100 = x8
            // 101 and above = x16
            unsigned int osrs_h : 3;

            unsigned int get() {
                return (osrs_h);
            }
        };
        ctrl_hum _humReg;
};

#endif
