/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:20:13 by jperpct           #+#    #+#             */
/*   Updated: 2024/12/02 13:42:17 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	not_join(int not, char join)
{
	if (join == '$' || join == ' ')
		not = 0;
	if (not > 0)
	{
		not--;
	}
	return (not);
}

static void	start_var_expand_heradoc(char **ret, char *set, char **temp)
{
	set[1] = '\0';
	*ret = ft_strdup("");
	*temp = ft_strdup("");
}

void	the_concatenate_and_free(char *temp, char *ret)
{
	ret = ft_strjoin_and_free(ret, temp);
	ft_free(temp, NULL);
}

char	*expand_heradoc(t_minis *mini, char *str)
{
	char	*ret;
	char	set[3];
	char	*temp;
	int		not_print;
	int		i;

	i = -1;
	not_print = 0;
	start_var_expand_heradoc(&ret, set, &temp);
	while (str[++i] != '\0')
	{
		set[0] = str[i];
		not_print = not_join(not_print, str[i]);
		if (not_print > 0)
			continue ;
		if (str[i] == '$')
		{
			temp = concatenate_the_str_with_env_var(&str[i], mini,
					&not_print, (t_quotes *) NULL);
			the_concatenate_and_free(temp, ret);
		}
		else
			ret = ft_strjoin_and_free(ret, set);
	}
	return (ret);
}
