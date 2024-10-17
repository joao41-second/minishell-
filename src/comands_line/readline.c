/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/16 15:15:29 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_shell()
{
	char	cwd[CWD_BUFFER];
	char	*line;
	char	*prompt;

	server();
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			prompt = ft_strjoin("~", cwd);
			prompt = ft_strjoin(prompt, "$ ");
			line = readline(prompt);
		}
        else
		{
            perror("getcwd() error");
            exit(1);
        }
		if(line == NULL)
			break;
		ft_printf("%s\n",line);
		add_history(line);
		free(line);
	}
}
