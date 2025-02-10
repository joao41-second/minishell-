/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:42:43 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/10 16:05:43 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <sys/types.h>

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*save;
	char	*aloc;

	save = ft_strdup(s1);
	ft_free(s1, NULL);
	aloc = ft_strjoin(save, s2);
	ft_free(save, NULL);
	return (aloc);
}

char	*expnad_nex_while(char *env, t_minis *mini, int *len)
{
	char	*ok;

	ok = ft_strjoin("", ft_getenv(mini, env));
	*len = ft_strlen(env) + 1;
	ft_free(env, NULL);
	return (ok);
}

char	*concatenate_the_str_with_env_var(char *str,
									t_minis *mini, int *len, t_quotes *quotes)
{
	char	*env;
	int		i;

	i = 0;
	if (str[0] == '$' && !(str[1] == '\0' || str[1] == ' '
			|| str[1] == '"' || str[1] == 39 || str[1] == '$'))
	{
		while (str[++i] != '\0')
			if (str[i] == ' ' || str[i] == '"'
				|| str[i] == 39 || str[i] == '$' || str[i - 1] == '?')
				break ;
		env = ft_substr(str, 1, --i);
		return (expnad_nex_while(env, mini, len));
	}
	else if (str[1] == '\0' || str[1] == ' ' || str[1] == '"'
		|| str[1] == 39 || str[1] == '$' )
	{
		if (quotes != NULL && (quotes->dub == 1 || quotes->simp == 1))
			return ("$");
		if (str[0] == '$' && (str[1] != '"' && str[1] != 39))
			return ("$");
	}
	return ("");
}
