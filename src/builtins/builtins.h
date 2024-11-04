/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:55:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/04 12:40:59 by jperpct          ###   ########.fr       */
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

t_list_ *list_env_i();


t_env* new_node(char *s1);
void free_env(void *point);
void ft_env(t_minis* mini);

char *ft_getenv(t_minis *mini ,char *var);

void* get_env_node(void *point ,void *locate);

void ft_cd(t_minis *mini);

void ft_pwd(t_minis *mini);

void ft_exit(t_minis *mini);

void ft_unset(t_minis *mini);

void ft_export(t_minis *mini);

void builtins(t_minis* mini);

void export_add( t_list_ **list, t_env *var);

t_env * list_to_env(t_list_ *list);



#endif // DEBUG
