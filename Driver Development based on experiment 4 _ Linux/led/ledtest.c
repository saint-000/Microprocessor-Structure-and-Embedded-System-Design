#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc , char **argv)
{
	int fd;
	int val = 8;
	fd = open("/dev/ees331_led_dev",O_RDWR);
	if (fd < 0)
	{
		printf("error\n");
	}
	int j;
	while(1)
	{	
		printf("please scanf val \n");
		scanf("%d",&val);
		printf("%d",val);
		ioctl(fd,0, val);
	}
}
