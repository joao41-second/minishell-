/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:28:34 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/15 17:29:54 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EXPAND_H
#ifdef EXPAND_H

typedef union s_quotes 
{
	struct {
	int simp;
	int simp_size;
	int dub;
	int dub_size;
	};
		int flags[4];
	char *end;
}			t_quotes;


char *expand_env(char *str, t_minis *mini);


char	*ft_strjoin_and_free(char *s1, char *s2);

char *concatenate_the_str_with_env_var(char *str,t_minis *mini, int *len);

#endif // !EXPAND_H
