//
// Created by zinjkov on 30.03.18.
//

#include "binary_stream.hpp"

namespace rov_types {

	binary_stream::binary_stream() :
		m_counter(0), m_len(0) {
        unsigned short x = 1; /* 0x0001 */
        m_system_type = (*((unsigned char *) &x) == 0) ? byte_ordering::big_endian : byte_ordering::little_endian;
        m_ordering = byte_ordering::big_endian;
    }

	binary_stream::binary_stream(const uint8_t * byte_array, size_t len)
	{
		for (int i = 0; i < len; i++) {
			m_data[i] = byte_array[i];
			m_len = len;
		}
		unsigned short x = 1; /* 0x0001 */
		m_system_type = (*((unsigned char *)&x) == 0) ? byte_ordering::big_endian : byte_ordering::little_endian;
		m_ordering = byte_ordering::big_endian;
	}

    binary_stream::~binary_stream() {

    }

	void binary_stream::data(uint8_t * data, size_t *len)
	{
		for (int i = 0; i < m_len; i++) {
			data[i] = m_data[i];
		}
		*len = m_len;
	}

  

    void binary_stream::change_byte_ordering(binary_stream::byte_ordering ordering) {
        if (m_ordering != ordering) {
            for(auto &b : m_data) {
                b = swap_endian(b);
            }
            m_ordering = ordering;
        }
    }

}