/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmasha-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:16:36 by fmasha-h          #+#    #+#             */
/*   Updated: 2019/08/06 15:16:38 by fmasha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_builtin(void)
{
	int	i;

	i = 0;
	while (g_env->envp[i])
		ft_printf("%s\n", g_env->envp[i++]);
}
