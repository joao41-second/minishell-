/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:44:30 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/11 09:52:13 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*creat_new_not(int i, char *str, t_quotes *quotes, t_minis *mini)
{
	static char	*temp = NULL;
	static int	not_print;
	char		verifc[2];

	(void)mini;
	verifc[0] = str[i];
	verifc[1] = '\0';
	if (if_verifc(verifc, &not_print, &temp) == TRUE)
		return (NULL);
	if (not_print > 0)
		not_print--;
	if (not_print == 0)
	{
		if (temp == NULL)
			temp = ft_strdup("");
		temp = concatenate_not_env(verifc, quotes, temp);
	}
	return (temp);
}

char	*expand_not_env(char *str, t_minis *mini)
{
	int			i;
	t_quotes	quotes;
	char		*end;

	end = "";
	(void)mini;
	i = -1;
	if (chek(str) != TRUE)
		return (ft_strdup(str));
	quotes.flags[0] = 0;
	quotes.flags[1] = 0;
	quotes.flags[2] = 0;
	quotes.flags[3] = 0;
	end = creat_new(0, "\0", &quotes, mini);
	while (str[++i] != '\0')
	{
		set_quotes(&quotes, str, i);
		end = creat_new_not(i, str, &quotes, mini);
		if (end == NULL)
			return (NULL);
	}
	return (end);
}
