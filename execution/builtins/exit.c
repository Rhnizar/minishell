/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:03:23 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/14 20:19:16 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_message(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static long	my_ft_atoi(char *str)
{
	int					sign;
	unsigned long		ret;
	int					i;

	ret = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = ret * 10 + str[i++] - '0';
		if ((sign == -1 && ret - 1 > LONG_MAX) || (ret > LONG_MAX && sign == 1))
		{
			error_message(str);
			return (255);
		}
	}
	return (ret * sign);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1 || (str[i] == '-' && i != 0) \
			|| (str[i] == '+' && i != 0))
			return (1);
		i++;
	}
	return (0);
}

void	exitt(t_global *global, t_args *args)
{
	if (args)
	{
		ft_putstr_fd("exit\n", 2);
		if (!args->next)
			exit(0);
		if (args->next->next && check_arg(args->next->str) == 0)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			global->exit_status = 1;
		}
		else if (check_arg(args->next->str) == 1)
		{
			error_message(args->next->str);
			exit(255);
		}
		else
			exit(my_ft_atoi(args->next->str));
	}
}
