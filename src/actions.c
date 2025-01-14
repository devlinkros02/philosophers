/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:59:42 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:40:16 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->num_philos]);
}

void	take_forks(t_philo *philo)
{
	int	temp;
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->data->num_philos;
	if (left_fork > right_fork)
	{
		temp = left_fork;
		left_fork = right_fork;
		right_fork = temp;
	}
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	safe_print(philo->data, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	safe_print(philo->data, philo->id, "has taken a fork", 0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	take_forks(philo);
	safe_print(philo->data, philo->id, "is eating", 0);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	ft_usleep((philo->data->time_to_eat), philo);
	put_down_forks(philo);
}

void	go_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	safe_print(philo->data, philo->id, "is sleeping", 0);
	ft_usleep((philo->data->time_to_sleep), philo);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	safe_print(philo->data, philo->id, "is thinking", 0);
}
