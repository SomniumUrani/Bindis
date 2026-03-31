#include "client.h"

int main(int argc, char * argv[]){
	//bindis initialization process, please set the same resolution values
	//   that you wrote on your config file.
	struct bd bd;
	bd.width  = 128;
	bd.height = 64;
	if (bindisInit(&bd)) return 1;
	/***/
	

	bd.buffer[0] = 0xff;


	return 0;
}
