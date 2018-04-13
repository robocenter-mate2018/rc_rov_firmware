#ifndef ROV_MANIPULATORPAYLOAD_H
#define ROV_MANIPULATORPAYLOAD_H

#include <stdint.h>
#include "rov_data_types.hpp"
#include "step_motor.h"
#include "device.h"

namespace rov {

class manipulator : public device  {
  public:
    manipulator();

    virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

    ~manipulator();


  private:
	void rotate(int8_t power);
	void open_close(int8_t power);

    step_motor m_axisX;

    step_motor m_axisY;

    int8_t m_valX;

    int8_t m_valY;

};

} // namespace rov
#endif
