#pragma once

namespace game
{
    struct player
    {
        void* vtable;          // 0x0000
        char pad_0x0000[0x34]; // 0x0004
        float x_pos;           // 0x0038
        float y_pos;           // 0x003C
        float z_pos;           // 0x0040
        char pad_0x0044[0x2C]; // 0x0044
        bool is_pos_moving;    // 0x0070
        char pad_0x0071[0xF];  // 0x0071
        WORD speed;            // 0x0080
        char pad_0x0082[0x76]; // 0x0082
        int health;            // 0x00F8
        int armor;             // 0X00FC
        char pad_0x0100[0x28]; // 0x0100
        int ammo_mags;         // 0x0128
        char pad_0x012C[0x24]; // 0x012C
        int ammo;              // 0x0150
        char pad_0x0154[0x4];  // 0x0154
        int flashbangs;        // 0x0158
    };
}
