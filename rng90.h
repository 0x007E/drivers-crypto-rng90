/**
 * @file rng90.h
 * @brief Header file with declarations and macros for driving an rng90.
 * 
 * This file provides function prototypes, type definitions, and constants for communication with an rng90 crypto chip.
 * 
 * @author g.raf
 * @date 2026-01-24
 * @version 1.0 Release
 * @copyright
 * Copyright (c) 2026 g.raf
 * Released under the GPLv3 License. (see LICENSE in repository)
 * 
 * @note This file is part of a larger project and subject to the license specified in the repository. For updates and the complete revision history, see the GitHub repository.
 * 
 * @see https://github.com/0x007e/drivers-crypto-rng90 "RNG90 crypto driver library"
 */

#ifndef RNG90_H_
#define RNG90_H_

	#ifndef F_CPU
        /**
         * @def F_CPU
         * @brief System clock frequency definition.
         *
         * @details
         * This macro defines the operating frequency of the microcontroller's clock in Hertz. It is used by delay functions and timing calculations. The value should match the actual hardware clock frequency to ensure correct timing behavior in the software.
         */
        #define F_CPU 20000000UL
    #endif

	#ifndef RNG90_HAL_PLATFORM
		/**
         * @def OLED_HAL_PLATFORM
         * @brief Sets the target platform for the OLED hardware abstraction layer (HAL), e.g., `avr` or `avr0`.
         *
         * @details
         * Define this macro with the name of the target platform to select the corresponding platform-specific implementations (such as BUS or TWI access) for the OLED driver.
         *
         * Common values are `avr` (classic AVR architecture) or `avr0` (AVR0/1 series).
         *
         * @note Set this macro as global define as a compiler symbol to select the correct libraries of the whole project.
         */
        #define RNG90_HAL_PLATFORM avr0
    #endif

	#ifndef RNG90_ADDRESS
		/**
		 * @def RNG90_ADDRESS
		 * @brief Defines the TWI/I2C address of the RNG90 device.
		 *
		 * @details
		 * This macro specifies the 7-bit I2C slave address used to communicate with the RNG90 device on the TWI/I2C bus. The value can be overridden by defining `RNG90_ADDRESS` before including this header if the hardware configuration uses a different address.
		 *
		 * @note By default, `RNG90_ADDRESS` is set to `0x40`.
		 */
		#define RNG90_ADDRESS 0x40
	#endif
	
	#ifndef RNG90_RESET_COMMAND
		/**
		 * @def RNG90_RESET_COMMAND
		 * @brief Defines the reset command for the RNG90 device.
		 *
		 * @details
		 * This macro specifies the command value used to reset the RNG90 device via the communication interface. The value can be overridden by defining `RNG90_RESET_COMMAND` before including this header if a different reset command is required by the hardware or protocol configuration.
		 *
		 * @note By default, `RNG90_RESET_COMMAND` is set to `0x00`.
		 */
		#define RNG90_RESET_COMMAND 0x00
	#endif
	
	#ifndef RNG90_SLEEP_COMMAND1
		/**
		 * @def RNG90_SLEEP_COMMAND1
		 * @brief Defines the first sleep command for the RNG90 device.
		 *
		 * @details
		 * This macro specifies the command value used to put the RNG90 device
		 * into a low-power or sleep mode via the communication interface. The value can be overridden by defining `RNG90_SLEEP_COMMAND1` before including this header if a different command is required by the specific hardware or protocol configuration.
		 *
		 * @note By default, `RNG90_SLEEP_COMMAND1` is set to `0x01`.
		 */
		#define RNG90_SLEEP_COMMAND1 0x01
	#endif
	
	#ifndef RNG90_SLEEP_COMMAND2
		/**
		 * @def RNG90_SLEEP_COMMAND2
		 * @brief Defines the second sleep command for the RNG90 device.
		 *
		 * @details
		 * This macro specifies an additional command value used to place the RNG90 device into a low-power or sleep mode via the communication interface. The value can be overridden by defining `RNG90_SLEEP_COMMAND2` before including this header if a different command is required by the specific hardware or protocol configuration.
		 *
		 * @note By default, `RNG90_SLEEP_COMMAND2` is set to `0x02`.
		 */
		#define RNG90_SLEEP_COMMAND2 0x02
	#endif
	
	#ifndef RNG90_EXECUTE_COMMAND
		/**
		 * @def RNG90_EXECUTE_COMMAND
		 * @brief Defines the execute command for the RNG90 device.
		 *
		 * @details
		 * This macro specifies the command value used to initiate the execution of a specific operation on the RNG90 device via the communication interface. The value can be overridden by defining `RNG90_EXECUTE_COMMAND` before including this header if a different command is required by the specific hardware or protocol configuration.
		 *
		 * @note By default, `RNG90_EXECUTE_COMMAND` is set to `0x03`.
		 */
		#define RNG90_EXECUTE_COMMAND 0x03
	#endif
	
	#ifndef RNG90_OPERATION_INFO
		/**
		 * @def RNG90_OPERATION_INFO
		 * @brief Defines the command code for querying operation information of the RNG90 device.
		 *
		 * @details
		 * This macro specifies the base command used to request operation or status information from the RNG90 device via the communication interface. The associated parameter macros `RNG90_OPERATION_INFO_PARAM1` and `RNG90_OPERATION_INFO_PARAM2` further refine the request.
		 *
		 * @note By default, `RNG90_OPERATION_INFO` is set to `0x30`.
		 */
		#define RNG90_OPERATION_INFO 0x30
		
		#ifndef RNG90_OPERATION_INFO_PARAM1
			/**
			 * @def RNG90_OPERATION_INFO_PARAM1
			 * @brief Defines the first parameter for the RNG90 operation info command.
			 *
			 * @details
			 * This macro specifies the first parameter value used together with `RNG90_OPERATION_INFO` when requesting operation information from the RNG90 device. It can be overridden before including this header to adapt the command to a specific use case.
			 *
			 * @note By default, `RNG90_OPERATION_INFO_PARAM1` is set to `0x00`.
			 */
			#define RNG90_OPERATION_INFO_PARAM1 0x00
		#endif
		
		#ifndef RNG90_OPERATION_INFO_PARAM2
			/**
			 * @def RNG90_OPERATION_INFO_PARAM2
			 * @brief Defines the second parameter for the RNG90 operation info command.
			 *
			 * @details
			 * This macro specifies the second parameter value used together with `RNG90_OPERATION_INFO` when requesting operation information from the RNG90 device. It is typically a 16-bit value and may encode additional options or sub-functions of the command.
			 *
			 * @note By default, `RNG90_OPERATION_INFO_PARAM2` is set to `0x0000`.
			 */
			#define RNG90_OPERATION_INFO_PARAM2 0x0000
		#endif
	#endif
	
	#ifndef RNG90_OPERATION_RANDOM
		/**
		 * @def RNG90_OPERATION_RANDOM
		 * @brief Defines the command code for random number generation on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the base command used to request random data from the RNG90 device. The associated parameter and size macros (`RNG90_OPERATION_RANDOM_PARAM1`, `RNG90_OPERATION_RANDOM_PARAM2`, `RNG90_OPERATION_RANDOM_DATA_SIZE`, `RNG90_OPERATION_RANDOM_DATA`, and `RNG90_OPERATION_RANDOM_RNG_SIZE`) further define how the random data request is configured and how much data is returned.
		 *
		 * @note By default, `RNG90_OPERATION_RANDOM` is set to `0x16`.
		 */
		#define RNG90_OPERATION_RANDOM 0x16
		
		#ifndef RNG90_OPERATION_RANDOM_PARAM1
			/**
			 * @def RNG90_OPERATION_RANDOM_PARAM1
			 * @brief Defines the first parameter for the RNG90 random number generation command.
			 *
			 * @details
			 * This macro specifies the first parameter value used together with `RNG90_OPERATION_RANDOM` when requesting random data from the RNG90 device. It can be overridden before including this header to adapt the command to a specific use case.
			 *
			 * @note By default, `RNG90_OPERATION_RANDOM_PARAM1` is set to `0x00`.
			 */
			#define RNG90_OPERATION_RANDOM_PARAM1 0x00
		#endif
		
		#ifndef RNG90_OPERATION_RANDOM_PARAM2
			/**
			 * @def RNG90_OPERATION_RANDOM_PARAM2
			 * @brief Defines the second parameter for the RNG90 random number generation command.
			 *
			 * @details
			 * This macro specifies the second parameter value used together with `RNG90_OPERATION_RANDOM` when requesting random data from the RNG90 device. It is typically a 16-bit value and may encode additional options or sub-functions of the command.
			 *
			 * @note By default, `RNG90_OPERATION_RANDOM_PARAM2` is set to `0x0000`.
			 */
			#define RNG90_OPERATION_RANDOM_PARAM2 0x0000
		#endif
		
		#ifndef RNG90_OPERATION_RANDOM_DATA_SIZE
			/**
			 * @def RNG90_OPERATION_RANDOM_DATA_SIZE
			 * @brief Defines the size of random data to be generated by the RNG90 device.
			 *
			 * @details
			 * This macro specifies the number of random bytes to be generated and returned by the RNG90 device when the `RNG90_OPERATION_RANDOM` command is executed. The value can be adjusted based on application requirements, but must not exceed the maximum supported size of the device.
			 *
			 * @note By default, `RNG90_OPERATION_RANDOM_DATA_SIZE` is set to `20UL`.
			 */
			#define RNG90_OPERATION_RANDOM_DATA_SIZE 20UL

            #ifndef RNG90_OPERATION_RANDOM_DATA
				/**
				 * @def RNG90_OPERATION_RANDOM_DATA
				 * @brief Defines the data buffer for random data generated by the RNG90 device.
				 *
				 * @details
				 * This macro specifies the data buffer used to store the random bytes generated by the RNG90 device when the `RNG90_OPERATION_RANDOM` command is executed. It can be overridden before including this header to adapt the buffer to a specific use case.
				 *
				 * @note By default, `RNG90_OPERATION_RANDOM_DATA` is set to `0x00`.
				 */
                #define RNG90_OPERATION_RANDOM_DATA 0x00
            #endif
		#endif
		
		#ifndef RNG90_OPERATION_RANDOM_RNG_SIZE
			/**
			 * @def RNG90_OPERATION_RANDOM_RNG_SIZE
			 * @brief Defines the size of the RNG state or seed used by the RNG90 device.
			 *
			 * @details
			 * This macro specifies the size of the internal random number generator (RNG) state or seed used by the RNG90 device. This value is important for ensuring the quality and security of the generated random numbers.
			 *
			 * @note By default, `RNG90_OPERATION_RANDOM_RNG_SIZE` is set to `32UL`.
			 */
			#define RNG90_OPERATION_RANDOM_RNG_SIZE 32UL
		#endif
	#endif
	
	#ifndef RNG90_OPERATION_READ
		/**
		 * @def RNG90_OPERATION_READ
		 * @brief Defines the command code for reading data from the RNG90 device.
		 *
		 * @details
		 * This macro specifies the base command used to read data from the RNG90 device. The associated parameter and size macros (`RNG90_OPERATION_READ_PARAM1`, `RNG90_OPERATION_READ_PARAM2`, `RNG90_OPERATION_READ_DATA_SIZE`, and `RNG90_OPERATION_READ_SERIAL_SIZE`) further define how the read request is configured and how much data is returned.
		 *
		 * @note By default, `RNG90_OPERATION_READ` is set to `0x02`.
		 */
		#define RNG90_OPERATION_READ 0x02
		
		#ifndef RNG90_OPERATION_READ_PARAM1
			/**
			 * @def RNG90_OPERATION_READ_PARAM1
			 * @brief Defines the first parameter for the RNG90 read command.
			 *
			 * @details
			 * This macro specifies the first parameter value used together with `RNG90_OPERATION_READ` when requesting data from the RNG90 device. It can be overridden before including this header to adapt the command to a specific use case.
			 *
			 * @note By default, `RNG90_OPERATION_READ_PARAM1` is set to `0x01`.
			 */
			#define RNG90_OPERATION_READ_PARAM1 0x01
		#endif
		
		#ifndef RNG90_OPERATION_READ_PARAM2
			/**
			 * @def RNG90_OPERATION_READ_PARAM2
			 * @brief Defines the second parameter for the RNG90 read command.
			 *
			 * @details
			 * This macro specifies the second parameter value used together with `RNG90_OPERATION_READ` when requesting data from the RNG90 device. It is typically a 16-bit value and may encode additional options or sub-functions of the command.
			 *
			 * @note By default, `RNG90_OPERATION_READ_PARAM2` is set to `0x0000`.
			 */
			#define RNG90_OPERATION_READ_PARAM2 0x0000
		#endif
		
		#ifndef RNG90_OPERATION_READ_DATA_SIZE
			/**
			 * @def RNG90_OPERATION_READ_DATA_SIZE
			 * @brief Defines the size of data to be read from the RNG90 device.
			 *
			 * @details
			 * This macro specifies the number of bytes to be read from the RNG90 device when the `RNG90_OPERATION_READ` command is executed. The value can be adjusted based on application requirements, but must not exceed the maximum supported size of the device.
			 *
			 * @note By default, `RNG90_OPERATION_READ_DATA_SIZE` is set to `16UL`.
			 */
			#define RNG90_OPERATION_READ_DATA_SIZE 16UL
		#endif

		#ifndef RNG90_OPERATION_READ_SERIAL_SIZE
			/**
			 * @def RNG90_OPERATION_READ_SERIAL_SIZE
			 * @brief Defines the size of the serial number data read from the RNG90 device.
			 *
			 * @details
			 * This macro specifies the number of bytes used for the serial number or identification data when reading from the RNG90 device (for example as part of a device information or ID readout sequence). The value can be adjusted to match the format and length defined by the device specification or application requirements.
			 *
			 * @note By default, `RNG90_OPERATION_READ_SERIAL_SIZE` is set to `8UL`.
			 */
		    #define RNG90_OPERATION_READ_SERIAL_SIZE 8UL
		#endif
	#endif
	
	#ifndef RNG90_OPERATION_SELF_TEST
		/**
		 * @def RNG90_OPERATION_SELF_TEST
		 * @brief Defines the command code for triggering self-test routines on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the base command used to start or query internal self-test functions of the RNG90 device, such as DRBG and SHA-256 checks. The associated parameter macros (`RNG90_OPERATION_SELF_TEST_PARAM1_*` and `RNG90_OPERATION_SELF_TEST_PARAM2`) select which tests are executed and how the command is interpreted.
		 *
		 * @note By default, `RNG90_OPERATION_SELF_TEST` is set to `0x77`.
		 */
		#define RNG90_OPERATION_SELF_TEST 0x77

		#ifndef RNG90_OPERATION_SELF_TEST_PARAM1_READ
			/**
			 * @def RNG90_OPERATION_SELF_TEST_PARAM1_READ
			 * @brief Parameter for reading self-test status from the RNG90 device.
			 *
			 * @details
			 * This macro defines the value for the first parameter of the `RNG90_OPERATION_SELF_TEST` command when only the current self-test status or result should be read without starting a new test.
			 *
			 * @note By default, `RNG90_OPERATION_SELF_TEST_PARAM1_READ` is set to `0x00`.
			 */
			#define RNG90_OPERATION_SELF_TEST_PARAM1_READ 0x00
		#endif

		#ifndef RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG
			/**
			 * @def RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG
			 * @brief Parameter for running the DRBG self-test on the RNG90 device.
			 *
			 * @details
			 * This macro defines the value for the first parameter of the `RNG90_OPERATION_SELF_TEST` command when the deterministic random bit generator (DRBG) self-test should be executed.
			 *
			 * @note By default, `RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG` is set to `0x01`.
			 */
			#define RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG 0x01
		#endif

		#ifndef RNG90_OPERATION_SELF_TEST_PARAM1_RUN_SHA256
			/**
			 * @def RNG90_OPERATION_SELF_TEST_PARAM1_RUN_SHA256
			 * @brief Parameter for running the SHA-256 self-test on the RNG90 device.
			 *
			 * @details
			 * This macro defines the value for the first parameter of the `RNG90_OPERATION_SELF_TEST` command when the internal SHA-256 functionality should be verified by a self-test.
			 *
			 * @note By default, `RNG90_OPERATION_SELF_TEST_PARAM1_RUN_SHA256` is set to `0x20`.
			 */
			#define RNG90_OPERATION_SELF_TEST_PARAM1_RUN_SHA256 0x20
		#endif

		#ifndef RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG_AND_SHA256
			/**
			 * @def RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG_AND_SHA256
			 * @brief Parameter for running both DRBG and SHA-256 self-tests on the RNG90 device.
			 *
			 * @details
			 * This macro defines the value for the first parameter of the
			 * `RNG90_OPERATION_SELF_TEST` command when both the DRBG and the
			 * SHA-256 self-tests should be executed in a combined test sequence.
			 *
			 * @note By default, `RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG_AND_SHA256` is set to `0x21`.
			 */
			#define RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG_AND_SHA256 0x21
		#endif

		#ifndef RNG90_OPERATION_SELF_TEST_PARAM2
			/**
			 * @def RNG90_OPERATION_SELF_TEST_PARAM2
			 * @brief Defines the second parameter for the RNG90 self-test command.
			 *
			 * @details
			 * This macro specifies the second parameter value used together with
			 * `RNG90_OPERATION_SELF_TEST`. It is typically a 16-bit value reserved
			 * for future extensions or additional options and is usually kept at
			 * its default value.
			 *
			 * @note By default, `RNG90_OPERATION_SELF_TEST_PARAM2` is set to `0x0000`.
			 */
			#define RNG90_OPERATION_SELF_TEST_PARAM2 0x0000
		#endif
	#endif
	
	#ifndef RNG90_NEW_BUS_TRANSMISSION_US
		/**
		 * @def RNG90_NEW_BUS_TRANSMISSION_US
		 * @brief Defines the minimum delay between two I2C bus transmissions.
		 *
		 * @details
		 * This macro specifies the delay time, in microseconds, that should be observed between consecutive transmissions on the I2C bus when communicating with the RNG90 device. It can be overridden before including this header to meet specific timing or bus-load requirements.
		 *
		 * @note By default, `RNG90_NEW_BUS_TRANSMISSION_US` is set to `2UL`.
		 */
		#define RNG90_NEW_BUS_TRANSMISSION_US 2UL
	#endif
	
	#ifndef RNG90_STATUS_SUCCESSFUL_COMMAND_EXECUTION
		/**
		 * @def RNG90_STATUS_SUCCESSFUL_COMMAND_EXECUTION
		 * @brief Defines the status code for a successfully executed command on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that a command has been processed and completed without errors. It can be checked by the application after a transaction to verify proper command execution.
		 *
		 * @note By default, `RNG90_STATUS_SUCCESSFUL_COMMAND_EXECUTION` is set to `0x00`.
		 */
		#define RNG90_STATUS_SUCCESSFUL_COMMAND_EXECUTION 0x00
	#endif
	
	#ifndef RNG90_STATUS_PARSE_ERROR
		/**
		 * @def RNG90_STATUS_PARSE_ERROR
		 * @brief Defines the status code for a parse error on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that there was an error parsing the received command or parameters. This typically means that the command format was incorrect or contained invalid values.
		 *
		 * @note By default, `RNG90_STATUS_PARSE_ERROR` is set to `0x03`.
		 */
		#define RNG90_STATUS_PARSE_ERROR 0x03
	#endif
	
	#ifndef RNG90_STATUS_SELF_TEST_ERROR
		/**
		 * @def RNG90_STATUS_SELF_TEST_ERROR
		 * @brief Defines the status code for a self-test error on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that a self-test routine has failed. This may indicate an internal fault or malfunction within the device's cryptographic components.
		 *
		 * @note By default, `RNG90_STATUS_SELF_TEST_ERROR` is set to `0x07`.
		 */
		#define RNG90_STATUS_SELF_TEST_ERROR 0x07
	#endif
	
	#ifndef RNG90_STATUS_HEALTH_TEST_ERROR
		/**
		 * @def RNG90_STATUS_HEALTH_TEST_ERROR
		 * @brief Defines the status code for a health test error on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that a health test has failed. Health tests are typically used to verify the integrity and proper functioning of the random number generator components.
		 *
		 * @note By default, `RNG90_STATUS_HEALTH_TEST_ERROR` is set to `0x08`.
		 */
		#define RNG90_STATUS_HEALTH_TEST_ERROR 0x08
	#endif
	
	#ifndef RNG90_STATUS_EXECUTION_ERROR
		/**
		 * @def RNG90_STATUS_EXECUTION_ERROR
		 * @brief Defines the status code for an execution error on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that an error occurred during the execution of a command. This may be due to internal issues or resource constraints.
		 *
		 * @note By default, `RNG90_STATUS_EXECUTION_ERROR` is set to `0x0F`.
		 */
		#define RNG90_STATUS_EXECUTION_ERROR 0x0F
	#endif
	
	#ifndef RNG90_STATUS_AFTER_WAKE
		/**
		 * @def RNG90_STATUS_AFTER_WAKE
		 * @brief Defines the status code indicating the RNG90 device has just woken up from sleep mode.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that it has recently transitioned from a low-power sleep state back to active operation. This status can be used by the application to handle any necessary re-initialization or state management after waking up.
		 *
		 * @note By default, `RNG90_STATUS_AFTER_WAKE` is set to `0x11`.
		 */
		#define RNG90_STATUS_AFTER_WAKE 0x11
	#endif
	
	#ifndef RNG90_STATUS_TWI_ERROR
		/**
		 * @def RNG90_STATUS_TWI_ERROR
		 * @brief Defines the status code for a TWI/I2C communication error with the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value used to indicate that a communication error occurred on the TWI/I2C bus while interacting with the RNG90 device. This may be due to bus contention, incorrect addressing, or other transmission issues.
		 *
		 * @note By default, `RNG90_STATUS_TWI_ERROR` is set to `0xF0`.
		 */
		#define RNG90_STATUS_TWI_ERROR 0xF0
	#endif
	
	#ifndef RNG90_STATUS_CRC_OR_COMMUNICATION_ERROR
		/**
		 * @def RNG90_STATUS_CRC_OR_COMMUNICATION_ERROR
		 * @brief Defines the status code for a CRC or communication error with the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value used to indicate that a cyclic redundancy check (CRC) error or other communication error occurred while exchanging data with the RNG90 device. This typically means that the received data was corrupted or incomplete.
		 *
		 * @note By default, `RNG90_STATUS_CRC_OR_COMMUNICATION_ERROR` is set to `0xFF`.
		 */
		#define RNG90_STATUS_CRC_OR_COMMUNICATION_ERROR 0xFF
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_PASSED_SUCCESSFULLY
		/**
		 * @def RNG90_SELFTEST_STATUS_PASSED_SUCCESSFULLY
		 * @brief Defines the self-test status code indicating all tests passed successfully on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that all executed self-tests, including DRBG and SHA-256 tests, have completed successfully without any errors. This status confirms the integrity and proper functioning of the device's cryptographic components.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_PASSED_SUCCESSFULLY` is set to `0x00`.
		 */
		#define RNG90_SELFTEST_STATUS_PASSED_SUCCESSFULLY 0x00
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_DRBG_SELFTEST_FAIL
		/**
		 * @def RNG90_SELFTEST_STATUS_DRBG_SELFTEST_FAIL
		 * @brief Defines the self-test status code indicating the DRBG self-test failed on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that the deterministic random bit generator (DRBG) self-test has failed. This may indicate an internal fault or malfunction within the DRBG component of the device.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_DRBG_SELFTEST_FAIL` is set to `0x01`.
		 */
		#define RNG90_SELFTEST_STATUS_DRBG_SELFTEST_FAIL 0x01
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_SHA256_SELFTEST_FAIL
		/**
		 * @def RNG90_SELFTEST_STATUS_SHA256_SELFTEST_FAIL
		 * @brief Defines the self-test status code indicating the SHA-256 self-test failed on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that the SHA-256 self-test has failed. This may indicate an internal fault or malfunction within the SHA-256 component of the device.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_SHA256_SELFTEST_FAIL` is set to `0x20`.
		 */
		#define RNG90_SELFTEST_STATUS_SHA256_SELFTEST_FAIL 0x20
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_DRBG_SHA256_SELFTEST_FAIL
		/**
		 * @def RNG90_SELFTEST_STATUS_DRBG_SHA256_SELFTEST_FAIL
		 * @brief Defines the self-test status code indicating both DRBG and SHA-256 self-tests failed on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that both the DRBG and SHA-256 self-tests have failed. This may indicate multiple internal faults or malfunctions within the cryptographic components of the device.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_DRBG_SHA256_SELFTEST_FAIL` is set to `0x21`.
		 */
		#define RNG90_SELFTEST_STATUS_DRBG_SHA256_SELFTEST_FAIL 0x21
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_DRBG_SELFTEST_NOT_RUN
		/**
		 * @def RNG90_SELFTEST_STATUS_DRBG_SELFTEST_NOT_RUN
		 * @brief Defines the self-test status code indicating the DRBG self-test was not run on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that the DRBG self-test was not executed. This may occur if the self-test command was configured to skip the DRBG test or if an error prevented its execution.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_DRBG_SELFTEST_NOT_RUN` is set to `0x02`.
		 */
		#define RNG90_SELFTEST_STATUS_DRBG_SELFTEST_NOT_RUN 0x02
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_SHA256_SELFTEST_NOT_RUN
		/**
		 * @def RNG90_SELFTEST_STATUS_SHA256_SELFTEST_NOT_RUN
		 * @brief Defines the self-test status code indicating the SHA-256 self-test was not run on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that the SHA-256 self-test was not executed. This may occur if the self-test command was configured to skip the SHA-256 test or if an error prevented its execution.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_SHA256_SELFTEST_NOT_RUN` is set to `0x10`.
		 */
		#define RNG90_SELFTEST_STATUS_SHA256_SELFTEST_NOT_RUN 0x10
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_NEITHER_SELFTEST_NOT_RUN
		/**
		 * @def RNG90_SELFTEST_STATUS_NEITHER_SELFTEST_NOT_RUN
		 * @brief Defines the self-test status code indicating neither DRBG nor SHA-256 self-tests were run on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that neither the DRBG nor the SHA-256 self-tests were executed. This may occur if the self-test command was configured to skip both tests or if an error prevented their execution.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_NEITHER_SELFTEST_NOT_RUN` is set to `0x12`.
		 */
		#define RNG90_SELFTEST_STATUS_NEITHER_SELFTEST_NOT_RUN 0x12
	#endif
	
	#ifndef RNG90_SELFTEST_STATUS_ERROR
		/**
		 * @def RNG90_SELFTEST_STATUS_ERROR
		 * @brief Defines the self-test status code indicating an error occurred during self-testing on the RNG90 device.
		 *
		 * @details
		 * This macro specifies the status value returned by the RNG90 device to indicate that an error occurred while performing self-tests. This may be due to internal issues or resource constraints that prevented the tests from completing successfully.
		 *
		 * @note By default, `RNG90_SELFTEST_STATUS_ERROR` is set to `0xFF`.
		 */
		#define RNG90_SELFTEST_STATUS_ERROR 0xFF
	#endif
	
	#ifndef RNG90_INFO_EXECUTION_TIME_MS
		/**
		 * @def RNG90_INFO_EXECUTION_TIME_MS
		 * @brief Defines the typical execution time for RNG90 info commands in milliseconds.
		 *
		 * @details
		 * This macro specifies the expected time, in milliseconds, that the RNG90 device requires to process an information or status query before the result can be safely read. The value can be adjusted if timing measurements or a different device configuration indicate a longer or shorter processing time is needed.
		 *
		 * @note By default, `RNG90_INFO_EXECUTION_TIME_MS` is set to `1UL`.
		 */
		#define RNG90_INFO_EXECUTION_TIME_MS 1UL
	#endif
	
	#ifndef RNG90_RANDOM_EXECUTION_TIME_MS
		/**
		 * @def RNG90_RANDOM_EXECUTION_TIME_MS
		 * @brief Defines the typical execution time for RNG90 random number generation commands in milliseconds.
		 *
		 * @details
		 * This macro specifies the expected time, in milliseconds, that the RNG90 device requires to generate and provide random data after receiving a random number generation command. The value can be adjusted if timing measurements or a different device configuration indicate a longer or shorter processing time is needed.
		 *
		 * @note By default, `RNG90_RANDOM_EXECUTION_TIME_MS` is set to `75UL`.
		 */
		#define RNG90_RANDOM_EXECUTION_TIME_MS 75UL
	#endif
	
	#ifndef RNG90_READ_EXECUTION_TIME_MS
		/**
		 * @def RNG90_READ_EXECUTION_TIME_MS
		 * @brief Defines the typical execution time for RNG90 read commands in milliseconds.
		 *
		 * @details
		 * This macro specifies the expected time, in milliseconds, that the RNG90 device requires to process a read command before the requested data can be safely retrieved. The value can be adjusted if timing measurements or a different device configuration indicate a longer or shorter processing time is needed.
		 *
		 * @note By default, `RNG90_READ_EXECUTION_TIME_MS` is set to `1UL`.
		 */
		#define RNG90_READ_EXECUTION_TIME_MS 1UL
	#endif
	
	#ifndef RNG90_SELFTEST_EXECUTION_TIME_MS
		/**
		 * @def RNG90_SELFTEST_EXECUTION_TIME_MS
		 * @brief Defines the typical execution time for RNG90 self-test commands in milliseconds.
		 *
		 * @details
		 * This macro specifies the expected time, in milliseconds, that the RNG90 device requires to complete self-test routines after receiving a self-test command. The value can be adjusted if timing measurements or a different device configuration indicate a longer or shorter processing time is needed.
		 *
		 * @note By default, `RNG90_SELFTEST_EXECUTION_TIME_MS` is set to `32UL`.
		 */
		#define RNG90_SELFTEST_EXECUTION_TIME_MS 32UL
	#endif
	
	#ifndef RNG90_WDT_RESET_TIME_MS
		/**
		 * @def RNG90_WDT_RESET_TIME_MS
		 * @brief Defines the watchdog timer reset time for the RNG90 device in milliseconds.
		 *
		 * @details
		 * This macro specifies the time, in milliseconds, after which the watchdog timer (WDT) of the RNG90 device will trigger a reset if not serviced. This value is important for ensuring that the device can recover from unexpected conditions or hangs. The value can be adjusted based on application requirements and system design.
		 *
		 * @note By default, `RNG90_WDT_RESET_TIME_MS` is set to `1300UL`.
		 */
		#define RNG90_WDT_RESET_TIME_MS 1300UL
	#endif
	
    #ifndef RNG90_CRC_POLYNOMIAL
		/**
		 * @def RNG90_CRC_POLYNOMIAL
		 * @brief Defines the CRC polynomial used for error checking in RNG90 communications.
		 *
		 * @details
		 * This macro specifies the polynomial value used in the cyclic redundancy check (CRC) algorithm for verifying data integrity during communication with the RNG90 device. The polynomial is typically represented in hexadecimal format and is essential for ensuring that transmitted data has not been corrupted.
		 *
		 * @note By default, `RNG90_CRC_POLYNOMIAL` is set to `0x8005`.
		 */
        #define RNG90_CRC_POLYNOMIAL 0x8005
    #endif

    #ifndef RNG90_CRC_SIZE
		/**
		 * @def RNG90_CRC_SIZE
		 * @brief Defines the size of the CRC field used by the RNG90 device.
		 *
		 * @details
		 * This macro specifies the length, in bytes, of the CRC value appended to data frames exchanged with the RNG90 device. The CRC size is used by the application to allocate buffers and to validate received data integrity.
		 *
		 * @note By default, `RNG90_CRC_SIZE` is set to `2UL`.
		 */
        #define RNG90_CRC_SIZE 2UL
    #endif
	
    #ifndef RNG90_STANDARD_FRAME_SIZE
		/**
		 * @def RNG90_STANDARD_FRAME_SIZE
		 * @brief Defines the standard frame size used by the RNG90 device.
		 *
		 * @details
		 * This macro specifies the default number of bytes in a standard data frame exchanged with the RNG90 device. It is typically used for basic commands or responses that follow a fixed-length frame format and can be adjusted if a different framing scheme is required.
		 *
		 * @note By default, `RNG90_STANDARD_FRAME_SIZE` is set to `4UL`.
		 */
		#define RNG90_STANDARD_FRAME_SIZE 4UL
    #endif
	
    #ifndef RNG90_INFO_FRAME_SIZE
		/**
		 * @def RNG90_INFO_FRAME_SIZE
		 * @brief Defines the frame size for information responses from the RNG90 device. [conversation_history:1]
		 *
		 * @details
		 * This macro specifies the number of bytes in an information or status frame returned by the RNG90 device. [conversation_history:1] It is used by the application to allocate buffers and to parse the received info frames correctly. [conversation_history:1]
		 *
		 * @note By default, `RNG90_INFO_FRAME_SIZE` is set to `7UL`. [conversation_history:1]
		 */
		#define RNG90_INFO_FRAME_SIZE 7UL
    #endif
    
    #ifndef RNG90_NUMBER_FRAME_SIZE
		/**
		 * @def RNG90_NUMBER_FRAME_SIZE
		 * @brief Defines the frame size for random number responses from the RNG90 device.
		 *
		 * @details
		 * This macro specifies the total number of bytes in a data frame that contains random numbers or similar payload returned by the RNG90 device. It is used by the application to allocate buffers and to correctly parse frames that carry random data.
		 *
		 * @note By default, `RNG90_NUMBER_FRAME_SIZE` is set to `35UL`.
		 */
		#define RNG90_NUMBER_FRAME_SIZE 35UL
    #endif
	
    #ifndef RNG90_SERIAL_FRAME_SIZE
		/**
		 * @def RNG90_SERIAL_FRAME_SIZE
		 * @brief Defines the frame size for serial number responses from the RNG90 device.
		 *
		 * @details
		 * This macro specifies the total number of bytes in a data frame that contains the device serial number or identification data returned by the RNG90 device. It is used by the application to allocate buffers and to correctly parse frames that carry serial or ID information.
		 *
		 * @note By default, `RNG90_SERIAL_FRAME_SIZE` is set to `19UL`.
		 */
		#define RNG90_SERIAL_FRAME_SIZE 19UL
    #endif

	#include "../../../utils/macros/stringify.h"

	#include _STR(../../../hal/RNG90_HAL_PLATFORM/twi/twi.h)
	
	#include "../../../utils/crc/crc16.h"
	#include "../../../utils/systick/systick.h"

	/**
     * @enum RNG90_Status_t
     * @brief Represents status codes returned by the RNG90 device.
     *
     * @details
     * This enumeration defines symbolic names for the various status values that can be reported by the RNG90 device after a command execution. It covers successful execution as well as different error and indication conditions, such as parse errors, self-test failures, health test failures, execution errors, wake-up indications, TWI communication errors, and other CRC or communication-related errors.
     */
    enum RNG90_Status_t
    {
        RNG90_Status_Success              = RNG90_STATUS_SUCCESSFUL_COMMAND_EXECUTION, /**< Command executed successfully */
        RNG90_Status_Parse_Error          = RNG90_STATUS_PARSE_ERROR,                  /**< Error while parsing the command or parameters */
        RNG90_Status_SelfTest_Error       = RNG90_STATUS_SELF_TEST_ERROR,              /**< Self-test (e.g. DRBG/SHA) reported an error */
        RNG90_Status_HealthTest_Error     = RNG90_STATUS_HEALTH_TEST_ERROR,            /**< Health test reported an error */
        RNG90_Status_Execution_Error      = RNG90_STATUS_EXECUTION_ERROR,              /**< Error during command execution */
        RNG90_Status_AfterWake_Indication = RNG90_STATUS_AFTER_WAKE,                   /**< Status indicates the device has just woken up */
        RNG90_Status_TWI_Error            = RNG90_STATUS_TWI_ERROR,                    /**< Error on the TWI/I2C communication layer */
        RNG90_Status_Other_Error          = RNG90_STATUS_CRC_OR_COMMUNICATION_ERROR    /**< CRC mismatch or other unspecified communication error */
    };

    /**
     * @typedef RNG90_Status
     * @brief Alias for enum RNG90_Status_t representing RNG90 status codes.
     */
    typedef enum RNG90_Status_t RNG90_Status;
	
	/**
     * @enum RNG90_Run_SelfTest_t
     * @brief Selects which self-test routine to run on the RNG90 device.
     *
     * @details
     * This enumeration defines the available self-test options that can be requested from the RNG90 device via the self-test operation command. It allows triggering the DRBG self-test, the SHA-256 self-test, or a combined self-test that runs both DRBG and SHA-256 checks.
     */
    enum RNG90_Run_SelfTest_t
    {
        RNG90_Run_DRBG_SelfTest        = RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG,             /**< Run only the DRBG self-test */
        RNG90_Run_SHA256_SelfTest      = RNG90_OPERATION_SELF_TEST_PARAM1_RUN_SHA256,           /**< Run only the SHA-256 self-test */
        RNG90_Run_DBRG_SHA256_SelfTest = RNG90_OPERATION_SELF_TEST_PARAM1_RUN_DRBG_AND_SHA256   /**< Run both DRBG and SHA-256 self-tests */
    };

    /**
     * @typedef RNG90_Run_SelfTest
     * @brief Alias for enum RNG90_Run_SelfTest_t representing RNG90 self-test selections.
     */
    typedef enum RNG90_Run_SelfTest_t RNG90_Run_SelfTest;
	
	/**
     * @enum RNG90_SelfTest_Status_t
     * @brief Represents the result status of self-test routines on the RNG90 device.
     *
     * @details
     * This enumeration defines the possible outcome codes reported by the
     * RNG90 device after executing internal self-tests. It distinguishes
     * between successful completion, individual DRBG or SHA-256 failures,
     * tests that were not executed, combined DRBG/SHA-256 failures, and
     * a generic error state.
     */
    enum RNG90_SelfTest_Status_t
    {
        RNG90_SelfTest_Success              = RNG90_SELFTEST_STATUS_PASSED_SUCCESSFULLY,       /**< All requested self-tests passed successfully */
        RNG90_SelfTest_Fail_DBRG            = RNG90_SELFTEST_STATUS_DRBG_SELFTEST_FAIL,        /**< DRBG self-test failed */
        RNG90_SelfTest_Not_Run_DBRG         = RNG90_SELFTEST_STATUS_DRBG_SELFTEST_NOT_RUN,     /**< DRBG self-test was not executed */
        RNG90_SelfTest_Not_Run_SHA256       = RNG90_SELFTEST_STATUS_SHA256_SELFTEST_NOT_RUN,   /**< SHA-256 self-test was not executed */
        RNG90_SelfTest_Not_Run_Neither      = RNG90_SELFTEST_STATUS_NEITHER_SELFTEST_NOT_RUN,  /**< Neither DRBG nor SHA-256 self-test was executed */
        RNG90_SelfTest_Fail_SHA256          = RNG90_SELFTEST_STATUS_SHA256_SELFTEST_FAIL,      /**< SHA-256 self-test failed */
        RNG90_SelfTest_Fail_DBRG_SHA256     = RNG90_SELFTEST_STATUS_DRBG_SHA256_SELFTEST_FAIL, /**< Both DRBG and SHA-256 self-tests failed */
        RNG90_SelfTest_Error                = RNG90_SELFTEST_STATUS_ERROR                      /**< Undefined or general self-test error condition */
    };

    /**
     * @typedef RNG90_SelfTest_Status
     * @brief Alias for enum RNG90_SelfTest_Status_t representing RNG90 self-test result codes.
     */
    typedef enum RNG90_SelfTest_Status_t RNG90_SelfTest_Status;
	
	/**
     * @struct RNG90_Info_t
     * @brief Holds basic identification and revision information for the RNG90 device.
     *
     * @details
     * This structure contains fields for the device identifier, silicon identifier, and revision information as reported by the RNG90 device. The RFU field is reserved for future use or protocol-specific flags and should typically be left unchanged by the application.
     */
    struct RNG90_Info_t
    {
        unsigned char RFU;       /**< Reserved for future use (RFU) */
        unsigned char DeviceID;  /**< Device identifier of the RNG90 */
        unsigned char SiliconID; /**< Silicon or variant identifier */
        unsigned char Revision;  /**< Hardware or firmware revision information */
    };

    /**
     * @typedef RNG90_Info
     * @brief Alias for struct RNG90_Info_t representing RNG90 device information.
     */
    typedef struct RNG90_Info_t RNG90_Info;

    /**
     * @struct RNG90_Packet_t
     * @brief Represents a generic command or response packet for the RNG90 device.
     *
     * @details
     * This structure describes the basic frame format used to communicate with the RNG90 device. It contains a byte count, an opcode selecting the command or response type, two parameter fields, and a CRC value for data integrity checking. The exact semantics of the parameters depend on the specific command being sent or received.
     */
    struct RNG90_Packet_t
    {
        unsigned char count;   /**< Total number of bytes in the packet (including fields and CRC) */
        unsigned char opcode;  /**< Operation code specifying the command or response type */
        unsigned char param1;  /**< First parameter byte for the command or response */
        unsigned int  param2;  /**< Second parameter field, typically a 16-bit value */
        unsigned int  crc;     /**< CRC value used to verify the integrity of the packet */
    };

    /**
     * @typedef RNG90_Packet
     * @brief Alias for struct RNG90_Packet_t representing an RNG90 packet.
     */
    typedef struct RNG90_Packet_t RNG90_Packet;
	
	/**
     * @enum RNG90_Data_Status_t
     * @brief Indicates whether received RNG90 data is valid.
     *
     * @details
     * This enumeration is used to represent the validation result of data obtained from the RNG90 device. It distinguishes between data that has been verified as correct and usable, and data that failed checks such as CRC or format validation.
     */
    enum RNG90_Data_Status_t
    {
        RNG90_Data_Status_Valid   = 0, /**< Data is valid and passed all checks */
        RNG90_Data_Status_Invalid      /**< Data is invalid or failed verification */
    };

    /**
     * @typedef RNG90_Data_Status
     * @brief Alias for enum RNG90_Data_Status_t representing RNG90 data validity status.
     */
    typedef enum RNG90_Data_Status_t RNG90_Data_Status;
	
	/**
     * @struct RNG90_Frame_t
     * @brief Describes a processed data frame received from the RNG90 device.
     *
     * @details
     * This structure holds meta information about a data frame obtained from the RNG90 device. The length field specifies the number of bytes in the frame payload, while the status field indicates whether the frame data has been validated successfully or found to be invalid.
     */
    struct RNG90_Frame_t
    {
        unsigned char     length; /**< Number of bytes in the frame payload */
        RNG90_Data_Status status; /**< Validation status of the frame data */
    };

    /**
     * @typedef RNG90_Frame
     * @brief Alias for struct RNG90_Frame_t representing an RNG90 data frame.
     */
    typedef struct RNG90_Frame_t RNG90_Frame;
	
    RNG90_Status rng90_init(void);
    RNG90_SelfTest_Status rng90_selftest(RNG90_Run_SelfTest test);
    RNG90_Status rng90_info(RNG90_Info *info);
    RNG90_Status rng90_random(unsigned char *numbers);
    RNG90_Status rng90_serial(unsigned char *serial);

#endif /* RNG90_H_ */