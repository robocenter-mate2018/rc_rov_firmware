#pragma once

#include "rov_data_types.hpp"

class data_store
{
public:
	data_store() {
	}
	~data_store() {
	}

	inline rov_types::rov_hardware_control &get_control() {
		return m_control;
	}
	inline rov_types::rov_telimetry &get_telimetry() {
		return m_telimetry;
	}
	inline const rov_types::rov_hardware_control &get_control() const {
		return m_control;
	}
	inline const rov_types::rov_telimetry &get_telimetry() const {
		return m_telimetry;
	}
	inline void set_control(const rov_types::rov_hardware_control &control) {
		m_control = control;
	}
	inline void set_telimetry(const rov_types::rov_telimetry &telimetry) {
		m_telimetry = telimetry;
	}
private:
	rov_types::rov_hardware_control m_control;
	rov_types::rov_telimetry m_telimetry;
	
};