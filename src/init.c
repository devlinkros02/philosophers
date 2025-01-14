/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:58:59 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:41:55 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	create_philo(int id, t_data *data)
{
	t_philo	philo;

	philo.id = id;
	philo.data = data;
	philo.last_meal = get_current_time();
	philo.meals_eaten = 0;
	return (philo);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("Error: malloc failed for philos.\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i] = create_philo(i, data);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (printf("Error: malloc failed for forks.\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: pthread_mutex_init failed.\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (printf("Error: init failed for write_mutex.\n"), 1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (printf("Error: init failed for dead_mutex.\n"), 1);
	data->dead = 0;
	data->start_time = get_current_time();
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (printf("Error: pthread_create failed.\n"), 1);
		i++;
	}
	return (0);
}
