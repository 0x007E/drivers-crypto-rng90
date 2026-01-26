/**
 * @file rng90.c
 *
 * @brief Implementation of the RNG90 driver functions.
 *
 * This file contains the implementation of functions to initialize the RNG90 device, perform self-tests, retrieve device information, generate random numbers, and read the device serial number. It utilizes TWI/I2C communication to interact with the RNG90 hardware.
 *
 * @author g.raf
 * @date 2026-01-25
 * @version 1.0 Release
 * @copyright
 * Copyright (c) 2026 g.raf
 * Released under the GPLv3 License. (see LICENSE in repository)
 * 
 * @note This file is part of a larger project and subject to the license specified in the repository. For updates and the complete revision history, see the GitHub repository.
 * 
 * @see https://github.com/0x007e/driver-crypto-rng90 "RNG90 crypto driver library"
 */

#include "rng90.h"

unsigned char rng90_buffer[87];

/**
 * @brief Initializes the RNG90 device by running a self-test.
 *
 * @return Returns one of the following status codes:
 * - `RNG90_Status_Success` if the DRBG self-test completed successfully and the device is ready for operation.
 * - `RNG90_Status_SelfTest_Error` if the DRBG self-test failed and the device should not be used.
 * 
 * @details
 * This function performs an initialization sequence for the RNG90 device by invoking the `rng90_selftest()` routine with `RNG90_Run_DRBG_SelfTest` to verify the deterministic random bit generator (DRBG) functionality. If the self-test does not report `RNG90_SelfTest_Success`, the function returns RNG90_Status_SelfTest_Error` to indicate that the device failed initialization. When the DRBG self-test completes successfully, the function returns `RNG90_Status_Success`, signaling that the RNG90 is ready for normal operation.
 */
RNG90_Status rng90_init(void)
{
    if(rng90_selftest(RNG90_Run_DRBG_SelfTest) != RNG90_SelfTest_Success)
    {
        return RNG90_Status_SelfTest_Error;
    }
	return RNG90_Status_Success;
}

static void rng90_write(RNG90_Packet *packet)
{
    unsigned char *ptr = (unsigned char *)packet;
	packet->count += 7;

	crc16_init(CRC16_INITIAL_VALUE);

    twi_address(RNG90_ADDRESS, TWI_Write);
    twi_set(RNG90_EXECUTE_COMMAND);
	
    for (unsigned char i=0; i < (sizeof(RNG90_Packet) - RNG90_CRC_SIZE); i++)
    {
		crc16_update(*(ptr + i));
        twi_set(*(ptr + i));
    }
}

static void rng90_command(RNG90_Packet *packet)
{
    twi_start();
    rng90_write(packet);
	
	packet->crc = crc16_result();
	
    twi_set((unsigned char)(0x00FF & packet->crc));
    twi_set((unsigned char)(0x00FF & (packet->crc>>8)));
    twi_stop();
}

static RNG90_Frame rng90_frame;

static RNG90_Frame rng90_data(unsigned char *data)
{
	crc16_init(CRC16_INITIAL_VALUE);
	
	unsigned char temp = 0;
	unsigned int crc = 0x0000;
	
	rng90_frame.length = 1 + RNG90_CRC_SIZE;
	rng90_frame.status = RNG90_Data_Status_Invalid;
	
    twi_start();
    twi_address(RNG90_ADDRESS, TWI_Read);
	
    for (unsigned char i=0; i < rng90_frame.length - RNG90_CRC_SIZE; i++)
    {	
		twi_get(&temp, TWI_ACK);
        crc16_update(temp);
		
		if(i == 0)
		{
			rng90_frame.length = temp;
			continue;
		}
		*(data + i - 1) = temp;
    }
	
	twi_get(&temp, TWI_ACK);
	crc = (0x00FF & temp);
	twi_get(&temp, TWI_NACK);
	crc |= (0xFF00 & (temp<<8));

    twi_stop();
	
	rng90_frame.status = RNG90_Data_Status_Valid;

    if (crc != crc16_result())
    {
	    rng90_frame.status = RNG90_Data_Status_Invalid;
    }
    return rng90_frame;
}

/**
 * @brief Executes a self-test routine on the RNG90 device.
 *
 * @param test Specifies which self-test to run, using a value from ::RNG90_Run_SelfTest:
 * - `RNG90_Run_DRBG_SelfTest`
 * - `RNG90_Run_SHA256_SelfTest`
 * - `RNG90_Run_DBRG_SHA256_SelfTest`
 *
 * @return Returns one of the following self-test status codes:
 * - `RNG90_SelfTest_Success` if the requested self-test completed successfully.
 * - `RNG90_SelfTest_Fail_DBRG` if the DRBG self-test failed.
 * - `RNG90_SelfTest_Fail_SHA256` if the SHA-256 self-test failed.
 * - `RNG90_SelfTest_Fail_DBRG_SHA256` if both DRBG and SHA-256 self-tests failed.
 * - `RNG90_SelfTest_Not_Run_DBRG`, `RNG90_SelfTest_Not_Run_SHA256`,
 *   or `RNG90_SelfTest_Not_Run_Neither` if one or more tests were not executed.
 * - `RNG90_SelfTest_Error` if the response frame is invalid or a general error occurred.
 *
 * @details
 * This function triggers a self-test on the RNG90 device according to the selected @p test mode and evaluates the returned status code. Depending on the self-test result, an appropriate ::RNG90_SelfTest_Status value is returned to the caller.
 */
RNG90_SelfTest_Status rng90_selftest(RNG90_Run_SelfTest test)
{
    RNG90_Packet packet;
    packet.count = 0;
    packet.opcode = RNG90_OPERATION_SELF_TEST;
    packet.param1 = test;
    packet.param2 = RNG90_OPERATION_SELF_TEST_PARAM2;
	packet.crc = 0x0000;

    rng90_command(&packet);
	systick_timer_wait_ms(RNG90_SELFTEST_EXECUTION_TIME_MS);
	
	RNG90_Frame frame = rng90_data(rng90_buffer);
	
	if((frame.length == RNG90_STANDARD_FRAME_SIZE) && (frame.status == RNG90_Data_Status_Valid))
	{
		return (RNG90_SelfTest_Status)(rng90_buffer[0]);
	}
    return RNG90_SelfTest_Error;
}

/**
 * @brief Requests device information from the RNG90 and fills an info structure.
 *
 * @param info Pointer to an ::RNG90_Info structure that will be populated with the following fields if the command completes successfully:
 * - RFU
 * - DeviceID
 * - SiliconID
 * - Revision
 *
 * @return Returns one of the following status codes:
 * - `RNG90_Status_Success` if a valid info response was received and @p info was filled.
 * - `RNG90_Status_SelfTest_Error` (cast from the buffer) if the response is a self-test status frame.
 * - `RNG90_Status_Other_Error` if the response frame is invalid, has an unexpected
 *   length, or another communication/parse error occurred.
 *
 * @details
 * This function requests device information from the RNG90 and evaluates the
 * returned frame. Depending on the response type, it either interprets the
 * first data byte as a self-test status or extracts the identification fields
 * into @p info and returns an appropriate status code.
 */
RNG90_Status rng90_info(RNG90_Info *info)
{
	RNG90_Packet packet;
	packet.count = 0;
	packet.opcode = RNG90_OPERATION_INFO;
	packet.param1 = RNG90_OPERATION_INFO_PARAM1;
	packet.param2 = RNG90_OPERATION_INFO_PARAM2;
	packet.crc = 0x0000;

	rng90_command(&packet);
    systick_timer_wait_ms(RNG90_INFO_EXECUTION_TIME_MS);

	RNG90_Frame frame = rng90_data(rng90_buffer);
	
	if((frame.length == RNG90_STANDARD_FRAME_SIZE) && (frame.status == RNG90_Data_Status_Valid))
	{
		return (RNG90_SelfTest_Status)(rng90_buffer[0]);
	}
	else if (frame.length == RNG90_INFO_FRAME_SIZE && (frame.status == RNG90_Data_Status_Valid))
	{
		info->RFU = rng90_buffer[0];
		info->DeviceID = rng90_buffer[1];
		info->SiliconID = rng90_buffer[2];
		info->Revision = rng90_buffer[3];
		return RNG90_Status_Success;
	}
	return RNG90_Status_Other_Error;
}

/**
 * @brief Requests random numbers from the RNG90 device and stores them in a buffer.
 *
 * @param numbers Pointer to a buffer where the received random bytes will be stored.
 * 
 * @warning The buffer must be able to hold at least `RNG90_OPERATION_RANDOM_RNG_SIZE` bytes.
 *
 * @return Returns one of the following status codes:
 * - `RNG90_Status_Success` if valid random data was received and written to @p numbers.
 * - `RNG90_Status_TWI_Error` if a TWI/I2C transmission error occurred while sending the command or payload.
 * - `RNG90_Status_SelfTest_Error` (cast from the buffer) if the response is a self-test status frame instead of random data.
 * - `RNG90_Status_Other_Error` if the response frame is invalid, has an unexpected length,
 *   or another communication/parse error occurred.
 *
 * @details
 * This function sends a random-number request to the RNG90 device, transmits the associated payload and CRC over TWI/I2C, and then reads back the response frame. Depending on the response type, it either copies the received random bytes into @p numbers or returns an appropriate status code.
 */
RNG90_Status rng90_random(unsigned char *numbers)
{
	RNG90_Packet packet;
	packet.count = RNG90_OPERATION_RANDOM_DATA_SIZE;
	packet.opcode = RNG90_OPERATION_RANDOM;
	packet.param1 = RNG90_OPERATION_RANDOM_PARAM1;
	packet.param2 = RNG90_OPERATION_RANDOM_PARAM2;
	packet.crc = 0x0000;
	
    twi_start();
    rng90_write(&packet);

    for (unsigned char i=0; i < RNG90_OPERATION_RANDOM_DATA_SIZE; i++)
    {
        if(twi_set(RNG90_OPERATION_RANDOM_DATA) != TWI_None)
        {
            twi_stop();
            return RNG90_Status_TWI_Error;
        }
        crc16_update(RNG90_OPERATION_RANDOM_DATA);
    }
	packet.crc = crc16_result();
	
	twi_set((unsigned char)(0x00FF & packet.crc));
	twi_set((unsigned char)(0x00FF & (packet.crc>>8)));
	twi_stop();

    systick_timer_wait_ms(RNG90_RANDOM_EXECUTION_TIME_MS);
	
	RNG90_Frame frame = rng90_data(rng90_buffer);
	
	if((frame.length == RNG90_STANDARD_FRAME_SIZE) && (frame.status == RNG90_Data_Status_Valid))
	{
		return (RNG90_SelfTest_Status)(rng90_buffer[0]);
	}
	else if (frame.length == RNG90_NUMBER_FRAME_SIZE && (frame.status == RNG90_Data_Status_Valid))
	{
		for (unsigned char i=0; i < RNG90_OPERATION_RANDOM_RNG_SIZE; i++)
		{
			*(numbers + i) = rng90_buffer[i];
		}
		return RNG90_Status_Success;
	}
	return RNG90_Status_Other_Error;
}

/**
 * @brief Reads the device serial number from the RNG90 and stores it in a buffer.
 *
 * @param serial Pointer to a buffer where the received serial number bytes will be stored.
 * 
 * The buffer must be able to hold at least `RNG90_OPERATION_READ_SERIAL_SIZE` bytes.
 *
 * @return Returns one of the following status codes:
 * - `RNG90_Status_Success` if a valid serial number frame was received and @p serial was filled.
 * - `RNG90_Status_SelfTest_Error` (cast from the buffer) if the response is a self-test status frame instead of serial data.
 * - `RNG90_Status_Other_Error` if the response frame is invalid, has an unexpected length, or another communication/parse error occurred.
 *
 * @details
 * This function sends a read command to the RNG90 device to obtain its serial number. After the command has been processed, the response frame is evaluated. If valid serial data is returned, the bytes are copied into @p serial and an appropriate ::RNG90_Status value is returned.
 */
RNG90_Status rng90_serial(unsigned char *serial)
{
	RNG90_Packet packet;
	packet.count = 0;
	packet.opcode = RNG90_OPERATION_READ;
	packet.param1 = RNG90_OPERATION_READ_PARAM1;
	packet.param2 = RNG90_OPERATION_READ_PARAM2;
	packet.crc = 0x0000;
	
	rng90_command(&packet);
    systick_timer_wait_ms(RNG90_READ_EXECUTION_TIME_MS);

    RNG90_Frame frame = rng90_data(rng90_buffer);
    
    if((frame.length == RNG90_STANDARD_FRAME_SIZE) && (frame.status == RNG90_Data_Status_Valid))
    {
	    return (RNG90_SelfTest_Status)(rng90_buffer[0]);
    }
    else if (frame.length == RNG90_SERIAL_FRAME_SIZE && (frame.status == RNG90_Data_Status_Valid))
    {
		for (unsigned char i=0; i < RNG90_OPERATION_READ_SERIAL_SIZE; i++)
		{
			*(serial + i) = rng90_buffer[i];
		}
	    return RNG90_Status_Success;
    }
    return RNG90_Status_Other_Error;
}