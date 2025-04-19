/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 20:37:33 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *parser(char *input, t_shell *shell)
{
    int     i;

    i = -1;
    printf("input: %s\n", input);
    shell->line = ft_strdup(input);
    get_tokens(shell->line);
    // while (input[++i])
    // {
    //     node_addback(&token, new_token());
    // }
    return (NULL);
}

void    execute(char *input, t_shell *shell)
{
    char    *line;
    
    line = parser(input, shell);
    if (!line)
        exit(EXIT_FAILURE);
}

void    signal_handler(int signal)
{
    if (signal == SIGINT)
        printf("\n%s", PROMPT);
    else if (signal == SIGQUIT)
        return ;
}

void    init_shell(char *env[], t_shell *shell)
{        
    shell->cmds = NULL;
    shell->tokens = NULL;
    shell->env = dup_env(env);
    shell->path = search_env(shell->env, "PATH")->value;
    shell->user = search_env(shell->env, "USER")->value;
    shell->home = search_env(shell->env, "HOME")->value;
    shell->oldpwd = search_env(shell->env, "OLDPWD")->value;
    shell->pwd = search_env(shell->env, "PWD")->value;
    signal(SIGINT, &signal_handler);
    signal(SIGQUIT, &signal_handler);
}

void    exit_shell(t_shell *shell)
{
    printf("exit\n");
    rl_clear_history();
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[], char *env[])
{
    t_shell shell;

    init_shell(env, &shell);
    while (true)
    {
        shell.input = readline(PROMPT);
        if (!shell.input)
            exit_shell(&shell);
        execute(shell.input, &shell);
        add_history(shell.input);
        free(shell.input);
    }
}
