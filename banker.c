/* Author: Siddhant Saurabh
   version: 2.3
   Bugs: not started yet
*/
/*Reena’s operating system uses an algorithm for deadlock avoidance to
manage the allocation of resources say three namely A, B, and C to three
processes P0, P1, and P2. Consider the following scenario as reference
.user must enter the current state of system as given in this example :
Suppose P0 has 0,0,1 instances , P1 is having 3,2,0 instances and P2
occupies 2,1,1 instances of A,B,C resource respectively.
Also the maximum number of instances required for P0 is 8,4,3 and for p1
is 6,2,0 and finally for P2 there are 3,3,3 instances of resources A,B,C
respectively. There are 3 instances of resource A, 2 instances of resource B
and 2 instances of resource C available. Write a program to check whether
Reena’s operating system is in a safe state or not in the following
independent requests for additional resources in the
current state:
1. Request1: P0 requests 0 instances of A and 0 instances of B and 2
instances of C.
2. Request2: P1 requests for 2 instances of A, 0 instances of B and 0
instances of C.
All the request must be given by user as input.
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int allocated[100][100]={{0,0,1,2},{1,0,0,0},{1,3,5,4},{0,6,3,2},{0,0,1,4}};
int max_resource[100][100]={{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}};
int needed[100][100]={{0,0,0,0},{0,7,5,0},{1,0,0,2},{0,0,2,0},{0,6,4,2}};

int process_no=5;
int resource_no=4;

int available[100]={0};
int new_available[100]={0};

int sequence[100]={0};
int notinsequence[100]={0};
int notinsequenceno=0;
int old_notinsequenceno=0;

bool finish[100];

int request[100];

void enter()
{
	int i,j;
/*	//Entering the processes and their resources
	printf("Enter no. of processes: ");
	scanf("%d",&process_no);
	printf("Enter no. of resources: ");
	scanf("%d",&resource_no);
	
	//getting the allocation matrix
	printf("Enter all the details of a process seperated by space \n");
	for(i=0;i<process_no;i++)
	{
		printf("Enter allocated resources of P%d : ",i);
		for(j=0;j<resource_no;j++)
		{
			scanf("%d",&allocated[i][j]);
		}
		printf("Enter maximum resources of P%d   : ",i);
		for(j=0;j<resource_no;j++)
		{
			scanf("%d",&max_resource[i][j]);
			//checking if max>=allocated
			if(max_resource[i][j]<allocated[i][j])
			{
				printf("maximum resource required is less than allocated resource.\nError! \n");
				exit(0);
			}
			//calculating the need matrix
			needed[i][j]=max_resource[i][j]-allocated[i][j];
		}
	}
		
*/	printf("Printing needed resource matrix \n");
	for(i=0;i<process_no;i++)
	{
		for(j=0;j<resource_no;j++)
		{
			printf("%d %d %d      ",allocated[i][j],max_resource[i][j],needed[i][j]);
		}
		printf("\n");
	}
	
	printf("Enter the initial available system resources : ");
	for(i=0;i<resource_no;i++)
	{
		scanf("%d",&new_available[i]);
		available[i]=new_available[i];
	}
}

//for finding needed[i]<=new_available[i],
bool work(int i)
{
	printf("%d hey",i);
	int count=0;
	int j=0;
	for(j=0;j<resource_no;j++)
	{
		printf("x %d %d\n",needed[i][j],new_available[j]);
		if(needed[i][j]<=new_available[j])
		{
			count++;
		}
	}
			
	printf("count %d",count);
	
	if(count==resource_no)
		return true;
	else
		return false;
}

int no_of_finished()
{
	printf("hey inside finished fun");
	int count=0;
	int i=0;
	for(i=0;i<process_no;i++)
	{
		if (finish[i]==true)
		{
			printf("finshed true counted");
			count++;
		}
	}
	
	return count;
}

void bankers_algo()
{
	int i=0,j=0;
	
	int sequencecounter=0;
	notinsequenceno=0;
	old_notinsequenceno=0;
	for(i=0;i<process_no;i++)
	{
		sequence[i]=0;
		//notinsequence[i]=0;
		finish[i]=false;
	}
	
	
	
	//goto
	Redoing:
		for(i=0;i<process_no;i++)
		{
			//printf("%d  i value",i);
			bool nw=work(i);
			if(finish[i]==false  && nw==true)
			{
				for(j=0;j<resource_no;j++)
				{
					new_available[j]+=allocated[i][j];
				}
				finish[i]=true;
				printf("converted finish to true %d",finish[i]);
				sequence[sequencecounter++]=i;
			}
			else if(finish[i]==false && nw==false)
			{
				notinsequenceno++;
			}
		}
	printf("no_of_finished %d  nsn %d  onsn %d  sequence cntr %d",no_of_finished(),notinsequenceno,old_notinsequenceno,sequencecounter);
	if(no_of_finished()==process_no)
	{
		printf("Processes are in Safe State and one of the Safe sequence is : ");
		printf("< ");
		for(i=0;i<process_no;i++)
		{
			printf("%d ",sequence[i]);
		}
		printf(">\n");
	}
	else if(notinsequenceno!=old_notinsequenceno)
	{
		old_notinsequenceno=notinsequenceno;
		notinsequenceno=0;
		printf("inside banker algo \n");
		sleep(1);
		goto Redoing;
	}
	else if(notinsequenceno==old_notinsequenceno)
	{
		printf("No Safe sequence found.\nProcesses are in Unsafe State\n");
	}
}


void request_for_additional_resource()
{
	/*
	
	1.  If Requesti .Needi , go to step 2. Otherwise, raise an error condition, since
		the process has exceeded its maximum claim.
	2.  If Requesti . Available, go to step 3. Otherwise, Pi must wait, since the
		resources are not available.
	3.  Have the system pretend to have allocated the requested resources to
		process Pi by modifying the state as follows:
		Available = Available.Requesti ;
		Allocationi = Allocationi + Requesti ;
		Needi = Needi .Requesti ;
	
	*/
	char ch=NULL;
	int pn=0;
	int i=0,j=0,k=0;
	int flag=0;
	int flag2=0;
	int sequencecounter=0;
	
	int count=0;
	
	do
	{
		pn=0;
		i=0,j=0,k=0;
		flag=0;
		flag2=0;
		sequencecounter=0;
		count=0;
		for(i=0;i<resource_no;i++)
		{
			new_available[i]=available[i];
		}
		
		
		printf("Enter the Process no. for which additional resource you want to be before allocated extra : ");
		scanf("%d",&pn);
		
		printf("Enter all the extra allocation seperated by space \n");
		for(i=0;i<resource_no;i++)
		{
			scanf("%d",&request[i]);
			if(request[i]>needed[pn][i])
			{
				printf("Extra resources should not exceed more than the needed");
				exit(0);
			}
			if(request[i]>new_available[i])
			{
				flag=1;
			}
		}
		if (flag==0)
		{
			for(i=0;i<resource_no;i++)
			{
				allocated[pn][i]+=request[i];
				needed[pn][i]-=request[i];
				new_available[i]-=request[i];
			}
			bankers_algo();
			//for keeping the original data independent of the test case choosen in the request_for_additional_resource();
			for(i=0;i<resource_no;i++)
			{
				allocated[pn][i]-=request[i];
				needed[pn][i]+=request[i];
				new_available[i]+=request[i];
			}
		}
		
		
		if(flag==1)
		{
			printf("inside persistant flag");
			//persistant check
			notinsequenceno=0;
			old_notinsequenceno=0;
			for(i=0;i<process_no;i++)
			{
				sequence[i]=0;
				//notinsequence[i]=0;
				finish[i]=false;
			}
	
			//goto
			Redoing:
				for(i=0;i<process_no;i++)
				{
					//printf("%d  i value",i);
					bool nw=work(i);
					if(finish[i]==false  && nw==true && i!=pn)
					{
						for(j=0;j<resource_no;j++)
						{
							new_available[j]+=allocated[i][j];
							printf("%d ",new_available[j]);
						}
						printf("\n");
						finish[i]=true;
						printf("converted finish to true %d",finish[i]);
						sequence[sequencecounter++]=i;
						
						//checking & Updating
						if(flag2==0)
						{
							count=0;
							for(j=0;j<resource_no;j++)
							{
								if(request[j]<=new_available[j])
								{
									count++;
								}
							}
							if(count==resource_no)
							{
								flag2=1;
								for(k=0;k<resource_no;k++)
								{
									allocated[pn][k]+=request[k];
									needed[pn][k]-=request[k];
									new_available[k]-=request[k];
								}
								
								for(k=0;k<resource_no;k++)
								{
									new_available[k]+=allocated[pn][k];
								}
								finish[pn]=true;
								printf("converted finish to true %d",finish[pn]);
								sequence[sequencecounter++]=pn;
							}
						}
	
	
					}
					else if(finish[i]==false && nw==false)
					{
						notinsequenceno++;
					}
				}
			printf("no_of_finished %d  nsn %d  onsn %d  sequence cntr %d",no_of_finished(),notinsequenceno,old_notinsequenceno,sequencecounter);
			if(no_of_finished()==process_no)
			{
				printf("Processes are in Safe State and one of the Safe sequence is : ");
				printf("< ");
				for(i=0;i<process_no;i++)
				{
					printf("%d ",sequence[i]);
				}
				printf(">\n");
			}
			else if(notinsequenceno!=old_notinsequenceno)
			{
				old_notinsequenceno=notinsequenceno;
				notinsequenceno=0;
				printf("inside banker algo \n");
				sleep(1);
				goto Redoing;
			}
			else if(notinsequenceno==old_notinsequenceno)
			{
				printf("No Safe sequence found.\nProcesses are in Unsafe State\n");
			}
			
			for(i=0;i<resource_no;i++)
			{
				allocated[pn][i]-=request[i];
				needed[pn][i]+=request[i];
				new_available[i]+=request[i];
			}
		}
		
		printf("Enter Y/y if you want to check another case, else press N/n");
		ch=getch();
		printf("\n");
	}
	while(ch=='Y'||ch=='y');
}

int main()
{
	enter();
	bankers_algo();
	request_for_additional_resource();
}

