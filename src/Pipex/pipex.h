/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:30:31 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/03 23:17:35 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_btree
{
	void			*redir;
	char			*cmd;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

void	fork_error(void);
void	pipe_error(void);
void	open_file_error(void);
void	command_error(void);
void	no_path_error(char *cmd);
char	*find_path(char *cmd, char **envp, t_minis *mini);
void	here_doc(char *limiter);
void	execute(char *argv, t_minis *mini);
int		open_file(char *argv, int i);
char	**pipex_split(char const *s, char c);
t_btree	*build_tree(char **argv, int i, int end);
t_btree	*create_node(char *cmd, t_btree *l, t_btree *r, int first_cmd);
void	usage(void);
int		process_tree(t_btree *node, t_minis *mini);
int		chek_biltin(char **cmd);
void	check_execute_permissions(char *file_path, char *orig);

char	*build_and_check_path(char *path, char *cmd);

void	chek_comand_permicion(char *file_path);

char	**get_paths_from_env(char **envp);

void	deep_copy_tokens(t_list_ *original_tokens, t_list_ **merged_list);

t_btree	*create_tree_node(char *cmd);

t_btree	*process_pipe_commands(t_list_ *merged_list, t_btree *root);

#endif
