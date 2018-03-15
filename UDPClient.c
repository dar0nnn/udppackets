#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <string>
#define BUFLEN 512
#define PORT 9930
 
void err(char *s)
{
    perror(s);
    exit(1);
}
 
int main()
{
    
    struct timespec nt;
    struct sockaddr_in serv_addr;
    int sockfd, slen=sizeof(serv_addr);
    
    std::string host="192.168.0.2";
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
        err("socket");
 
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    int i =0;

    if (inet_aton(host.c_str(), &serv_addr.sin_addr)==0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    while(1)
    {
	char buf[30];
	char nsec_buf[9];

	clock_gettime(CLOCK_REALTIME, &nt);
	sprintf(buf,"%d",(long)nt.tv_sec);
	strcat(buf,".");
	sprintf(nsec_buf,"%d",(long)nt.tv_nsec);
	strcat(buf,nsec_buf);

//	buf += i+' '+buffer; //TYT+ i + buf
//.c_str() buf.length()
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&serv_addr, slen)==-1)
            err("sendto()");
	i++;
//	buf = {0};
//	nsec_buf = {0};
	sleep(1);
    }
 
    close(sockfd);
    return 0;
}
