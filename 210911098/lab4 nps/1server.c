
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

struct Student{
	char student_id[15];
	char subject_id[3][10];
	char fname[15];
	char lname[15];
	char marks[3][3];
	char add[10];
	char dep[10];
	char sem[10];
	char section[5];
};
struct subjects{
char subject_id[15];
char subject_name[15];
};

int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[200];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(3388);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.");

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.");
	struct Student stu[2];
	struct subjects sub[3];

	strcpy(stu[0].student_id, "210911310");
	strcpy(stu[1].student_id, "210911330");
	strcpy(stu[0].sem, "5");
	strcpy(stu[1].sem, "3");
	strcpy(stu[0].section, "C");
	strcpy(stu[1].section, "C");
	strcpy(stu[0].subject_id[0], "SUBJ1");
	strcpy(stu[0].subject_id[1], "SUBJ2");
	strcpy(stu[0].subject_id[2], "SUBJ3");
	strcpy(stu[1].subject_id[0], "SUBJ4");
	strcpy(stu[1].subject_id[1], "SUBJ5");
	strcpy(stu[1].subject_id[2], "SUBJ6");
	strcpy(stu[0].fname, "John");
	strcpy(stu[1].fname, "Jane");
	strcpy(stu[0].lname, "Doe");
	strcpy(stu[1].lname, "Smith");
	strcpy(stu[0].marks[0], "85");
	strcpy(stu[0].marks[1], "75");
	strcpy(stu[0].marks[2], "88");
	strcpy(stu[1].marks[0], "77");
	strcpy(stu[1].marks[1], "84");
	strcpy(stu[1].marks[2], "86");
	strcpy(stu[0].add, "Address1");
	strcpy(stu[1].add, "Address2");
	strcpy(stu[0].dep, "Department1");
	strcpy(stu[1].dep, "Department2");
	strcpy(sub[0].subject_id, "SUBJ1");
	strcpy(sub[1].subject_id, "SUBJ2");
	strcpy(sub[2].subject_id, "SUBJ3");
	strcpy(sub[0].subject_name, "Subject1");
	strcpy(sub[1].subject_name, "Subject2");
	strcpy(sub[2].subject_name, "Subject3");

	char PID[5];
	while(1)
	{
	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");
		close(s);
		close(ns);
		exit(0);
	}
	int n,i=0,j=0;
	char temp[50];
	int ch=buff[0];
	n=buff[1];
	for(i=0;i<n;i++)
	{
		temp[j]=buff[i+2];
		j++;
	}
	temp[j]='\0';
	if(ch==4)
		break;
	int pid=fork();
	if(pid==0)
	{
		if(ch==1)
		{
			if(strcmp(stu[0].student_id,temp)==0)
			{
				strcpy(buff,"");
				strcpy(buff,"Name of student is: ");
				strcat(buff,stu[0].fname);
				strcat(buff," ");
				strcat(buff,stu[0].lname);
				strcat(buff," ");
				//strcpy(buff,"Address : ");
				strcat(buff,stu[0].add);
				strcat(buff," ");
				strcat(buff,stu[0].sem);
				strcat(buff," ");
				strcat(buff,stu[0].section);
				strcat(buff," \nPID is: ");
				sprintf(PID, "%d", getpid());
				strcat(buff,PID);
			}
			else if(strcmp(stu[1].student_id,temp)==0)
			{
				strcpy(buff,"");
				strcpy(buff,"Name of student is: ");
				strcat(buff,stu[1].fname);
				strcat(buff," ");
				strcat(buff,stu[1].lname);
				strcat(buff," ");
				//strcpy(buff,"Address : ");
				strcat(buff,stu[1].add);
				strcat(buff," ");

				strcat(buff," \nPID is: ");
				sprintf(PID, "%d", getpid());
				strcat(buff,PID);
			}
			else
			{
				strcpy(buff,"");
				strcpy(buff,"INCORRECT INPUT\n");
			}


	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
		}
		else
		{
			int p=fork();
			if(p==0)
			{
				//child 2 and ch=2
				if(ch==2)
				{
					if(strcmp(stu[0].fname,temp)==0)
					{
						strcpy(buff,"");
						strcpy(buff,"Dept sem section courses: \n");
						strcat(buff,stu[0].dep);
						strcat(buff," ");
						strcat(buff,stu[0].sem);
						strcat(buff,stu[0].section);
						strcat(buff," ");
						strcat(buff,stu[0].subject_id[0]);
						strcat(buff," ");
						strcat(buff,stu[0].subject_id[1]);
						strcat(buff," ");
						strcat(buff,stu[0].subject_id[2]);
						strcat(buff," ");
						strcat(buff,stu[0].sem);
						strcat(buff," ");
						strcat(buff,stu[0].section);
						strcat(buff," \nPID is: ");
						sprintf(PID, "%d", getpid());
						strcat(buff,PID);

					}
					else if(strcmp(stu[1].fname,temp)==0)
					{
						strcpy(buff,"");
						strcpy(buff,"Dept sem section courses: \n");
						strcat(buff,stu[1].dep);
						strcat(buff," ");
						strcat(buff,stu[1].sem);
						strcat(buff,stu[1].section);
						strcat(buff," ");
						strcat(buff,stu[1].subject_id[0]);
						strcat(buff," ");
						strcat(buff,stu[1].subject_id[1]);
						strcat(buff," ");
						strcat(buff,stu[1].subject_id[2]);
						strcat(buff," ");
						strcat(buff,stu[1].sem);
						strcat(buff," ");
						strcat(buff,stu[1].section);
						strcat(buff," \nPID is: ");
						sprintf(PID, "%d", getpid());
						strcat(buff,PID);
					}
					else
					{
						strcpy(buff,"");
						strcpy(buff,"INCORRECT INPUT\n");
					}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
				}
				else
				{
					int pd=fork();
					if(pd==0)
					{
						//child 3 and ch=3
						if(strcmp(stu[0].subject_id[0],temp)==0)
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: \n");
							strcat(buff,stu[0].fname);
							strcat(buff,": ");
							strcat(buff,stu[0].marks[0]);
							strcat(buff,"\n");
							strcat(buff,stu[1].fname);
							strcat(buff,": ");
							strcat(buff,stu[1].marks[0]);
							strcat(buff," \nPID is: ");
							sprintf(PID, "%d", getpid());
							strcat(buff,PID);
						}
						else if(strcmp(stu[0].subject_id[1],temp)==0)
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: \n");
							strcat(buff,stu[0].fname);
							strcat(buff,": ");
							strcat(buff,stu[0].marks[1]);
							strcat(buff,"\n");
							strcat(buff,stu[1].fname);
							strcat(buff,": ");
							strcat(buff,stu[1].marks[1]);
							strcat(buff," \nPID is: ");
							sprintf(PID, "%d", getpid());
							strcat(buff,PID);
						}
						else if(strcmp(stu[0].subject_id[2],temp)==0)
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: \n");
							strcat(buff,stu[0].fname);
							strcat(buff,": ");
							strcat(buff,stu[0].marks[2]);
							strcat(buff,"\n");
							strcat(buff,stu[1].fname);
							strcat(buff,": ");
							strcat(buff,stu[1].marks[2]);
							strcat(buff," \nPID is: ");
							sprintf(PID, "%d", getpid());
							strcat(buff,PID);
						}
						else
						{
							strcpy(buff,"");
							strcpy(buff,"INCORRECT INPUT\n");
						}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
						exit(0);
					}

				}
				exit(0);
			}
		}
	exit(0);
	}
}

	close(ns);
	close(s);
}
