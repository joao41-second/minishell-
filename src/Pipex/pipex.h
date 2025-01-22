/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:30:31 by rpires-c          #+#    #+#             */
/*   Updated: 2025/01/09 16:18:14 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_btree
{
	void			*redir;
	void			*cmd;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

void	fork_error(void);
void	pipe_error(void);
void	open_file_error(void);
void	command_error(void);
void	no_path_error(char *cmd);
char	*find_path(char *cmd, char **envp);
void	here_doc(char *limiter);
void	execute(char *argv, t_minis *mini);
int		open_file(char *argv, int i);
char	**pipex_split(char const *s, char c);
t_btree	*build_tree(char **argv, int i, int end);
t_btree	*create_node(char *cmd, t_btree *l, t_btree *r, int first_cmd);
void	usage(void);
void	process_tree(t_btree *node, t_minis *mini, int original_stdout);
int		chek_biltin(char **cmd);
#endif
