/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:08:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 21:41:08 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *new_token(char *argv, t_token_type tk_type, t_quote_type qt_type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->argv = argv;
	new->tk_type = tk_type;
	new->qt_type = qt_type;
	new->next = NULL;
	return (new);
}

void print_token_type(t_token_type type)
{
	if (type == TK_UNEXPECTED)
		printf("unexpected token");
	else if (type == TK_PIPE)
		printf("pipe");
	else if (type == TK_REDIRECT)
		printf("redirect");
	else if (type == TK_COMMAND)
		printf("command");
	else if (type == TK_OPTION)
		printf("option");
	else if (type == TK_TEXT)
		printf("text");
	else if (type == TK_FILE)
		printf("file");
	else if (type == TK_EXPAND)
		printf("expand");
}

t_token_type get_token_type(char *argv)
{
	if (argv[0] == '|' && !argv[1])
		return (TK_PIPE);
	else if (argv[0] == '>' || (!ft_strncmp(argv, ">>", 2) && !argv[2]) ||
			 argv[0] == '<' || (!ft_strncmp(argv, "<<", 2) && !argv[2]))
		return (TK_REDIRECT);
	else if (argv[0] == '-' && argv[1])
		return (TK_OPTION);
	else if (argv[0] == '$' && argv[1])
		return (TK_EXPAND);
	else if (!ft_strncmp("\\", argv, ft_strlen(argv)))
		return (TK_COMMAND);
	else if (!ft_strncmp("\\", argv, ft_strlen(argv)))
		return (TK_FILE);
	return (TK_UNEXPECTED);
}

t_quote_type get_quote_type(char *argv)
{
}

// char	*get_token_argv(char *input, t_token *tokens)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(input);
// 	while (i < len)
// 	{
// 		while (input[i] && input[i] == ' ')
// 			i++;
// 		printf("%d: %c\n", i, input[i]);
// 		while (input[i] && input[i] != ' ')
// 			i++;
// 		printf("%d: %c\n", i, input[i]);
// 	}
// }

t_token *get_tokens(char *input)
{
	int i;
	int len;
	t_token tmp;
	t_token *tokens;

	tokens = NULL;
	i = -1;
	len = ft_strlen(input);
	while (++i < len)
	{
		while (input[i] && input[i] == ' ')
			i++;
		tmp.argv = &input[i];
		while (input[i] && input[i] != ' ')
			i++;
		input[i] = '\0';
		node_addback((void *)&tokens, new_token(tmp.argv, \
			get_token_type(tmp.argv), get_quote_type(tmp.argv)));
	}
	while (tokens)
	{
		print_token_type(tokens->tk_type);
		printf(" -> %s\n", tokens->argv);
		tokens = tokens->next;
	}
	return (NULL);
}
