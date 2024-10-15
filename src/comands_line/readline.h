/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:15 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/15 14:18:05 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define READLINE_H
#ifdef READLINE_H
#include "../minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>


 
void start_shell();

void	server();


#endif // !READLINE_H
