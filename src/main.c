/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/15 19:34:43 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void func_test ()
{
	char *testo = ft_malloc(3456 * sizeof(int), NULL);
}

int main(int ac, char **av, char **env)
{
	t_list_ * ok;
	t_minis  mini;
	ok = ft_node_new(malloc(sizeof(1))); 
	ft_malloc(3,ok);
	ft_free_all(ok);
	ft_free(NULL,ok);
	mini.env = env_split(env);
	print_list(mini.env,print_env);	

	start_shell();
}
