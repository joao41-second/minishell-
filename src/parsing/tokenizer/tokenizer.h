/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:52 by rpires-c          #+#    #+#             */
/*   Updated: 2025/02/11 11:07:49 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TOKENIZER_H
#ifdef TOKENIZER_H

typedef struct s_token
{
	char	*token;
	char	*type;
	char	*redirection_target;
	char	*redirection_source;
	int		redir_fd;
}	t_token;

typedef struct s_flags
{
	bool	command;
	bool	master;
	bool	override;
}	t_flags;

t_token		*get_token(t_list_ *list);

char		**env_to_matrix(t_minis *mini);

t_list_		*tokenize_and_check_bash_command(t_minis *mini);

void		set_redirection_relations(t_list_ *list);

int			is_whitespace(char c);

int			is_quote(char c);

t_token		*create_token(char *str, char *type, char *target, char *source);

void		add_to_list(t_list_ **list, t_token *token);

char		*get_redirection_type(char *str);

void		free_env_matrix(char **env_matrix);

int			extract_quoted_string(char *line, int *i, char **token);

int			is_quoted_string(char *line);

void		modify_token_types(t_list_ *token_list, t_minis *mini);

t_list_		*initializeAndFinalizeTokenizer(t_minis *mini, char ***env_matrix);

t_list_		*initialize_tokenizer(t_minis *mini, char ***env_matrix);

void		finalize_tokens(t_list_ *token_list,
				char **env_matrix, t_minis *mini);

void		free_token(void *content);

int			process_quotes(const char *line, int i, char quote);

void		convert_chekline(t_minis *mini);

void		extract_token(const char *line, int *i,
				int token_start, char **current_token);

void		process_regular_token_extra(const char *line,
				char quote, int *i);

void		operator_handler(bool *master, bool *override, bool *command);

void		reset_flags(bool *command, bool *master, bool *override);

void		process_pipe_or_redirection(char *line, int *i,
				t_list_ **token_list, t_flags *flags);

void		process_pipe_or_redirection1(char *line, int *i,
				t_list_ **token_list, t_flags *flags);

void		process_regular_command(char *line, int *i, t_list_ **token_list,
				t_flags *flags);

void		process_operator_tokens(const char *line, int *i,
				t_list_ **token_list);

void		process_regular_token(char *line, int *i,
				t_list_ **token_list, bool command);

#endif
