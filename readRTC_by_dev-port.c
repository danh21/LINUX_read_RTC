#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



#define RTC_addr_port 	0x70
#define RTC_data_port	0x71



int main()
{
	char hour, min, sec, data[5], i;
	int fd = open("/dev/port", O_RDWR);

	for(i = 0; i < 5; i++) {
		lseek(fd, RTC_addr_port, SEEK_SET);	// file - offset - The file offset is set to offset bytes
		write(fd, &i, 1);
		lseek(fd, RTC_data_port, SEEK_SET);
		read(fd, &data[i], 1);
	}

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
}
