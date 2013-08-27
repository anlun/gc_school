#include <stdio.h>

register unsigned **ebp_reg asm("ebp");

void* func_address() {
	unsigned* caller_ebp = *(ebp_reg);
	unsigned* next_cmd   = caller_ebp[1];
	unsigned  offset     = *(next_cmd - 1);
	return (void *) ((unsigned) next_cmd + offset);
}

void print_stack_address() {
	unsigned* caller_ebp = *(ebp_reg);
	int count = 0;

	printf("PRINT STACK TRACE\n-----------------\n");
	while (caller_ebp != 0) {
		unsigned* next_cmd  = caller_ebp[1];
		unsigned  offset    = *(next_cmd - 1);

		void* func_address = (void*) ((unsigned) next_cmd + offset);
		printf("Func %d address: %p\n", count, func_address);

		caller_ebp = *caller_ebp;
		count++;
	}
	printf("-----------------\n\n");
}

void t() {
	printf("Print t stack:\n");
	print_stack_address();
}

void f() {
	printf("Print f stack:\n");
	print_stack_address();

	t();
}

void g() {
	printf("Print g stack:\n");
	print_stack_address();

	f();
}

int main() {
	printf("Print main stack:\n");
	print_stack_address();

	g();

	return 0;
}