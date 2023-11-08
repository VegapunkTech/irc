
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <fcntl.h>


struct sockaddr_in srv;
#define PORT 9909

int nClientSocket;

int main()
{
    int nRet = 0;
    //Initialize the socket
    nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (nClientSocket < 0)
    {
        std::cout << "The socket not opened" <<std::endl;
    }
    else
    {
        std::cout << "The socket opened" << std::endl;
    }

    //Initilize the environement for sockaddr structure
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(srv.sin_zero), 0, 8);

   nRet = connect(nClientSocket, (struct sockaddr*) &srv, sizeof(srv));



    if (nRet < 0)
    {
        std::cout << "connect failed" << std::endl;
        //exit(EXIT_FAILURE);
    }
    else
    {
        while(1)
        {
            char userInput[50];
            std::cin >> userInput;
            //std::cout << "Vous avez saisi : " << userInput << std::endl;
            send(nClientSocket, userInput , strlen(userInput), 0);
        }
    }
}
