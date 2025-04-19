/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:44:42 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 00:54:47 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char *argv[] = {
		"cat",
		"tree.c",
		"-e",
		NULL
	};
	execve("/bin/cat", argv, env);
}
