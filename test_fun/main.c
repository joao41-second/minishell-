#include <stdio.h> #include <readline/readline.h> #include <readline/history.h>

int main(void)
{
	char *line;
	line =readline("oi: ");
	add_history(line);
	line =readline("oi: ");

	printf("%s\n",line);


}
