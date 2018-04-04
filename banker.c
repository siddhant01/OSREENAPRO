/* Author: Siddhant Saurabh
   version: 2.6
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

//have take the default values of the question
int allocated[100][100]={{0,0,1,2},{1,0,0,0},{1,3,5,4},{0,6,3,2},{0,0,1,4}};//{{0,0,1},{3,2,0},{2,1,1}};
int max_resource[100][100]={{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}};//{{8,4,3},{6,2,0},{3,3,3}};
int needed[100][100]={{0,0,0,0},{0,7,5,0},{1,0,0,2},{0,0,2,0},{0,6,4,2}};//{{8,4,2},{3,0,0},{1,2,2}};

int process_no=5;//3;
int resource_no=4;//3;

int available[100]={1,5,2,0};//{3,2,2};
int new_available[100]={1,5,2,0};//{3,2,2};

int sequence[100]={0};
int notinsequence[100]={0};
int notinsequenceno=0;
int old_notinsequenceno=0;

bool finish[100];

int request[100];

void enter()
{
	printf("=============================================================================\n");
	int i,j;
	//Entering the processes and their resources
	printf("Enter no. of processes: ");
	scanf("%d",&process_no);
	printf("Enter no. of resources: ");
	scanf("%d",&resource_no);
	
	//getting the allocation matrix
	printf("\"Enter all the details of a process seperated by space\" \n");
	for(i=0;i<process_no;i++)
	{
		printf("Enter allocated resources of P%d : ",i);
		for(j=0;j<resource_no;j++)
			scanf("%d",&allocated[i][j]);
	}
	//getting the maximum resources required
	for(i=0;i<process_no;i++)
	{
		printf("Enter maximum resources of P%d   : ",i);
		for(j=0;j<resource_no;j++)
		{
			scanf("%d",&max_resource[i][j]);
			//checking if max>=allocated
			if(max_resource[i][j]<allocated[i][j])
			{
				printf("Maximum resource required is less than allocated resource.\nError! \n");
				exit(0);
			}
			//calculating the need matrix
			needed[i][j]=max_resource[i][j]-allocated[i][j];
		}
	}	
	
	//getting the available resources
	printf("Enter the initial available system resources : ");
	for(i=0;i<resource_no;i++)
	{
		scanf("%d",&new_available[i]);
		available[i]=new_available[i];
	}
}

//for printing
void print()
{
	printf("=============================================================================\n");
	int i,j;
	printf("Printing Allocated resource matrix \n");
	printf("    ");
	for(i=0;i<resource_no;i++)
		printf("%c  ",'A'+i);
	printf("\n");
	for(i=0;i<process_no;i++)
	{
		printf("P%d  ",i);
		for(j=0;j<resource_no;j++)
			printf("%d  ",allocated[i][j]);
		printf("\n");
	}
	
	printf("Printing Maximum resource matrix \n");
	printf("    ");
	for(i=0;i<resource_no;i++)
		printf("%c  ",'A'+i);
	printf("\n");
	for(i=0;i<process_no;i++)
	{
		printf("P%d  ",i);
		for(j=0;j<resource_no;j++)
			printf("%d  ",max_resource[i][j]);
		printf("\n");
	}
	
	printf("Printing Needed resource matrix \n");
	printf("    ");
	for(i=0;i<resource_no;i++)
		printf("%c  ",'A'+i);
	printf("\n");
	for(i=0;i<process_no;i++)
	{
		printf("P%d  ",i);
		for(j=0;j<resource_no;j++)
			printf("%d  ",needed[i][j]);
		printf("\n");
	}
	
	printf("Printing Available resources \n");
	for(i=0;i<resource_no;i++)
		printf("%c  ",'A'+i);
	printf("\n");
	for(i=0;i<resource_no;i++)
		printf("%d  ",available[i]);
	printf("\n");
	printf("=============================================================================\n");
}

//for finding needed[i]<=new_available[i],
bool work(int i)
{
	int count=0;
	int j=0;
	for(j=0;j<resource_no;j++)
		if(needed[i][j]<=new_available[j])
			count++;
	if(count==resource_no)
		return true;
	else
		return false;
}

//for counting no. of trues in the finish array
int no_of_finished()
{
	int count=0;
	int i=0;
	for(i=0;i<process_no;i++)
		if (finish[i]==true)
			count++;
	return count;
}

void bankers_algo()
{
	/*			Algorithum of Banker's Algorithum
	
	1.  LetWork and Finish be vectors of length m and n, respectively. Initialize
		Work = Available and Finish[i] = false for i = 0, 1, ..., n . 1.
	2.  Find an index i such that both
			a. Finish[i] == false
			b. Needi .Work
			If no such i exists, go to step 4.
	3.  Work =Work + Allocationi
		Finish[i] = true
		Go to step 2.
	4.  If Finish[i] == true for all i, then the system is in a safe state.
	
	*/	
	printf("Applying Bankers_algorithum... \n");
	int i=0,j=0;
	
	int sequencecounter=0;
	notinsequenceno=0;
	old_notinsequenceno=0;
	for(i=0;i<process_no;i++)
	{
		sequence[i]=0;
		finish[i]=false;
	}
	
	//goto
	Redoing:
		for(i=0;i<process_no;i++)
		{
			bool nw=work(i);
			if(finish[i]==false  && nw==true)
			{
				for(j=0;j<resource_no;j++)
					new_available[j]+=allocated[i][j];
				finish[i]=true;
				sequence[sequencecounter++]=i;
			}
			else if(finish[i]==false && nw==false)
				notinsequenceno++;
		}
	if(no_of_finished()==process_no)
	{
		printf("Processes are in Safe State and one of the Safe sequence is : ");
		printf("< ");
		for(i=0;i<process_no;i++)
			printf("P%d ",sequence[i]);
		printf(">\n");
	}
	else if(notinsequenceno!=old_notinsequenceno)
	{
		old_notinsequenceno=notinsequenceno;
		notinsequenceno=0;
		goto Redoing;
	}
	else if(notinsequenceno==old_notinsequenceno)
		printf("No Safe sequence found.\nProcesses are in Unsafe State\n");
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
	int pn;
	int i,j,k;
	int flag;
	int flag2;
	int sequencecounter;
	int count;
	
	do
	{
		printf("=============================================================================\n");
		pn=0;
		i=0,j=0,k=0;
		flag=0;
		flag2=0;
		sequencecounter=0;
		count=0;
		// reinitialling new_available to original availbale
		for(i=0;i<resource_no;i++)
			new_available[i]=available[i];
		
		//taking inputs for additional resources
		printf("Enter the Process no. for which you want to give extra additional resources : ");
		scanf("%d",&pn);
		if(pn > process_no)
		{
			printf("You have selected a wrong process\n");
			exit(0);
		}
		printf("\"Enter all the extra allocation seperated by space \"\n");
		printf("Additional resource for P%d is : ",pn);
		for(i=0;i<resource_no;i++)
		{
			scanf("%d",&request[i]);
			//for checking request<=need, else wrong
			if(request[i]>needed[pn][i])
			{
				printf("Extra resources should not exceed more than the needed\nError!");
				exit(0);
			}
			//for checking request<new_available, else waiting needs to be done
			if(request[i]>new_available[i])
				flag=1;
		}
		//for non waiting case
		if (flag==0)
		{
			//updating the allocated, needed matrix, and new_availbale 
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
			}
		}
		//for waiting case
		if(flag==1)
		{
			printf("Resources are not availbale righ now, but will be allocated as soon as they become free \n");
			//persistant checking is done here
			//most of the code is of bankers algorithum here
			notinsequenceno=0;
			old_notinsequenceno=0;
			for(i=0;i<process_no;i++)
			{
				sequence[i]=0;
				finish[i]=false;
			}
			
			printf("Applying Bankers_Algorithum...\n");
			//goto
			Redoing2:
				for(i=0;i<process_no;i++)
				{
					bool nw=work(i);
					if(finish[i]==false  && nw==true && i!=pn)
					{
						for(j=0;j<resource_no;j++)
							new_available[j]+=allocated[i][j];
						finish[i]=true;
						sequence[sequencecounter++]=i;
						
						//checking & Updating
						if(flag2==0)
						{
							count=0;
							for(j=0;j<resource_no;j++)
								if(request[j]<=new_available[j])
									count++;
							if(count==resource_no)
							{
								flag2=1;
								printf("Found available resources so now applying the new requirements of the resources...\n");
								//updating the allocated, needed matrix, and new_availbale 
								for(k=0;k<resource_no;k++)
								{
									allocated[pn][k]+=request[k];
									needed[pn][k]-=request[k];
									new_available[k]-=request[k];
								}
								
								for(k=0;k<resource_no;k++)
									new_available[k]+=allocated[pn][k];
								finish[pn]=true;
								sequence[sequencecounter++]=pn;
							}
						}
	
					}
					else if(finish[i]==false && nw==false)
						notinsequenceno++;
				}
			if(no_of_finished()==process_no)
			{
				printf("Processes are in Safe State and one of the Safe sequence is : ");
				printf("< ");
				for(i=0;i<process_no;i++)
					printf("P%d ",sequence[i]);
				printf(">\n");
			}
			else if(notinsequenceno!=old_notinsequenceno)
			{
				old_notinsequenceno=notinsequenceno;
				notinsequenceno=0;
				goto Redoing2;
			}
			else if(notinsequenceno==old_notinsequenceno)
				printf("No Safe sequence found.\nProcesses are in Unsafe State\n");
			//for keeping the original data independent of the test case choosen in the request_for_additional_resource();
			if(flag2==1)
				for(i=0;i<resource_no;i++)
				{
					allocated[pn][i]-=request[i];
					needed[pn][i]+=request[i];
				}
		}
		
		//for checking if user wants more test cases to be inputed
		printf("Enter Y/y if you want to check another case, else press N/n : ");
		ch=getche();
		printf("\n");
	}
	while(ch=='Y'||ch=='y');
}

int main()
{
	char ch;
	printf("Want to input your own case or you want to take the default case Y/y or N/n : ");
	ch=getche();
	printf("\n");
	if(ch=='Y' || ch=='y')
		enter();
	print();
	bankers_algo();
	request_for_additional_resource();
	return 0;
}
