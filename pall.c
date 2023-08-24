#include "monty.h"
/**
 * pall - print all values on stack
 * @stack: pointer to stack
 * @line_num: line number
 */
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_num)
{
	stack_t *curr = *stack;

	while (curr)
	{
		printf("%d\n", curr->n);
		curr = curr->next;
	}
}
