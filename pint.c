#include "monty.h"
/**
 * pint - print value at top of stack
 * @stack: ptr to stack
 * @line_num: line number
 */
void pint(stack_t **stack, unsigned int line_num)
{
	if (!(*stack))
		exit_with_ferror("L%d: can't pint, stack empty\n", line_num);

	printf("%d\n", (*stack)->n);
}
