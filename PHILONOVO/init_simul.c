/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:36:41 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/22 17:37:02 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_threads (t_global *global)
{
	int count;
	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_create(&global->philo[count].threads, NULL, &action, &global->philo[count]))
			return FALSE;
		count++;
	}
	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_join(global->philo[count].threads, NULL))
			return FALSE;
		count++;
	}
	return TRUE;
}

t_bool	init_mutexes(t_global *global)
{
	int count;
	count = 0;
	if (!(global->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * global->n_philo)))
		return FALSE;
	if (pthread_mutex_init(&global->dead_lock, NULL))
		return FALSE;
	while (count <  global->n_philo)
	{
		if (pthread_mutex_init(&global->forks[count], NULL))
			return FALSE;
		count++;
	}
	return(TRUE);
}

t_bool init_simul(t_global *global)
{
	if (!init_mutexes(global))
		return FALSE;
	if (!init_threads(global))
		return FALSE;
	return TRUE;
}