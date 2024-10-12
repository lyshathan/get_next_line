#include <stdio.h>

void function(int x)
{
	x++;
	printf("%d\n", x);
}

void	call_function(int x)
{
	function(x);
	function(x);
	function(x);
	printf("%d", x);
}

int main()
{
	static int x = 0;
	call_function(x);
	return 0;
}