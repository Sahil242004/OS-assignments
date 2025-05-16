#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

int do_parent(int a[], int sz)
{
	int add=0, i;
	for (i=0; i<sz; i++)
		add += a[i];

	return add;
}

int do_child(int a[], int sz)
{
	int mult=1;
	int i;
	for (i=0; i<sz; i++)
		mult *= a[i];

	return mult;
}

int main()
{
	pid_t x;
	int a[50], sz, i;

	printf("Enter the size of array\n");
	scanf("%d", &sz);

	printf("Enter array elements\n");
	for (i=0; i<sz; i++)
		scanf("%d", &a[i]);

	x = fork();

	if (x==0)
	{
		int m;
		m = do_child(a, sz);
		printf("mutiplication=%d\n", m);
	}
	else
	{
		int s;
		s = do_parent(a, sz);
		printf("addition=%d\n", s);
	}

	return 0;
}
