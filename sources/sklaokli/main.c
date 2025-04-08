/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/08 19:47:55 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    sighandler(int sig, siginfo_t *info, void *ucontext)
{
    if (sig == SIGINT)
    {
        printf("\n%s$ ", PROMPT);
    }
}

char    *parser(char *input)
{
    add_history(input);
    free(input);
    return (input);
}

void    execute(char *input, t_shell *shell)
{
    shell->line = parser(input);
    return ;
}

void    init_shell(t_shell *shell)
{
    struct sigaction    sa;
    
    sa.sa_sigaction = &sighandler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
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

    init_shell(&shell);
    while (true)
    {
        shell.input = readline(PROMPT"$ ");
        if (shell.input)
            execute(shell.input, &shell);
        else if (!shell.input)
            exit_shell(&shell);
    }
}
