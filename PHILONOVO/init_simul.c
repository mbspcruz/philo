/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:36:41 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/24 16:29:57 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_threads (t_global *global)
{
	int count;
	count = 0;
	//pthread_mutex_lock(&global->dead_lock);
	while (count < global->n_philo)
	{
		if (pthread_create(&global->philo[count].threads, NULL, &action, &global->philo[count]))
			return FALSE;
		pthread_detach(global->philo->threads);
		usleep(200);
		count++;
	}
	check_death(global);
	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_join(global->philo[count].threads, NULL))
			return FALSE;
		count++;
	}
	count = 0;
	while (count < global->n_philo)
	{
		if (pthread_mutex_destroy(&global->forks[count]))
			return FALSE;
		count++;
	}
	pthread_mutex_destroy(&global->is_dead_lock);
	pthread_mutex_destroy(&global->dead_lock);
	pthread_mutex_destroy(&global->eat_lock);
	pthread_mutex_destroy(&global->print_lock);
	free(global->philo);
	free(global);
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
	if (pthread_mutex_init(&global->eat_lock, NULL))
		return FALSE;
	if (pthread_mutex_init(&global->is_dead_lock, NULL))
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