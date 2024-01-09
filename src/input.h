#ifndef _INPUT_H_
#define _INPUT_H_

#include <cstdint>

using u8 = std::uint8_t;

struct keyboard_inputs {
    u8 keyW;
    u8 keyA;
    u8 keyS;
    u8 keyD;
    u8 keySpace;
    u8 keyP;
};

#endif
