/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:28:34 by jperpct           #+#    #+#             */
/*   Updated: 2025/02/11 10:59:43 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EXPAND_H
#ifdef EXPAND_H

typedef union s_quotes
{
	struct
	{
		int	simp;
		int	simp_size;
		int	dub;
		int	dub_size;
	};
	int		flags[4];
	char	*end;
}			t_quotes;

/**
 * @brief the funcion expand env variabels in str
 *
 * @param str to env 
 * @param mini struct the minishell 
 * @return str env expand
 */
char		*expand_env(char *str, t_minis *mini);

/**
 * @brief strjoin usenig the free in s2
 *
 * @param s1 sting
 * @param s2 sring - is freed 
 * @return new str new memory alocad
 */
char		*ft_strjoin_and_free(char *s1, char *s2);

/**
 * @brief concatenate str with env expand
 *
 * @param str to concatenate
 * @param mini the struct the minishel 
 * @param len int char $ the str 
 * @return 
 */
char		*concatenate_the_str_with_env_var(char *str, t_minis *mini,
				int *len, t_quotes *quotes);

char		*creat_new(int i, char *str, t_quotes *quotes, t_minis *mini);

int			chek(char *line);

void		set_quotes(t_quotes *quotes, char *str, int i);

char		*concatenate_not_env( char *verifc, t_quotes *quotes, char *temp );

int			if_verifc(char *verifc, int *not_print, char **temp );

char		*expand_not_env(char *str, t_minis *mini);

#endif // !EXPAND_H
