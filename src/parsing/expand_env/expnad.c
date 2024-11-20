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
#include <stdio.h>
#include <sys/types.h>

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

int ft_if_expand(char *verifc, t_quotes *quotes, int i)
{
	(void)i;
	if((verifc[0] == '$' && verifc[0] == '$' && quotes->dub == 0 && quotes->simp == 0 ))
		return (TRUE);
	if(verifc[0] == '$' && quotes->dub == 1 && quotes->simp == 1 && quotes->dub > quotes->simp )
		return TRUE;
	return (FALSE);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char *save;
	char *aloc;
	save = ft_strdup(s1);
	ft_free(s1,NULL);
	aloc = ft_strjoin(save, s2);
	ft_free(save,NULL);
	return (aloc);
}


char	*creat_new( int i, char *str, t_quotes *quotes,  t_minis *mini)
{
	static char	*temp = NULL;
	static int not_print;
	char *save;
	char verifc[2];

	verifc[0] = str[i];
	verifc[1] = '\0';
	if(not_print > 0)
	{
		not_print--;
	}
	if(verifc[0] == '\0')
	{
		not_print = 0;
		ft_free(temp,NULL);
		temp = NULL;
		return (NULL);
	}

	if(not_print == 0)
	{
		
		printf("aspas %c = %d index = %d  '= %d index = %d \n",'"',	quotes->dub,quotes->dub_size,quotes->simp,quotes->simp_size);
		printf("%s %d\n",verifc,i);
		if(temp == NULL)
			temp = ft_strdup("");

		if(verifc[0] == '"' || verifc[0] == 39)
		{ 
			if(quotes->simp == 1 && quotes->dub == 1)
			{
				
				temp  = ft_strjoin_and_free(temp,verifc);
				if(verifc[0] == '"' )
					quotes->dub++;
				if(verifc[0] == 39 )
					quotes->simp++;

			}

		}
	

		if(ft_if_expand(verifc,quotes,i) == TRUE)
		{
			save = rmenv(&str[i],mini,&not_print);
			if(save == NULL)
			{
				not_print = INT_MAX;
				ft_free(temp,NULL);
				temp = NULL;
				return (NULL);
			}
			temp = ft_strjoin(temp, save);
			ft_free(save,NULL);
			return (temp);
		}
		if (verifc[0] != '"' && verifc[0] != 39)
		{
			temp  = ft_strjoin_and_free(temp,verifc);
		}
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
	
	end = creat_new(0, "\0", &quotes,mini);
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
			quotes.simp_size = i;
		}
		if(quotes.dub > 1)
		{
			quotes.dub = 0;
			quotes.dub_size = i; 
		}
	//	ft_free(end,NULL);

		end = creat_new(i, str, &quotes,mini);
		if(end == NULL)
			return (NULL); 
	}
	return (end);
}
