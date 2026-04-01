#pragma once

#define SHM_MAIN "/bd"
#define SHM_KEYS "/bdkeys"

//keys

#define BD_KEY_Q 0b00000001
#define BD_KEY_A 0b00000010
#define BD_KEY_B 0b00000100
#define BD_KEY_C 0b00001000
#define BD_KEY_D 0b00010000
#define BD_KEY_E 0b00100000
#define BD_KEY_F 0b01000000
#define BD_KEY_G 0b10000000

#define BYTE_SIZE 			8


#define MStoNS 			1000000
#define DEFAULT_ITIME 	1/60*1000* MStoNS


#define BINDIS_LOGO memcpy(bd.buffer, (uint8_t[]){0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00, 0xF9, 0x00, 0x00, 0xFE, 0x04, 0x0C, 0x08, 0x18, 0xF0, 0x00, 0x00, 0xFF, 0x81, 0x81, 0x42, 0x3C, 0x00, 0x00, 0xF9, 0x00, 0x00, 0x86, 0x89, 0x89, 0x71}, 32);
