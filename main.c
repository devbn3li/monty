#include "monty.h"

global_t glob;

/**
 * main - interpreter for monty bytecode file
 * @ac: arg count
 * @av: arg vector
 *
 * Return: EXIT_SUCCESS on success & EXIT_FAILURE on error
 */
int main(int ac, char **av)
{
	init_global();

	if (ac != 2)
		exit_with_ferror("USAGE: monty file\n");

	glob.file = fopen(av[1], "r");

	if (!(glob.file))
		exit_with_ferror("Error: Can't open file %s\n", av[1]);

	interpret();

	fclose(glob.file);

	return (EXIT_SUCCESS);
}

/**
* init_global - init glob var
*/
void init_global(void)
{
	glob.file = NULL;
	glob.line = NULL;
	glob.n = 0;
	glob.tokens = NULL;
	glob.stack = NULL;
	glob.queue_mode = false;
}

/**
 * interpret - interpreter a monty bytecode file
 */
void interpret(void)
{
	unsigned int line_num = 0;

	while (getline(&(glob.line), &(glob.n), glob.file) != -1)
	{
		void (*f)(stack_t **stack, unsigned int line_num) = NULL;

		line_num++;
		line_split(glob.line, " \t\n");

		if (glob.tokens[0] && glob.tokens[0][0] != '#')
		{
			f = *find_instruction();

			if (f)
				f(&(glob.stack), line_num);
			else
				exit_with_ferror("L%d: unknown instruction %s\n",
						line_num,
						glob.tokens[0]);
		}

		free(glob.line);
		glob.line = NULL;
		free(glob.tokens);
		glob.tokens = NULL;
	}

	free(glob.line);
	free_stack(&(glob.stack));
}
