/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:52 by rpires-c          #+#    #+#             */
/*   Updated: 2024/11/29 14:52:22 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TOKENIZER_H
#ifdef TOKENIZER_H

typedef struct s_token
{
	char	*token;
	char	*type;
	char	*redirection_target;
	char	*redirection_source;
}	t_token;

#endif
