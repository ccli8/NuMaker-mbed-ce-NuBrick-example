/* mbed Microcontroller Library
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "nubrick.h"
 
#if defined(TARGET_NUMAKER_PFM_NUC472)
I2C i2c(D14, D15);

#elif defined(TARGET_NUMAKER_PFM_M453)
I2C i2c(D14, D15);

#endif

/** Connect to one NuBrick slave via NuBrick master object
 */
#define NUBRICK_CONNECT(MASTER, NAME)                                   \
    do {                                                                \
        printf("\r\n\r\n");                                             \
        if (! MASTER.connect()) {                                       \
            printf("Connect to NuBrick:\t\t"NAME" failed\r\n\r\n");     \
            return;                                                     \
        }                                                               \
        else {                                                          \
            printf("Connect to NuBrick:\t\t"NAME" OK\r\n\r\n");         \
            MASTER.print_device_desc();                                 \
        }                                                               \
    } while (0);

/** Define NuBrick master objects to communicate with NuBrick slave devices
 */
NuBrickMasterBuzzer master_buzzer(i2c, true);
NuBrickMasterLED master_led(i2c, true);
NuBrickMasterAHRS master_ahrs(i2c, true);
NuBrickMasterSonar master_sonar(i2c, true);
NuBrickMasterTemp master_temp(i2c, true);
NuBrickMasterGas master_gas(i2c, true);
NuBrickMasterIR master_ir(i2c, true);
NuBrickMasterKeys master_keys(i2c, true);

/** Test NuBrick slave devices
 */
void test_nubrick_buzzer(void);
void test_nubrick_led(void);
void test_nubrick_ahrs(void);
void test_nubrick_sonar(void);
void test_nubrick_temp(void);
void test_nubrick_gas(void);
void test_nubrick_ir(void);
void test_nubrick_keys(void);

int main() {
    
    // Test all supported NuBrick slave devices
    test_nubrick_buzzer();
    test_nubrick_led();
    test_nubrick_ahrs();
    test_nubrick_sonar();
    test_nubrick_temp();
    test_nubrick_gas();
    test_nubrick_ir();
    test_nubrick_keys();

    return 0;
}

void test_nubrick_buzzer(void) {
    
    NUBRICK_CONNECT(master_buzzer, "Buzzer");

    // Configure the Buzzer
    master_buzzer.pull_feature_report();
    master_buzzer["feature.sleep_period"].set_value(100);
    master_buzzer["feature.volume"].set_value(60);          // Volume in %
    master_buzzer["feature.tone"].set_value(196);           // Tone in Hz
    master_buzzer["feature.song"].set_value(0);             // 0 (mono), 1 (Bee)
    master_buzzer["feature.period"].set_value(200);         // Period in ms
    master_buzzer["feature.duty"].set_value(30);            // Duty in %
    master_buzzer["feature.latency"].set_value(3);          // Alarm for time secs
    master_buzzer.push_feature_report();
    
    // The NuBrick I2C device may not respond in time. Add delay here.
    wait_ms(50);
    
    // Start sounding the buzzer
    master_buzzer["output.start_flag"].set_value(1);
    master_buzzer["output.stop_flag"].set_value(0);
    master_buzzer.push_output_report();
}

void test_nubrick_led(void) {
    
    NUBRICK_CONNECT(master_led, "LED");
     
    // Configure the LED
    master_led.pull_feature_report();
    master_led["feature.sleep_period"].set_value(100);
    master_led["feature.brightness"].set_value(30);         // Brightness in %
    master_led["feature.color"].set_value(0xF0);            // 0x0F: full blue, 0xF0: full green, 0x0F00: full red
    master_led["feature.blink"].set_value(0);               // Blink method: 0: blink to setting, 1: blink to the song Bee
    master_led["feature.period"].set_value(500);            // Blink period in ms
    master_led["feature.duty"].set_value(30);               // Blink duty in %
    master_led["feature.latency"].set_value(1);             // Blink for time in secs
    master_led.push_feature_report();
    
    // The NuBrick I2C device may not respond in time. Add delay here.
    wait_ms(50);
    
    // Start blinking the LED
    master_led["output.start_flag"].set_value(1);
    master_led["output.stop_flag"].set_value(0);
    master_led.push_output_report();
}

void test_nubrick_ahrs(void) {
    
    NUBRICK_CONNECT(master_ahrs, "AHRS");
    
    master_ahrs.pull_feature_report();    
    // Prescaled vibration alarm threshold
    printf("Prescaled vibration alarm threshold\t\t%d\r\n", master_ahrs["feature.pre_vibration_AT"].get_value());
    
    master_ahrs.pull_input_report();
    // Detected vibration
    printf("Detected vibration\t\t\t\t%d\r\n", master_ahrs["input.vibration"].get_value());
}

void test_nubrick_sonar(void) {
    
    NUBRICK_CONNECT(master_sonar, "Sonar");
    
    master_sonar.pull_feature_report();
    // Distance alarm threshold in cm
    printf("Distance alarm threshold\t\t%d\r\n", master_sonar["feature.distance_AT"].get_value());
    
    master_sonar.pull_input_report();
    // Detected distance in cm
    printf("Detected distance\t\t\t%d\r\n", master_sonar["input.distance"].get_value());
}

void test_nubrick_temp(void) {
    
    NUBRICK_CONNECT(master_temp, "Temperature & Humidity");
    
    master_temp.pull_feature_report();
    // Temp. alarm threshold in Celsius
    printf("Temp. alarm threshold\t\t%d\r\n", master_temp["feature.temp_AT"].get_value());
    // Hum. alarm threshold in %
    printf("Hum. alarm threshold\t\t%d\r\n", master_temp["feature.hum_AT"].get_value());
    
    master_temp.pull_input_report();
    // Detected temp in Celsius
    printf("Detected temp.\t\t\t%d\r\n", master_temp["input.temp"].get_value());
    // Detected hum. in %
    printf("Detected hum.\t\t\t%d\r\n", master_temp["input.hum"].get_value());
}

void test_nubrick_gas(void) {
    
    NUBRICK_CONNECT(master_gas, "Gas");
    
    master_gas.pull_feature_report();
    // Gas alarm threshold in %.
    printf("Gas alarm threshold\t\t%d\r\n", master_gas["feature.gas_AT"].get_value());
    
    master_gas.pull_input_report();
    // Detected gas in %. 80% above for normal.
    printf("Gas\t\t\t\t%d\r\n", master_gas["input.gas"].get_value());
}

void test_nubrick_ir(void) {
    
    NUBRICK_CONNECT(master_ir, "IR");
    
    master_ir.pull_feature_report();
    printf("Number of learned data\t\t%d\r\n", master_ir["feature.num_learned_data"].get_value());
    printf("Using data type\t\t\t%d\r\n", master_ir["feature.using_data_type"].get_value());
    printf("Index of original data to send\t%d\r\n", master_ir["feature.index_orig_data_to_send"].get_value());
    printf("Index of learned data to send\t%d\r\n", master_ir["feature.index_learned_data_to_send"].get_value());
    
    master_ir.pull_input_report();
    printf("Has received data flag\t\t%d\r\n", master_ir["input.received_data_flag"].get_value());
}

void test_nubrick_keys(void) {
    
    NUBRICK_CONNECT(master_keys, "Key");
    
    // Detect 8 keys
    master_keys.pull_input_report();
    uint16_t key_state = master_keys["input.key_state"].get_value();
    unsigned i = 0;
    for (i = 0; i < 8; i ++) {
        if (key_state & (1 << i)) {
            printf("KEY%d PRESSED\r\n", i + 1);
        }
        else {
           printf("KEY%d RELEASED\r\n", i + 1);
        }
    }
}
