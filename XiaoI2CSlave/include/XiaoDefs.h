#ifndef XIAO_DEFS_H_
#define XIAO_DEFS_H_

#include <cstdint>

constexpr uint8_t XIAO_I2C_ADDR = 0x2A;

enum Xiao_SlaveCmd
{
    READ_TDS = 0x00,
    READ_PH = 0x01,
    UNDEF
};

#endif // XIAO_DEFS_H_