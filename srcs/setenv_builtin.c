/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasha-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:50:21 by fmasha-h          #+#    #+#             */
/*   Updated: 2019/08/06 18:50:23 by fmasha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		validate_var_name(char **args, int len)
{
	int	i;
	int	j;

	i = (len > 1) ? 1 : 0;
	j = 0;
	if (args[i][j] >= 0 + 48 && args[i][j] <= 9 + 48)
	{
		ft_printf("setenv: Variable name must begin with a letter.\n");
		return (-1);
	}
	while (args[i][j])
	{
		if (!(args[i][j] >= '1' && args[i][j] <= '9') &&
			(!(args[i][j] >= 'a' && args[i][j] <= 'z')) &&
			(!(args[i][j] >= 'A' && args[i][j] <= 'Z')))
		{
			ft_printf("setenv: Variable name must contain ");
			ft_printf("alphanumeric characters.\n");
			return (-1);
		}
		j++;
	}
	return (0);
}

void	add_value(int var_len, char **ar, int i)
{
	char	*tmp;
	char	*var;

	if (i != -1)
		free(g_env->envp[i]);
	if (!(g_env->envp[i] =
	(char*)malloc(sizeof(char) * (var_len + ft_strlen(ar[2])) + 2)))
		return ;
	var = ft_strjoin(ar[1], "=");
	tmp = ft_strjoin(var, ar[2]);
	ft_strcpy(g_env->envp[i], tmp);
	free(tmp);
	free(var);
}

void	add_var(char **ar, int len, int v_i)
{
	char	*var;
	int		i;
	int		var_len;

	i = ((v_i == -1) ? g_env->used_size++ : v_i);
	var_len = ft_strlen(ar[1]);
	if (len == 2)
	{
		if (!(g_env->envp[i] = (char*)malloc(sizeof(char) * var_len + 2)))
			return ;
		var = ft_strjoin(ar[1], "=");
		ft_strcpy(g_env->envp[i], var);
		free(var);
	}
	if (len == 3)
		add_value(var_len, ar, i);
}

int		get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		;
	return (i);
}

void	setenv_builtin(char **argv)
{
	int		i;
	int		len;
	int		var_index;

	i = 0;
	var_index = 0;
	len = get_argc(argv);
	if (len == 1)
		env_builtin();
	else if (len >= 2 && len < 4)
	{
		if (validate_var_name(argv, len) == -1)
			return ;
		if ((var_index = search_var(argv[1])) != -1 && len == 2)
			return ;
		if (g_env->used_size + 1 > g_env->mem_size)
			add_mem_env();
		add_var(argv, len, var_index);
	}
	else
		ft_printf("setenv: Too many arguments.\n");
}
