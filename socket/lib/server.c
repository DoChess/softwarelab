#include "message.c"

//Declaring Socket as Global for Signalling in my_
int SD;
int fd;

//my_isr is just for changing the behaviour of SIGNAL 2 i.e ctrl+x /////
void my_isr(int n)
{
				printf("In Isr..\n");
				write(fd,"**************SERVER TERMINATED!!************",50);
				close(SD);
				printf("SOCKET closed\n");
				kill(getpid(),9);///Kill this process now…
}

void server()
{

				int portNumber = 8080;

				//FIll the  family and address..so that we can bind this details with the socket to be created..
				struct sockaddr_in addr;
				memset(&addr,0,sizeof(addr));
				addr.sin_family=AF_INET;
				addr.sin_addr.s_addr = htonl(INADDR_ANY);
				addr.sin_port = htons(portNumber);

				//////////////////////Creating a SOCKET/////////////////////////
				if((SD=socket(AF_INET,SOCK_STREAM,0))==-1)
				{
								printf("ERROR:Socket failed\n");

								return ;
				}
				printf("SUCCESS:Socket opened\n");

				///////////////////////////binding.//////////////////////////////////////
				if(bind(SD,(struct sockaddr *)&addr,sizeof(addr))==-1)
				{
								printf("ERROR:Binding on server\n");

								close(SD);
								return;
				}

				///////////////////////////Listening./////////////////////////////////////////
				printf("LIstening\n");
				listen(SD,5);//listen for any client for up to 5 queues

				///////////////////////////////////Accepting/.///////////////////////////////

				if((fd=accept(SD,NULL, NULL))<0)
				{
								printf("ERROR:ACCEPT by server\n");
								close(SD);
								return;
				}
				printf("SUCCESS:ACCEPT by Server\n");

				signal(2,my_isr);//modifying the behaviour of the signal 2 as defined in my_isr..routine

				//////////////////Creating parallel processes in while execution//////////////////////////

				if(fork()==0)//CHILD process..
				{
								while(1)
								{
									send_message(fd, "biscoito");
								}
				}
				else//PARENT process…………..
				{
								while(1)
								{
									receive_message(fd);
								}
				}
}
