/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:15 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/17 14:50:04 by rpires-c         ###   ########.fr       */
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
//ola mundo
void	start_shell(void);
void	server(void);
char	*get_shell_prefix(void);
char	*ft_strndup(const char *src, size_t n);

#endif // !READLINE_H
