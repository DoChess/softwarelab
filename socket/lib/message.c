#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void send_message(int global, char *message) {
        //Sending buffer for "sever to client"
				char buff[300];
				memset(buff,0,300);
				gets(buff);
        write(global,message,300);
}

void receive_message(int global) {
        //receving buffer for "Client to server"
        char buff[300];
        memset(buff,0,300);

        if(read(global,buff,300)!=0)
                puts(buff);
}
