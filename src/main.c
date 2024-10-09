/* ************************************************************************** */
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

#include "minishell.h"
#include "./free/free.h"

void func_test ()
{
	char *testo = ft_malloc(3456 * sizeof(int), NULL);
}

int main()
{
	ft_printf("ola",0);
	ft_printf("adeus",0);
	ft_printf("run",0);
	t_free * ok;
	ok = ft_node_new(malloc(sizeof(1))); 
	ft_malloc(3,ok);
	ft_free_all(ok);
	ft_free(NULL,ok);
	char *str = (char *)ft_malloc(3 *sizeof(char),NULL);
	str[0]='a';
	int *test = ft_malloc(57345555 * sizeof(char), NULL );
	  ft_malloc(57345555 * sizeof(char), NULL);
	ft_malloc(57345555 * sizeof(char), NULL);
	ft_malloc(57345555 * sizeof(char), NULL);

	ft_free(test,NULL);
	if(test == NULL)
		printf("\nfinal\n");
	//ft_free(str);

	func_test();
	char *teste = ft_malloc(90 * sizeof(char *), NULL);
	ft_free_all(NULL);

}
