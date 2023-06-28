#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>



#define RTC_addr_port 	0x70
#define RTC_data_port	0x71



void dump_port(unsigned char addr_port, unsigned char data_port, unsigned short offset, unsigned short length)
{
	unsigned char i, *data, hour, min, sec;
	data = (unsigned char *)malloc(length * sizeof(unsigned char));

	// write offset value into index port and read data from data port
	for(i = offset; i < offset + length; i++) {
		outb(i, addr_port);
		data[i - offset] = inb(data_port);
	}

	/*for(i = 0; i < length; i++)
		printf("%02X ", data[i]);
	printf("\n");*/

	sec = data[0];
	min = data[2];
	if (data[4] >= 0x00 && data[4] <= 0x09)		// 7h -> 16h
		hour = data[4] + 0x07;
	else if (data[4] >= 0x10 && data[4] <= 0x16)	// 17h -> 23h
		hour = data[4] + 0x01;
	else if (data[4] >= 0x17 && data[4] <= 0x19)	// 0h -> 2h
		hour = data[4] - 0x17;
	else						// 3h -> 6h
		hour = data[4] - 0x1D;

	printf("Real time: %02d:%02x:%02x\n", hour, min, sec);

	free(data);
}



int main(int argc, char *argv[])
{
	iopl(3);		// level 3: give your program access to all I/O ports
	//ioperm(0x70, 2, 1);

	dump_port(RTC_addr_port, RTC_data_port, 0, 5);
}
