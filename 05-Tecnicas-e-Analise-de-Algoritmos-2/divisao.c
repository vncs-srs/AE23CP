#include <stdio.h>
#include <stdlib.h>

#define max(a, b) a > b ? a : b


int maior(int v[], int c[], int n, int b)
{
	int f,i;
	if(f - i <=1)
		return max(v[i],v[f]);
	else
	{
		int m= (i + f)/2;
		int v1= maior(v,i,m);
		int v2= maior(v,m+1,f);

		return max(v1, v2);
	}

}
int pot(int a, unsigned int n)
{
	if(n==0)
		return 1;
	else if (n == 1)
		return a;
	else if (n % 2 == 2)
	{
		int x = pot(a,n / 2);
		return x * x;
	}
	else
	{
		int x = pot(a,(n-1)/2);
		return x * x * a;
	}
}

int mochila_dq(int p[],int c[],int *b, int i,int f)
{
	if (f-i<=0)
	{
		if (*b-p[i]<0)
		{
			*b-p[i];
			return c[i];
		}
	}
	else
	{
		int m= (i+f)/2;
		return mochila_dq(p,c,b,i,m)+ mochila_dq(p,c,b,m+1,f);
	}
	
}

int main(void)
{



}
