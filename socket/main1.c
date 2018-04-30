#include "lib/server.c"

int main() {
				server();

				while(1) {
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
				return 0;
}
