/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:47:23 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 20:04:39 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *key, char equal, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->equal = equal;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*dup_var(char *str, char c)
{
	int		i;
	char	*var;
	
	var = malloc(sizeof(char) * (ft_strlen_to_c(str, c) + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (*str && *str != c)
		var[i++] = *str++;
	var[i] = '\0';
	return (var);
}

void	set_env(t_env *env, char *key, char *value)
{
	t_env	*set;

	set = search_env(env, key);
	if (!set)
	{
		set = new_env(ft_strdup(key), '=' ,ft_strdup(value));
		node_addback((void **)&env, set);
	}
	else
		set->value = value;
}

void	del_env(t_env *env, char *key)
{
	t_env	*next;

	if (!key)
		return ;
	while (env && env->next)
	{
		next = env->next;
		if (!ft_strncmp(key, next->key, ft_strlen(next->key)))
		{
			env->next = next->next;
			if (next->key)
				free(next->key);
			if (next->value)
				free(next->value);
			free(next);
		}
		env = env->next;
	}
}

t_env	*dup_env(char *env[])
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	t_env	*dup;

	i = -1;
	j = 0;
	dup = NULL;
	while (env[++i])
	{
		j = 0;
		key = dup_var(&env[i][j], '=');
		while (env[i][j] && env[i][j] != '=')
			j++;
		j++;
		value = dup_var(&env[i][j], '\0');
		node_addback((void **)&dup, new_env(key, '=', value));
	}
	return (dup);
}

t_env	*search_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key)
			printf("%s", env->key);
		if (env->equal)
			printf("%c", env->equal);
		if (env->value)
			printf("%s", env->value);
		printf("\n");
		env = env->next;
	}
}
