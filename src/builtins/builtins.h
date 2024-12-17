/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:55:23 by jperpct           #+#    #+#             */
/*   Updated: 2024/11/15 15:18:41 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUILTINS_H
#ifdef BUILTINS_H

# include "../../libft/Get_next_line/get_next_line_bonus.h"
# include "../../libft/printf/ft_printf.h"

typedef struct s_env
{
	char	*name;
	char	*content;
	int		chek;
}			t_env;

/**
 * @brief save the env in linked list 
 * @param env file env the system
 * @return linked list
 */
t_list_		*env_split(char **env);

/**
 * @brief print the struct  t_env  
 * @param point t_env node 
 */
void		print_env(void *point);

/**
 * @brief the start env in case the env -i
 * @details file ./env/set_start_env.c
 * @param list where aloc the vaiabel
 * @return the list alocade
 */
t_list_		*list_env_i(void);

/**
 * @brief alloc the memory for struc t_env using in list 
 * @details file ./env/env.c
 * @param s1 the funcion use getenv search 
 * @return vaiabel t_env alocad 
 */
t_env		*new_node(char *s1);

/**
 * @brief the funcion use for list free the struct t_env
 * @details file ./env/env.c
 * @param point ponter for list
 */
void		free_env(void *point);

/**
 * @brief the env the builtins
 * @details file ./env/env_comand.c
 * @param mini 
 */
void		ft_env(t_minis *mini);

/**
 * @brief ins funcion return the vaiabel environment expande
 * @details file ./env/env_comand.c
 * @param mini struct base the minishell
 * @param var string shows variabel environment
 * @return the vaiabel environment expanded  
 */
char		*ft_getenv(t_minis *mini, char *var);

/**
 * @brief return the especifcally node the list
 * @details file ./unset/unset.c
 * @param point  the node list
 * @param locate the param user for funcion for locate node 
 */
void		*get_env_node(void *point, void *locate);

/**
 * @brief the builtin cd comand  
 * @details file ./cd/cd.c
 * @param mini the struct base the minishell
 */
void		ft_cd(t_minis *mini);

/**
 * @brief the builtins pwd comand
 * @details file ./pwd/pwd.c
 * @param mini the struct base the minishell
 */
void		ft_pwd(t_minis *mini);

/**
 * @brief the builtin ft_exit  
 * @details file ./exit/exit.c
 * @param mini the struct base the minishell
 */
void		ft_exit(t_minis *mini);

/**
 * @brief the builtin funcion 
 * @details file ./unset/unset.c
 * @param mini the struct base the minishell
 */
void		ft_unset(t_minis *mini);

/**
 * @brief the comand builtins the minishell
 * @details file ./export/export.c
 * @param mini the struct base the minishell
 */
void		ft_export(t_minis *mini);

/**
 * @brief the comand echo in builtins the minishell
 * @details file ./echo/ft_echo.c
 * @param mini the struct base the minishell 
*/
void		ft_echo(t_minis *mini);

/**
 * @brief the funcion the started the builtins and redirects
 * @details file ./builtins.c
 * @param mini the struct base the minishell 
 */
void		builtins(t_minis *mini);

/**
 * @brief add the new vaiabel in the lists the environment variabels
 * @details file ./export/export.c
 * @param list the list to and variabel
 * @param var stuct to andd in list 
 */
void		export_add(t_list_ **list, t_env *var);

/**
 * @brief organze the list the environment variabels
 * @details file ./export/organizer.c 
 * @param list to organze
 */
void		organizer_list(t_list_ *list);

/**
 * @brief print the export
 * @details file ./export/organizer.c
 * @param point 
 */
void		print_export(void *point);

/**
 * @brief transfor the t_list node int t_env node 
 *
 * @param list node the list
 * @return t_env node 
 */
t_env		*list_to_env(t_list_ *list);

/**
 * @brief return the contet the list determinated for list 
 * @details file ./export/export_util.c
 * @param list get the content
 * @param var for detent the content 
 * @return content
 */
t_env		*ft_getenv_content(t_list_ *list, char *var);

/**
 * @brief set and aloc the stuct t_env variabels to null
 *
 * @return t_env stuct aloced 
 */
t_env		*new_tenv(void);


t_env	*new_node_une(char *s1, char *s2);
#endif // DEBUG
