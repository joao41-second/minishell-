/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpires-c <rpires-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:26 by jperpct           #+#    #+#             */
/*   Updated: 2024/10/16 16:22:18 by rpires-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void start_shell() 
{
    char        cwd[1024];
    char        *line;
    char        *prompt;
    char        *temp1;
    char        *temp2;
    char        *user;
    char        *host;
    char        *session_manager;
    char        *start;
    char        *end;
    size_t		session_len;
	
    server();
    while (1) 
    {
        user = getenv("USER");
        session_manager = getenv("SESSION_MANAGER");
        
        if (!user)
        {
            ft_printf("Error: Could not get USER environment variable\n");
            exit(1);
        }
        
        if (!session_manager)
        {
            ft_printf("Error: Could not get SESSION_MANAGER environment variable\n");
            exit(1);
        }

        session_len = ft_strlen(session_manager);
        start = ft_strnstr(session_manager, "local/", session_len);
        if (!start)
        {
            ft_printf("Error: SESSION_MANAGER format is invalid (missing 'local/')\n");
            exit(1);
        }
        
        start += 6;
        end = ft_strchr(start, '.');
        if (!end)
        {
            ft_printf("Error: SESSION_MANAGER format is invalid (missing '.')\n");
            exit(1);
        }

        host = strndup(start, end - start);
        if (!host)
        {
            ft_printf("Error: Memory allocation failed for host\n");
            exit(1);
        }

        if (getcwd(cwd, sizeof(cwd)) == NULL) 
        {
            perror("getcwd() error");
            exit(1);
        }

        temp1 = ft_strjoin(user, "@");
        if (!temp1)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }
        
        temp2 = ft_strjoin(temp1, host);
        free(temp1);
        free(host);
        if (!temp2)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }
        
        temp1 = ft_strjoin(temp2, ":");
        free(temp2);
        if (!temp1)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }

        temp2 = ft_strjoin(temp1, "~");
        free(temp1);
        if (!temp2)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }
        
        temp1 = ft_strjoin(temp2, cwd);
        free(temp2);
        if (!temp1)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }
        
        prompt = ft_strjoin(temp1, "$ ");
        free(temp1);
        if (!prompt)
        {
            ft_printf("Error: Memory allocation failed\n");
            exit(1);
        }
        
        line = readline(prompt);
        free(prompt);
        
        if (line == NULL) 
            break;
            
        ft_printf("%s\n", line);
        check_syntax(line);
        add_history(line);
        free(line);
    }
}
