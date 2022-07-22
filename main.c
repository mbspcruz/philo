/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cruz <mda-cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:18:53 by mda-cruz          #+#    #+#             */
/*   Updated: 2022/07/21 19:39:22 by mda-cruz         ###   ########.fr       */
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
	while(1)
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
	while(i < data->n_philo)
	{

		if(pthread_join(data->philo[i].thread, NULL))
			return (0);
		i++;
	}
	return(1);
}

int	main(int ac, char **av)
{
	t_data *data = NULL;
	
	if (!valid_args(ac, av))
	{
		ft_putstr_fd("Error\nInvalid arguments\n", STDERR_FILENO);
		return(1);
	}
	data = init_args(ac, av, data);
	if (!start_sim(data))
	{
		free_clean(data);
		ft_putstr_fd("Error\nProblem creating threads\n", STDERR_FILENO);
		return(2);
	}
	free_clean(data);
	return 0;
}