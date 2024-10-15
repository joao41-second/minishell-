/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:12:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/10/15 15:19:24 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void func_test ()
{
	char *testo = ft_malloc(3456 * sizeof(int), NULL);
}

int main()
{
	t_list_ * ok;
	ok = ft_node_new(malloc(sizeof(1))); 
	ft_malloc(3,ok);
	ft_free_all(ok);
	ft_free(NULL,ok);
	start_shell();
}
