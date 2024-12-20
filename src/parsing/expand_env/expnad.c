/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:59:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/03 09:51:12 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

void	set_quotes(t_quotes *quotes, char *str, int i)
{
	if (str[i] == 39)
	{
		quotes->simp++;
		quotes->simp_size = i;
	}
	if (str[i] == '"')
	{
		quotes->dub++;
		quotes->dub_size = i;
	}
	if (quotes->simp > 1)
	{
		quotes->simp = 0;
		quotes->simp_size = i;
	}
	if (quotes->dub > 1)
	{
		quotes->dub = 0;
		quotes->dub_size = i;
	}
}

char	*expand_env(char *str, t_minis *mini)
{
	int			i;
	t_quotes	quotes;
	char		*end;

	end = "";
	(void)mini;
	i = -1;
	quotes.flags[0] = 0;
	quotes.flags[1] = 0;
	quotes.flags[2] = 0;
	quotes.flags[3] = 0;
	end = creat_new(0, "\0", &quotes, mini);
	while (str[++i] != '\0')
	{
		set_quotes(&quotes, str, i);
		end = creat_new(i, str, &quotes, mini);
		if (end == NULL)
			return (NULL);
	}
	return (end);
}


