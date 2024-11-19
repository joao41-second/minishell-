/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:59:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/15 16:15:47 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	
#include "../../minishell.h"

int ft_lenchar(char *str, char cha)
{
	int i;
	
	i = -1;
	while(str[++i] != '\0')
		if(str[i] == cha)
			break;
	return (i);
}

char *rmenv(char *str,t_minis *mini, int *len)
{
	char	*ok;
	char	*env;
	int i;
	
(void)mini;	
	i = 0;
	if(str[0] == '$')
	{
		while(str[++i] != '\0')
		{
			if(str[i] == ' ' || str[i] == '"' || str[i] == 39)
				break ;
		}
		env = ft_substr(str,1, --i);
		if(ft_getenv(mini,env) == NULL)
			return (NULL);
		ok = ft_strjoin("", ft_getenv(mini,env));
		*len = ft_strlen(env) +1;
		(void)len;
		ft_free(env, NULL);
		return (ok);
	}
	return ("");
}

char	*creat_new( char verifc, char *str, t_quotes quotes, t_minis *mini,int i)
{
	static char	*temp = NULL;
	static int not_print;
	char *save;
	if(not_print > 0)
	{
		not_print--;
	}
	if(verifc == '\0')
	{
		not_print = 0;
		ft_free(temp,NULL);
		temp = NULL;
		return (NULL);
	}
	if(not_print == 0)
	{
			if(temp == NULL)
			temp = ft_strjoin("","");
		if( verifc == '"' && quotes.simp == 1 && i > quotes.simp_size)
			temp = ft_strjoin(temp, &verifc);
		if( verifc == 39  && quotes.dub == 1 && i > quotes.dub_size)
			temp = ft_strjoin(temp, &verifc);
		if( (verifc == '$' && quotes.dub == 1 && i > quotes.dub_size)  || (verifc == '$' && quotes.dub == 0 && quotes.simp == 0 ))
		{
			save = rmenv(&str[ft_lenchar(str,'$')],mini,&not_print);
			if(save == NULL)
			{
				not_print = INT_MAX;
				ft_free(temp,NULL);
				temp = NULL;
				return (NULL);
			}
			temp = ft_strjoin(temp, save);		
			return (temp);
		}
		if (verifc != '"' && verifc != 39)
			temp = ft_strjoin(temp, &verifc);
	}
		return (temp); 
}

char *expand_env(char *str, t_minis *mini)
{
	int i;
	t_quotes quotes;
	 char *end;

	end = "";
	(void)mini;
	i = -1;
	quotes.flags[0] = 0;
	quotes.flags[1] = 0;
	quotes.flags[2] = 0;
	quotes.flags[3] = 0;
	
	end = creat_new('\0', str, quotes,mini,i);
	while (str[++i] != '\0')
	{
		if(str[i] == 39)
		{
			quotes.simp++;
			quotes.simp_size = i;
		}
		if(str[i] == '"')
		{
			quotes.dub++;
			quotes.dub_size = i;
		}
		if(quotes.simp > 1)
		{
			quotes.simp = 0;
			quotes.simp_size = 0;
		}
		if(quotes.dub > 1)
		{
			quotes.dub = 0;
			quotes.dub_size = 0;
		}
		end = creat_new(str[i], &str[i], quotes,mini,i);
	}
	return (end);
}
