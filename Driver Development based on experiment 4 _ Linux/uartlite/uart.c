#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <termios.h>  
#include <unistd.h>  
  
int set_opt(int,int,int,char,int);  
int main(void)  
{  
    int fd,ret;  
/*  Add your code here  */
	
    char *uart = "/dev/ttyUL";  
    char buffer_out[] = "2016031002009";  

	/*  Add your code here  */

    char buffer_in[512];       
    memset(buffer_in,0,512);  
    fd = open(uart,O_RDWR | O_NOCTTY);  
    if(fd == -1)  
    {  
        printf("%s open failed\n",uart); 
	return -1; 
    }   

    printf("%s open success\n",uart);  
    ret = set_opt(fd,9600,8,'N',1);  
    if(ret == -1)  
    {  
        exit(-1);  
    }  
    ret = write(fd,buffer_out,strlen(buffer_out));
    printf("your number sent  %d\n",ret); 
    while(1)  
    {  
	/*  Add your code here  */
	//1.主程序实现接收字符，并把接收到的字符发送出去
	ret=read(fd,buffer_in,512);
	if(ret>0)
	{
		 printf("your number sent  %d\n",ret);//接收字符
		 ret = write(fd,buffer_out,strlen(buffer_out));//发送出去
	}

	/*  Add your code here  */
    }  
    close(fd);  
}  
  
int set_opt(int fd,int nSpeed,int nBits,char nEvent,int nStop)  
{  
    struct termios newtio,oldtio;  
    if(tcgetattr(fd,&oldtio)!=0)  
    {  
        perror("error:SetupSerial 3\n");  
        return -1;  
    }  
    bzero(&newtio,sizeof(newtio));  
    newtio.c_cflag |= CLOCAL | CREAD;  
    newtio.c_cflag &= ~CSIZE;  
      
    newtio.c_lflag &=~ICANON;
                               


    switch(nBits)  
    {  
        case 7:  
            newtio.c_cflag |= CS7;  
            break;  
        case 8:  
            newtio.c_cflag |=CS8;  
            break;  
    }  
 
    switch(nEvent)  
      
    {  
        case 'O':  
            newtio.c_cflag |= PARENB;  
            newtio.c_cflag |= PARODD;  
            newtio.c_iflag |= (INPCK | ISTRIP);  
            break;  
        case 'E':  
            newtio.c_iflag |= (INPCK | ISTRIP);  
            newtio.c_cflag |= PARENB;  
            newtio.c_cflag &= ~PARODD;  
            break;  
        case 'N':  
            newtio.c_cflag &=~PARENB;  
            break;  
    }  
    switch(nSpeed)  
    {  
        case 2400:  
            cfsetispeed(&newtio,B2400);  
            cfsetospeed(&newtio,B2400);  
            break;  
        case 4800:  
            cfsetispeed(&newtio,B4800);  
            cfsetospeed(&newtio,B4800);  
            break;  
        case 9600:  
            cfsetispeed(&newtio,B9600);  
            cfsetospeed(&newtio,B9600);  
            break;  
        case 115200:  
            cfsetispeed(&newtio,B115200);  
            cfsetospeed(&newtio,B115200);  
            break;  
        case 460800:  
            cfsetispeed(&newtio,B460800);  
            cfsetospeed(&newtio,B460800);  
            break;  
        default:  
            cfsetispeed(&newtio,B9600);  
            cfsetospeed(&newtio,B9600);  
            break;  
    }  
    //ÉèÖÃÍ£Ö¹Î»  
    if(nStop == 1)  
        newtio.c_cflag &= ~CSTOPB;  
    else if(nStop == 2)  
        newtio.c_cflag |= CSTOPB;  
    newtio.c_cc[VTIME] = 5;  
    newtio.c_cc[VMIN] = 0;  
    tcflush(fd,TCIFLUSH);  
      
    if(tcsetattr(fd,TCSANOW,&newtio)!=0)  
    {  
        perror("com set error\n");  
        return -1;  
    }  
    return 0;  
}  
