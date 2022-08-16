/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:36:41 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/28 18:45:15 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_threads(t_global *global)
{
	int	count;

	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_create(&global->philo[count].threads, NULL,
				&action, &global->philo[count]))
			return (FALSE);
		count++;
	}
	return (TRUE);
}

int	finish_destroy(t_global *global)
{
	int	count;

	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_join(global->philo[count].threads, NULL))
			return (FALSE);
		count++;
	}
	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_mutex_destroy(&global->forks[count]))
			return (FALSE);
		count++;
	}
	pthread_mutex_destroy(&global->dead_lock);
	pthread_mutex_destroy(&global->print_lock);
	free(global->forks);
	free(global->philo);
	free(global);
	return (TRUE);
}

t_bool	init_mutexes(t_global *global)
{
	int	count;

	count = 0;
	global->forks = ft_calloc(global->n_philo, sizeof(pthread_mutex_t));
	if (!(global->forks))
		return (FALSE);
	if (pthread_mutex_init(&global->dead_lock, NULL))
		return (FALSE);
	if (pthread_mutex_init(&global->print_lock, NULL))
		return (FALSE);
	while (count < global->n_philo)
	{
		if (pthread_mutex_init(&global->forks[count], NULL))
			return (FALSE);
		count++;
	}
	return (TRUE);
}

t_bool	init_simul(t_global *global)
{
	if (!init_mutexes(global))
		return (FALSE);
	if (!init_threads(global))
		return (FALSE);
	return (TRUE);
}
