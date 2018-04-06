#ifndef ROV_MANIPULATORPAYLOAD_H
#define ROV_MANIPULATORPAYLOAD_H


#include "PayloadTool.h"
#include "Motor.h"
#include <stdint.h>
#include "RovDataStore.h"

namespace rov {

class manipulator {
  public:
    manipulator();

    virtual void init();

    virtual void set(const RovDataStore & store_);

    virtual void commit(RovDataStore & store_);

    ~manipulator();


  private:
    Motor m_axisX;

    Motor m_axisY;

    int8_t m_valX;

    int8_t m_valY;

};

} // namespace rov
#endif
