#pragma once
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <fcntl.h>
namespace stmotion_controller
{
namespace udp
{
class UDP_Socket
{
    public:
        typedef std::shared_ptr<UDP_Socket> Ptr;
        typedef std::shared_ptr<UDP_Socket const> ConstPtr;

    public:
        UDP_Socket()
        {
        }
        ~UDP_Socket()
        {
        }

        void Setup(const std::string& IP_addr, unsigned short port, unsigned int timeout_us)  
        {
            try{
                if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
                { 
                    perror("UDP socket creation failed!"); 
                    exit(EXIT_FAILURE);
                } 
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(IP_addr.c_str());
                addr.sin_port = htons(port);
                
                tv.tv_sec = 0;
                tv.tv_usec = timeout_us;

                addr_len = sizeof(addr);
            }
            catch(...){
                close(sockfd);
                exit(EXIT_FAILURE);
            }
        }
        
        void ServerSetup(unsigned short port)  
        {
            try{
                if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
                { 
                    perror("UDP socket creation failed!"); 
                    exit(EXIT_FAILURE);
                } 

                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = htonl(INADDR_ANY);
                addr.sin_port = htons(port);
                
                tv.tv_sec = 0;
                tv.tv_usec = 1;

                addr_len = sizeof(addr);

                if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
                {
                    perror("bind");
                    close(sockfd);
                }
            }
            catch(...){
                close(sockfd);
                exit(EXIT_FAILURE);
            }
        }

        void SendTo(const void* buffer, int len)
        {
            int ret = sendto(sockfd, buffer, len, 0, (sockaddr*)&addr, addr_len);
            if(ret < 0)
            {
                printf("UDP socket send failed!"); 
            }
        }

        void RecvFrom(void* buffer, int len)
        {
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            ssize_t recvlen = recvfrom(sockfd, buffer, len, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
            if (recvlen < 0)
            {
                printf("UDP socket recv failed!"); 
            }






        }

        void Close(){
            close(sockfd);
            close(sockfd_send);
        }

    private:
        int sockfd;
        int sockfd_send;
        sockaddr_in addr;
        sockaddr_in addr_send;
        struct timeval tv;
        socklen_t addr_len;
        socklen_t addr_send_len;
};
}
}