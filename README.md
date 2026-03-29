# BinDis
A terminal renderer for previewing memory buffer with target on monochromatic displays like SSD1306 so you don't waste compiling SDK's and long flash times of your MCU/MPU 's and wear of your electronic components.
<p align="center">
  <img src="img/name.png" alt="name" />
</p>

## Use it
### Requirements

- Bit level mindset (use of 0xDEADBEEF at least once)
- UTF-8 & ANSI terminal (nothing to check while not using legacy UNIX)
- POSIX compatible system (same parenthesis but now excluding Windows)
- Recommended to run client and main in a single user (same as above unless you're a linux maniac AKA. gentoo user)

### Installation
The **main program** can be compiled with a simple 
``` bash
make
```

The **client** directory is at (naturally) `client/`, the file where you would want to write your code is `client/client.c` and the API is in `client/bindisClient.h`.

I recomend using `make dev` in `client/` when testing (that I hope is always). It does:
1. Clean (if an error happens and end clean is not reached)
2. Compile    AKA. `make`
3. Run        AKA. `make run`
4. Clean      AKA. `make clean`

### Recommendations
- Understand hexdecimal representation of binary values so you can make your values less verbose (**0xFF** *[4 digits]*  =  **0b11111111** *[10 digits]*)
- Use python shell to try value conversion between binary and hexdecimal
- Bindis can be more comfortable in a good tiling window manager, make one that match your thinking model.

## API
The API in `client/bindisClient.h` handles safety the POSIX shared memory (while you don't move it) and gives you a pointer to the shared buffer. Your shared buffer, the memory space that in real life would read your display, is an array of **uint8_t** which size of bytes (AKA. number of elements of buffer) can be read in `bd->size`.

There is no need for free's, I used static memory and the dynamic shared memory is handled entirely by the kernel.

### Struct bd
The `bd` struct is a data structure to help API initialization. It can be read/write without any risk after correct initialization is made (and if you do not try to access array indexes greater than its sizes).
``` c
struct bd {
	uint8_t * buffer;    //the buffer you would want to write
	uint8_t * keys;      //you are not intended to read or write manually but possible
	uint32_t  width;
	uint32_t  height;
	uint8_t   pages;
	size_t    size;
};
```

## Example of use
``` c
int main(int argc, char * argv[]){
	//bindis initialization process, please set the same resolution values
	//   that you wrote on your config file.
	struct bd bd;
	bd.width  = 128;
	bd.height = 64;
	if (bindisInit(&bd)) return 1;


	bd.buffer[00] = 0b11111111;
	bd.buffer[01] = 0b10001001;
	bd.buffer[02] = 0b10001001;
	bd.buffer[03] = 0b10001001;
	bd.buffer[04] = 0b01110110;

	bd.buffer[07] = 0b11111001;

	bd.buffer[10] = 0b11111110;
	bd.buffer[11] = 0b00000100;
	bd.buffer[12] = 0b00001100;
	bd.buffer[13] = 0b00001000;
	bd.buffer[14] = 0b00011000;
	bd.buffer[15] = 0b11110000;

	bd.buffer[18] = 0b11111111;
	bd.buffer[19] = 0b10000001;
	bd.buffer[20] = 0b10000001;
	bd.buffer[21] = 0b01000010;
	bd.buffer[22] = 0b00111100;

	bd.buffer[25] = 0b11111001;

	bd.buffer[28] = 0b10000110;
	bd.buffer[29] = 0b10001001;
	bd.buffer[30] = 0b10001001;
	bd.buffer[31] = 0b01110001;

	

	return 0;
}
```

## To do
- [x] Make the start process for users
- [x] Check if it can work as a binary in PATH (it might but could be very opaque)
- [x] Add general purpose keys
- [x] Add general purpose keys API
- [x] Make something to differenciate the keys management in the shared memory or make another memory block
- [x] Add the vertical adressing mode
- [x] Finish the preceding points so I can make the project that needed this tool

## Note
This projects was not made with abstraction libraries in mind but for devs working bit level on applications on systems like the project adjacent to this one, libraries or anything this can be useful for.

If is needed a code/structure change for a library to work with this tool, I can add it if is not specific for libraries.
