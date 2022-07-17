// #include "philo.h"

// //start by locking forks

// void *action(void *p)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)p;
// 	printf("[%d] Philosopher %d is thinking\n", get_time() - philo->data->init_time, philo->philo_id);
// 	return 0;
// }

// int	setup_args(int ac, char **av, t_data *data)
// {
// 	data = (t_data *)malloc(sizeof(t_data));
// 	if(!data)
// 		return (0);
// 	data->n_philo = ft_atoi(av[1]);
// 	data->t_die = ft_atoi(av[2]);
// 	data->t_eat = ft_atoi(av[3]);
// 	data->t_sleep = ft_atoi(av[4]);
// 	if(ac == 6)
// 		data->n_eat = ft_atoi(av[5]);
// 	data->init_time = get_time();
// 	return (1);
// }

// int	setup_philo(t_data *data)
// {
// 	int count;
	
// 	count = 0;
// 	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
// 	if(!data->philo)
// 		return 0;
// 	while (count < data->n_philo)
// 	{
// 		data->philo[count].philo_id = count + 1;
// 		data->philo[count].meals_left = 0;
// 		data->philo[count].data = data;
// 		count++;
// 	}
// 	return (1);
// }

// int	setup_mutex(t_data *data)
// {
// 	int count;
	
// 	count = 0;
// 	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philo);
// 	if (!data->forks)
// 		return(0);
// 	while(count < data->n_philo)
// 	{
// 		pthread_mutex_init(&data->forks[count], NULL);
// 		count++;
// 	}

// }

// int	init_args(int ac, char ** av, t_data *data)
// {
// 	if (valid_args(ac, av) != 1)
// 		return (0);
// 	if (setup_args(ac, av, data) != 1)
// 		return (0);
// 	if (setup_philo(data)!= 1)
// 		return (0);
// 	if (setup_mutex(data) != 1)
// 		return (0);
// }

// int	start_sim(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while(i < data->n_philo)
// 	{
// 		if(pthread_create(&data->philo[i].thread, NULL, &action, &data->philo[i]) != EXIT_SUCCESS)
// 			return (0);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < data->n_philo)
// 	{

// 		if(pthread_join(data->philo[i].thread, NULL) != EXIT_SUCCESS)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	main(int ac, char **av)
// {
// 	t_data data;

// 	if (!init_args(ac, av, &data))
// 	{
// 		ft_putstr_fd("Error\nInvalid arguments\n", STDERR_FILENO);
// 		return(1);
// 	}
// 	if (!start_sim(&data))
// 	{
// 		ft_putstr_fd("Error\nCouldn't start sim\n", STDERR_FILENO);
// 		return(2);
// 	}
// 	return 0;
// }