/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:15 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/17 16:12:42 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define READLINE_H
#ifdef READLINE_H
//#include "../minishell.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

/**
* @brief get input from the user
*/
void	start_shell(void);
/**
* @brief deals with the signals
*/
void	server(void);
/**
* @brief gets command line prefix from env
* @return command line prefix almost like shell
*/
char	*get_shell_prefix(void);
/**
* @brief duplicates part of a stirngs
* @param src string to duplicate
* @param n number of bytes to duplicate
* @return part of the original string as a separate string
*/
char	*ft_strndup(const char *src, size_t n);

#endif // !READLINE_H
