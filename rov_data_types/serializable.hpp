//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_SERIALAZER_HPP
#define RC_ROV_SERVER_SERIALAZER_HPP


#include "binary_stream.hpp"
#include <Arduino.h>
namespace rov_types {

    struct serializable {
        enum error_code : uint8_t {
            success,
            success_size_greater,
            size_less,
            crc_mismatch,
            wrong_size,
            wrong_id
        };

        static bool check_for_success(error_code err);

        virtual void serialize(uint8_t *data, size_t *len) = 0;

        virtual error_code deserialize(const uint8_t *input, size_t len) = 0;

        static String error_to_string(error_code err);
    };

};

#endif //RC_ROV_SERVER_SERIALAZER_HPP
