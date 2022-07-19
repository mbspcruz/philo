/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:18:53 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/19 15:23:29 by mda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function for the philo to grab a fork
//Needs to first check if it will have time to eat before dying
//If philo dies he won't pick up the fork
//If he has the time he will pick up the fork and depends if its an odd
//Or even ID

void *action(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if(philo->philo_id % 2 == 0)
		usleep(100);
	int time_to_die = 0;
	time_to_die = time_of_death(philo);
	if (philo->data->n_philo == 1)
		start_dying(philo, time_to_die);
	while(check_death(philo) == 0)
	{		
		if (pick_up_fork(philo) != 1)
			break;
		if (philo_eat(philo) != 1)
			break;
		if (let_go_forks(philo) != 1)
			break;
		if (philo_sleep(philo) != 1)
			break;
		if (philo_think(philo) != 1)
			break;
		usleep(1);
	}
	return 0;
}

int	start_sim(t_data *data)
{
	int i;

	i = 0;
	while(i < data->n_philo)
	{
		if(pthread_create(&data->philo[i].thread, NULL, &action, &data->philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while(i < data->n_philo && data->philo_died == 0)
	{

		if(pthread_join(data->philo[i].thread, NULL))
			return (1);
			
		i++;
	}
	return(1);
}

int	main(int ac, char **av)
{
	t_data *data = NULL;
	
	if (!init_args(ac, av, data))
	{
		ft_putstr_fd("Error\nInvalid arguments\n", STDERR_FILENO);
		return(1);
	}
	data = init_args(ac, av, data);
	if (!start_sim(data))
	{
		ft_putstr_fd("Error\nProblem creating threads\n", STDERR_FILENO);
		return(2);
	}
	return 0;
}