#include <stdio.h>

/* IS NOT CORRECT */

int main()
{
	function;
	void(*print)(); // creates a function pointer called print with no arguments
	print = function(); // makes the pointer point to function
	print(); // since print points to fuction(), this will execute function()
}

void function ()
{
	printf("stuff");
}
