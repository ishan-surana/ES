#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
main()
{
int s,r,recb,sntb,x,ns,a=0;
printf("INPUT port number:- ");
scanf("%d",&x);
socklen_t len;
struct sockaddr_in server,client;
char buff[200];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("\nSocket creation error!");
exit(0);
}
printf("\nSocket created!");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nBinding error!");
exit(0);
}
printf("\nSocket binded!");
r=listen(s,1);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening...");
len=sizeof(client);
ns=accept(s,(struct sockaddr*)&client,&len);
if(ns==-1)
{
close(s);
exit(0);
}
printf("\nSocket accepting...");

recb=recv(ns,buff,sizeof(buff),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed!");
close(s);
close(ns);
exit(0);
}
printf("Message Recieved:- ");
printf("%s",buff);
getchar();
strcpy(buff,"Array received! Your options are:-\n1) Search\n2) Sort\n3) Split\n");
printf("\n");
sntb=send(ns,buff,sizeof(buff),0);
if(sntb==-1)
{
printf("\nMessage Sending Failed!");
close(s);
close(ns);
exit(0);
}

while(1)
{
recb=recv(ns,buff,sizeof(buff),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed!");
close(s);
close(ns);
exit(0);
}
printf("Option selected:- ");
printf("%s",buff);
if(strcmp(buff,"stop")==0) break;
printf("\nSend Reply:- ");
if(strcmp(buff,"\n")==0) getchar();
gets(buff);
printf("\n");
sntb=send(ns,buff,sizeof(buff),0);
if(strcmp(buff,"stop")==0) break;
if(sntb==-1)
{
printf("\nMessage Sending Failed!");
close(s);
close(ns);
exit(0);
}
}
close(ns);
close(s);
}
