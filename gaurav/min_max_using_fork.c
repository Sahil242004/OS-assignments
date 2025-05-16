#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<stdio.h>

int do_parent(int a[], int sz)
{
	int max;
	int i;
	max = a[0];
	for (i=1; i<sz; i++)
	{
		if (max<a[i])
			max = a[i];
	}

	return max;
}

int do_child(int a[], int sz)
{
	int min, i;
	min = a[0];
	for (i=1; i<sz; i++)
	{
		if (min>a[i])
			min = a[i];
	}

	return min;
}

int main()
{
	pid_t x;
	int a[50];
	int i, sz;
	int min, max;

	printf("Enter the size of the array\n");
	scanf("%d", &sz);
	
	printf("Enter array elements\n");
        for (i=0; i<sz; i++)
                scanf("%d", &a[i]);
	

	x = fork();
	if (x==0)
	{
		/*Child Process*/
		min = do_child(a, sz);
		printf("minimum array element = %d\n", min);
	}
	else
	{
		/*Parent Process*/
		wait(NULL);
		max = do_parent(a, sz);
		printf("maximum array element = %d\n", max);
	}

	return 0;
}
