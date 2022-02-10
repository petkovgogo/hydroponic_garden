#include "XiaoDefs.h"

#include <iostream>
#include "I2CDevice.h"

int main()
{
    I2CDevice xiao(1, XIAO_I2C_ADDR);
    uint8_t meas[2] = {0};

    xiao.read(Xiao_SlaveCmd::READ_TDS, meas, 2);

    uint16_t res = (meas[0] << 8) | meas[1];

    std::cout << "Content-Type: application/json\n\n";
    std::cout << "{\n";
    std::cout << "    \"tds:\" \"" << res << "\"\n";
    std::cout << "}" << std::endl;

    return 0;
}
