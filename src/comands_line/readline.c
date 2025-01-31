/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2025/01/31 18:45:10 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "../builtins/builtins.h"

void	excute_comand_ve(t_minis *mini)
{
	pid_t	pid;
	t_btree	*exec_list;
	int		temp;
	int		status;

	temp = 0;
	if (get_signal(0) != 1)
		mini->exit_code_error = get_signal(0);
	set_error_env(mini);
	mini->tokens = tokenize_and_check_bash_command(mini);
	exec_list = token_merger(mini);
	pid = fork();
	if (pid == 0)
	{
		set_redir(mini->tokens, &exec_list);
		temp = process_tree(exec_list, mini);
		ft_exit_end(temp);
	}
	waitpid(pid, &status, 0);
	mini->exit_code_error = WSTOPSIG(status);
	free_tree(exec_list);
}

void	start_prompt_and_sig(t_minis *mini)
{
	char	*prompt;
	char	*line;

	server();
	(void) prompt;
	line = readline("prompt " );
	if (line == NULL)
		ft_exit_end(0);
	if (mini->line)
	{
		ft_free(mini->line, NULL);
		mini->line = NULL;
	}
	if (!is_allspace(line))
	{
		mini->line = ft_strdup(ft_strdup(line));
		add_history(line);
	}
	else
	{
		ft_free(mini->line, NULL);
		mini->line = NULL;
	}
	free(line);
}

void	excute_comand(t_minis *mini)
{
	if (get_signal(0) != 1)
		mini->exit_code_error = get_signal(0);
	set_error_env(mini);
	mini->exit_code_error = 0;
	mini->tokens = tokenize_and_check_bash_command(mini);
	mini->tokens_copy = tokenize_and_check_bash_command(mini);
	convert_chekline(mini);
	if (chek_comand(*mini) == TRUE)
		builtins(mini);
	else
		excute_comand_ve(mini);
	free_list(mini->tokens, free_token);
	free_list(mini->tokens_copy, free_token);
	mini->tokens = NULL;
	mini->tokens_copy = NULL;
}

void	start_shell(t_minis mini)
{
	getcwd(mini.path, PATH_MAX);
	mini.exit_code_error = 0;
	set_error_env(&mini);
	while (1)
	{
		get_signal(1);
		start_prompt_and_sig(&mini);
		check_syntax(mini.line);
		if (mini.line != NULL && chek_expand(mini.line, &mini) == TRUE
			&& !is_allspace(ft_strdup(mini.line)))
			excute_comand(&mini);
		else
			mini.exit_code_error = 0;
		set_error_env(&mini);
		getcwd(mini.path, PATH_MAX);
		ft_free(mini.line, NULL);
		mini.line = NULL;
	}
	free_list(mini.env, free_env);
	free_list(mini.env_org, free_env);
}
