/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:20:37 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/10 13:12:18 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include "minishell.h"
#include "./free/free.h"

void func_test ()
{
	char *testo = ft_malloc(3456 * sizeof(int), NULL);
}

int main()
{
	t_free * ok;
	ok = ft_node_new(malloc(sizeof(1))); 
	ft_malloc(3,ok);
	ft_free_all(ok);
	ft_free(NULL,ok);

}
