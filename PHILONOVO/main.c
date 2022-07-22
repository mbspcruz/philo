/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:31:44 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/22 15:28:26 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int get_time()
{
	struct timeval start;
	int m_s;
	gettimeofday(&start, NULL);
	m_s = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (m_s);
}

int time_diff(int past)
{
	int curr = get_time();
	int t_diff = (past - curr);
	return (t_diff);
}

int	main(int ac, char **av)
{
	t_global *global;
	global = NULL;

	if (!check_args(ac, av))
	{
		ft_putstr_fd("Error with args", STDERR_FILENO);
		return 1;
	}
	if (!init_global(global, ac, av))
	{
		ft_putstr_fd("Error with philo assignement", STDERR_FILENO);
		return 2;
	}
	global = init_global(global, ac, av);
	printf("%d\n", time_diff(global->time_init));
}