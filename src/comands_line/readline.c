/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/15 18:36:55 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "readline.h"

void	start_shell()
{
	char	*line;

	server();
	while (1)
	{
		line = readline("hello how dead ?:");
		if(line == NULL)
			break;
		ft_printf("%s\n",line);
		add_history(line);
		free(line);
	}
}
