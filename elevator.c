#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solve(int nrid, int nst, int *dests);
int fw(int min,int max,int nrid,int *dests);
int minimum(int a,int b);
int fw_inf(int min,int nrid,int *dests);
int minimum_k(int a,int b);

int counter_k=0;

int main(void)
{
	int i,j,nrid,nst,nfl,*dests,*stops,counter=0;
	
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
    int i,j,k,nfl=-1, **M ,temp=10000,min=10000,**k_m;
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
    k_m = malloc(nfl * sizeof(int *));
    
    // Allocate each row of the array
    for (i = 0;  i <= nfl;  i++)
    {
        // Allocate a row of ints for the array
        k_m[i] = malloc(nst * sizeof(int));
    }
	
	for(i=0;i<=nfl;i++)
	{
		for(j=0;j<=nst;j++)
		{
			k_m[i][j]=0;
		}
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
				M[i][0]=fw_inf(0,nrid,dests);
			}
			else
			{
				for(k=0;k<=i;k++)
				{
					M[i][j]=minimum_k(temp,M[k][j-1]-fw_inf(k,nrid,dests)+fw(k,i,nrid,dests)+fw_inf(i,nrid,dests));
					temp=M[i][j];
				}
				k_m[i][j]=counter_k;
				counter_k=0;
				temp=10000;
			}
			//counter_k=0;
		}
	//	counter_k=0;
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
	
	for(j=0;j<=nst;j++)
	{
		for(i=0;i<=nfl;i++)
		{
			printf("%3d ",k_m[i][j]);
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
	printf("cost : %d ",min);
}

int fw(int min,int max,int nrid,int *dests)
{
	int i,mincost_in_range=0;

	for(i=0;i<nrid;i++)
	{
		if(dests[i]>=min && dests[i]<=max)
		{
			mincost_in_range+=minimum(abs(dests[i]-min),abs(dests[i]-max));
		}
	}
	
	return mincost_in_range;
}

int fw_inf(int min,int nrid,int *dests)
{
	int i,mincost_in_range=0;

	for(i=0;i<nrid;i++)
	{
		if(dests[i]>=min)
		{
			mincost_in_range+=abs(dests[i]-min);
		}
	}
	
	return mincost_in_range;
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

int minimum_k(int a,int b)
{
	if(a<b)
		return a;
	else if(b<a)
	{
		counter_k++;
		return b;
	}
}
