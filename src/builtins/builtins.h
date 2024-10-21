/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:55:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/21 16:10:53 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUILTINS_H
#ifdef BUILTINS_H

#include "../../libft/libft/libft.h"
#include "../../libft/Get_next_line/get_next_line_bonus.h"
#include "../../libft/printf/ft_printf.h"
typedef struct s_env {
	char* name;
	char* content;
} t_env;


/**
 * @brief save the env in linked list 
 * @param env file env the system
 * @return linked list
 */
t_list_ *env_split(char **env);

/**
 * @brief print the struct  t_env  
 * @param point t_env node 
 */
void print_env(void *point);

void free_env(void *point);

#endif // DEBUG
