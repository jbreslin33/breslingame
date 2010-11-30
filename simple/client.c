#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>

#define BUFLEN 512
#define NPACK 10
#define PORT 9930

#define SRV_IP "10.42.43.1"

void diep(char *s)
{
	perror(s);
        exit(1);
}
    
int main(void)
{
	struct sockaddr_in; //my socket (client)
	struct si_other;   //other socket (server)
	
        int s, i, slen=sizeof(si_other);
        char buf[BUFLEN];
    
        if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
	{
        	diep("socket");
    	}
        
	memset((char *) &si_other, 0, sizeof(si_other));
        si_other.sin_family = AF_INET;
        si_other.sin_port = htons(PORT);

        if (inet_aton(SRV_IP, &si_other.sin_addr)==0)
	{
        	fprintf(stderr, "inet_aton() failed\n");
          	exit(1);
        }
    
	//loop and send 9 packets to a server
        for (i=0; i<NPACK; i++)
	{
        	printf("Sending packet %d\n", i);  //just a printf to tell client what we are doing 
          	sprintf(buf, "This is packet %d\n", i); //actual message
          	if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, slen)==-1) //this sends message
		{
            		diep("sendto()");
		}
        }
    
        close(s); //close socket
        return 0; //return from main
      }

