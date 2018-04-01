//
// Created by zinjkov on 30.03.18.
//

#ifndef RC_ROV_SERVER_BINARY_STREAM_HPP
#define RC_ROV_SERVER_BINARY_STREAM_HPP


#include <stdint.h>
#include <string.h>

namespace rov_types {
    class binary_stream {
    public:
        enum class byte_ordering {
            big_endian,
            little_endian
        };

        binary_stream();

        binary_stream(const uint8_t *byte_array, size_t len);

        ~binary_stream();

        void data(uint8_t *data, size_t *len);

        void change_byte_ordering(byte_ordering t);

        template<typename T>
        binary_stream &operator>>(T &val) {
            if ((m_len - m_counter) >= sizeof(T))
                read(val);
            return *this;
        }

        template<typename T>
        binary_stream &operator<<(const T &val) {
            write(val);
            return *this;
        }

    private:
        byte_ordering m_system_type;
        byte_ordering m_ordering;
        size_t m_counter;
		size_t m_len;
        uint8_t m_data[255];


        template<typename T>
        inline T swap_endian(T u) {
            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source, dest;

            source.u = u;

            for (size_t k = 0; k < sizeof(T); k++)
                dest.u8[k] = source.u8[sizeof(T) - k - 1];

            return dest.u;
        }

        template<typename T>
        inline void read(T &data) {
            memcpy((void *) (&data), (void *) (&m_data[m_counter]), sizeof(T));
			if (m_ordering != m_system_type) {
				data = swap_endian(data);
			}
            m_counter += sizeof(T);
			m_len += sizeof(T);
        }

        template<typename T>
        inline void write(const T &data) {
            T loc = data;

            if (m_ordering != m_system_type) {
                loc = swap_endian(loc);
            }

            union {
                T u;
                unsigned char u8[sizeof(T)];
            } source;

            source.u = loc;
            for (auto &b : source.u8) {
                m_data[m_len++] = b;
            }
        }
    };

}
#endif //RC_ROV_SERVER_BINARY_STREAM_HPP
