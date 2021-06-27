#pragma once

#define _get_bit(byte, bit_pos) (byte & (1 << bit_pos))
#define _set_bit(byte, bit_pos) (byte |= 1 << bit_pos)
#define _clear_bit(byte, bit_pos) (byte &= ~(1 << bit_pos))
#define _toggle_bit(byte, bit_pos) (byte ^= 1 << bit_pos)