#include<stdio.h>
int main()
{
	char ch[26];
	char num[5]; 
	int n=2019,m,i,j=0;
	for(i=0;i<26;i++)
	{
		ch[i]='A'+i;
	}
	while(n>0)
	{
		m=n%26-1;
		num[j]=ch[m];
		n=n/26;
		j++;
	}
	for(i=j-1;i>=0;i--)
	{
		printf("%c",num[i]);
	}
	return 0;
}
