/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:09:15 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/31 18:30:31 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define READLINE_H
#ifdef READLINE_H

# include "../minishell.h"
# include "../Pipex/pipex.h"

/* 
 * @brief get input from the user
 *
 * @param mini the main struct og minishell 
 */
void	start_shell(t_minis mini);

/**
* @brief deals with the signals
*/
void	server(void);

int		get_signal(int sig);

/**
* @brief gets command line prefix from env
* @return command line prefix almost like shell
*/
char	*get_shell_prefix(t_minis *mini);

/**
* @brief gets user from "whoami" command
* @return name of the user logged in
*/
char	*get_user(void);

/**
* @brief duplicates part of a stirngs
* @param src string to duplicate
* @param n number of bytes to duplicate
* @return part of the original string as a separate string
*/
char	*ft_strndup(const char *src, size_t n);

/**
* @brief copies a string
* @param dst copied string
* @param src string to copy
* @return copy of the src string
*/
char	*ft_strcpy(char *dst, const char *src);

/**
* @brief compares two strings
* @param s1 first string to compare
* @param s2 second string to compare
* @return value of the diference of the strings
*/
int		ft_strcmp(const char *s1, const char *s2);

int		chek_expand(char *str, t_minis *mini);

bool	is_allspace(char *str);
void	process_token_list(t_list_ *tokens, char **envp);

void	print_token_list(t_list_ *list);

void	free_tree(t_btree *node);

int		chek_comand(t_minis mini);

#endif
