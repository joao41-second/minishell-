/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2025/02/03 20:40:33 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minis	start_minis(char **env)
{
	t_minis	mini;

	mini.line = NULL;
	mini.env = env_split(env);
	mini.env_org = env_split(env);
	mini.readline = 0;
	mini.comand = 0;
	mini.exit_code_error = 0;
	mini.pid = 0;
	mini.pips[0] = -1;
	mini.pips[1] = -1;
	return (mini);
}

int	main(int ac, char **av, char **env)
{
	t_minis	mini;

	(void)ac;
	(void)av;
	start_alloc();
	mini = start_minis(env);
	and_shelvl(&mini);
	start_shell(mini);
	ft_free_all(NULL);
	return (get_signal(0));
}
