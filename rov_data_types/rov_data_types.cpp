//
// Created by zinjkov on 30.03.18.
//

#include "rov_data_types.hpp"
#include "crc.hpp"


void  rov_types::rov_telimetry::serialize(uint8_t *data, size_t *len) {
    binary_stream bs;
    bs << meta::packet_id;
    bs << roll;
    bs << pitch;
    bs << yaw;
    bs << crc::calculateCRC(data, meta::payload_size);
	bs.data(data, len);
}

rov_types::serializable::error_code rov_types::rov_telimetry::deserialize(const uint8_t *input, size_t len) {
    binary_stream bs(input, len);
    uint8_t packet_id;

    if (len < meta::packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
    if (packet_id != meta::packet_id) {
        return error_code::wrong_id;
    }

    bs >> roll;
    bs >> pitch;
    bs >> yaw;
    int16_t current_crc = 0;
    bs >> current_crc;

    if (current_crc != crc::calculateCRC(input, meta::payload_size)) {
        return error_code::crc_mismatch;
    }

    if (len > meta::packet_size){
        return error_code::success_size_greater;
    }

    return success;
}

void rov_types::rov_control::serialize(uint8_t *data, size_t *len) {
    binary_stream bs;
    bs << meta::packet_id;
    bs << axis_x;
    bs << axis_y;
    bs << axis_z;
    bs << axis_w;
    bs << crc::calculateCRC(data, meta::payload_size);
    bs.data(data, len);
}

rov_types::serializable::error_code rov_types::rov_control::deserialize(const uint8_t *input, size_t len) {
    binary_stream bs(input, len);
    uint8_t packet_id;

    if (len < meta::packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
    if (packet_id != meta::packet_id) {
        return error_code::wrong_id;
    }

    bs >> axis_x;
    bs >> axis_y;
    bs >> axis_z;
    bs >> axis_w;

    int16_t current_crc = 0;
    bs >> current_crc;

    if (current_crc != crc::calculateCRC(input, meta::payload_size)) {
        return error_code::crc_mismatch;
    }

    if (len > meta::packet_size){
        return error_code::success_size_greater;
    }

    return success;
}

void rov_types::rov_hardware_control::serialize(uint8_t *data, size_t *len) {
    binary_stream bs;
    bs << meta::packet_id;

	Serial.println();

    for(auto & p : horizontal_power) {
        bs << p;
    }
    for(auto & p : vertical_power) {
        bs << p;
    }
	bs << crc::calculateCRC(data, meta::payload_size);
    bs.data(data, len);
	Serial.println((int)data[0]);
}

rov_types::serializable::error_code rov_types::rov_hardware_control::deserialize(const uint8_t *input, size_t len) {
    binary_stream bs(input, len);
    uint8_t packet_id;

    if (len < meta::packet_size){
        return error_code::size_less;
    }

    bs >> packet_id;
	
    if (packet_id != meta::packet_id) {
        return error_code::wrong_id;
    }

    for(auto & p : horizontal_power) {
        bs >> p;
    }
    for(auto & p : vertical_power) {
        bs >> p;
    }

    int16_t current_crc = 0;
    bs >> current_crc;
	
	Serial.print((int)current_crc);
	Serial.print(" ");
	Serial.print((int)crc::calculateCRC(input, meta::payload_size));

    if (current_crc != crc::calculateCRC(input, meta::payload_size)) {
        return error_code::crc_mismatch;
    }

    if (len > meta::packet_size){
        return error_code::success_size_greater;
    }

    return success;
}
