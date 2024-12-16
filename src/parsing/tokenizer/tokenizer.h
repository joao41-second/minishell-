/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:42:52 by rpires-c          #+#    #+#             */
/*   Updated: 2024/12/16 14:15:25 by rui              ###   ########.fr       */
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
}	t_token;

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

void		finalize_tokens(t_list_ *token_list, char **env_matrix, t_minis *mini);

void		free_token(void *content);

#endif
