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
#ifndef READLINE_H
#include "../minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
 
void start_shell();


#endif // !READLINE_H
