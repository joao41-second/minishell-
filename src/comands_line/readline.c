#include "readline.h"



void start_shell()
{
	char *line;
	
	while (1)
	{
		line = readline("hello how dead ?:");
		//if(line == NULL)
			//	break;
		add_history(line);
		free(line);
	}
}
