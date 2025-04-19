/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/16 21:54:39 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void    sighandler(int sig, siginfo_t *info, void *ucontext)
// {
//     if (sig == SIGINT)
//     {
//         printf("\n%s$ ", PROMPT);
//     }
// }

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

void    execute(t_cmds *cmds, t_shell *shell)
{

}

void    sigint_handler(int sigint)
{
    
}

void    sigquit_handler(int sigquit)
{
    
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
    signal(SIGINT, &sigint_handler);
    signal(SIGQUIT, &sigquit_handler);
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
        parser(shell.input, &shell);
        execute(shell.cmds, &shell);
        add_history(shell.input);
        free(shell.input);
    }
}
