#include <stdio.h>
#include<string.h>
#include<signal.h>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>

//Declaring SD global for use in isr_routine..
int SD;

void my_isr(int n)
{
				printf("In Isr..\n");
				write(SD,"**************CLient TERMINATED!!************",49);
				close(SD);
				printf("SOCKET closed\n");
				kill(getpid(),9);
}

main(int argc , char * argv[])
{
				int portNumber = 8080;

				//Receiving  buffer///////////////
				char rec_buff[300];
				memset(rec_buff,0,300);

				//Send Buffer////////
				char send_buff[300];
				memset(send_buff,0,300);

				////////////
				struct hostent *hPtr;
				char *remoteHost= "localhost";//Get IP address of the server from the command line arguments …
				if((hPtr = gethostbyname(remoteHost)) == NULL)

				{

								printf("ERROR:gethostbyname\n");
								return;

				}

				//FIll the server family and address details to connect..
				struct sockaddr_in ser_addr;
				memset(&ser_addr,0,sizeof(ser_addr));

				memcpy((char *)&ser_addr.sin_addr, hPtr->h_addr, hPtr->h_length);
				ser_addr.sin_family = AF_INET;
				ser_addr.sin_port = htons((u_short)portNumber);      // Set port number

				//Creating a SOCKET
				if((SD=socket(AF_INET,SOCK_STREAM,0))==-1)
				{
								printf("ERROR:Socket failed\n");
								return ;
				}
				printf("SUCCESS:Socket opened\n");

				/////////////////CONNECT///////////////////////////////////////////
				if( connect(SD, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
				{
								printf("\n Error : Connect SD Failed \n");
								return 1;
				}
				printf("Connection SD Successful\n");

				signal(2,my_isr);//modifying SIGNAL behaviour…………..

				//////////////////Creating parallel process///////////////
				if(fork()==0)//CHILD process…………..
				{
								while(1)
								{
												if(read(SD,rec_buff,300)!=0)
																puts(rec_buff);
								}
				}
				else//PARENT process…………….
				{
								while(1)
								{
												gets(send_buff);
												write(SD,send_buff,300);
								}
				}
}
