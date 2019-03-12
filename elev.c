#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
void solve(int nrid, int nst, int *dests);
int fw(int min,int max,int nrid,int *dests);
int minimum(int a,int b);
//int fw_inf(int min,int nrid,int *dests);
//int minimum_k(int a,int b);

//int counter_k=0;

int main(void)
{
	int i,j,nrid,nst,nfl,*dests;
	
	scanf("%d %d\n",&nrid,&nst);
	
	//printf("%d %d\n",nrid,nst);
	
	//Allocate the 1-D array of pointers
    dests = malloc(nrid * sizeof(int));
    
    
    for(i=0;i<nrid;i++)
    {
    	scanf("%d",&dests[i]);
	}
	
	/*
	for(i=0;i<nrid;i++)
    {
    	printf("%d ",dests[i]);
	}
	*/
	solve(nrid,nst,dests);
	
	return 0;
}

void solve(int nrid, int nst, int *dests) /* Recursive */
{ 
    int i,j,k,nfl=-1, **M ,cost,**p,min=1000,laststop;
    for(i=0;i<nrid;i++)
    {
    	if(dests[i]>nfl)
    		nfl=dests[i];
	}
	printf("nfl : %d\n",nfl);
	
	
	// Allocate the 1-D array of pointers
    M = malloc(nfl * sizeof(int *));
    
    // Allocate each row of the array
    for (i = 0;  i <= nfl;  i++)
    {
        // Allocate a row of ints for the array
        M[i] = malloc(nst * sizeof(int));

    }
    
    // Allocate the 1-D array of pointers
    p = malloc(nfl * sizeof(int *));
    
    // Allocate each row of the array
    for (i = 0;  i <= nfl;  i++)
    {
        // Allocate a row of ints for the array
        p[i] = malloc(nst * sizeof(int));
    }
	
	/*
	printf("%d\n",fw(5,12,nrid,dests));
	printf("%d",fw_inf(0,nrid,dests));
	*/
	
	for(i=0;i<=nfl;i++)
	{
		for(j=0;j<=nst;j++)
		{
			if(j==0)
			{
				M[i][0]=fw(0,INF,nrid,dests);
				p[i][0]=0;
			}
			else
			{
				M[i][j]=INF;
				for(k=0;k<=i;k++)
				{
					cost=M[k][j-1]-fw(k,INF,nrid,dests)+fw(k,i,nrid,dests)+fw(i,INF,nrid,dests);
					if(cost<M[i][j])
					{
						M[i][j]=cost;
						p[i][j]=k;
					}
				}
			}
		}
	}
	
	for(j=0;j<=nst;j++)
	{
		for(i=0;i<=nfl;i++)
		{
			printf("%3d ",M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	for(i=0;i<=nfl;i++)
	{
		for(j=0;j<=nst;j++)
		{
			printf("%3d ",p[i][j]);
		}
		printf("\n");
	}
	
	for(j=0;j<=nst;j++)
	{
		for(i=0;i<=nfl;i++)
		{
			if(M[i][j]<min)
			{
				min=M[i][j];
			}
		}
	}
	
	laststop=0;
	for(i=0;i<nfl;i++)
	{
		if(M[i][nst]<M[laststop][nst])
			laststop=i;
	}
	printf("cost : %d \n",min);
	printf("last stop : %d \n",laststop);
	
	printf("Elevator stops are : ");
	for(j=2;j<nst;j++)
	{
		printf("%d ",p[laststop+1][j]);
	}
	printf("%d\n",laststop);
}

int fw(int min,int max,int nrid,int *dests)
{
	int i,steps_walked=0;

	for(i=0;i<nrid;i++)
	{
		if(dests[i]>=min && dests[i]<=max)
		{
			steps_walked+=minimum(abs(dests[i]-min),abs(dests[i]-max));
		}
	}
	
	return steps_walked;
}


int minimum(int a,int b)
{
	if(a<b)
		return a;
	else if(b<a)
	{
		return b;
	}
}

