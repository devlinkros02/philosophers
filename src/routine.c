/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:09 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:43:21 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	safe_print(philo->data, philo->id, "has taken a fork", 0);
	ft_usleep(philo->data->time_to_die + 1, philo);
	safe_print(philo->data, philo->id, "died", 0);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_current_time();
	if (philo->data->num_philos == 1)
		return (handle_single_philo(philo), NULL);
	if (philo->id % 2 == 1)
		ft_usleep(200, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		eat(philo);
		go_to_sleep(philo);
		think(philo);
	}
	return (NULL);
}
