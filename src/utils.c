/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:57:17 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:44:47 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_simple_atoi(char *number_str)
{
	int		i;
	long	output_number;

	i = 0;
	output_number = 0;
	while (number_str[i])
	{
		if (!is_num(number_str[i]))
			return (-1);
		output_number = output_number * 10 + (number_str[i] - '0');
		i++;
	}
	if (output_number > INT_MAX)
		return (-1);
	return ((int)output_number);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: 4 or 5 arguments required.\n"), 1);
	data->num_philos = ft_simple_atoi(argv[1]);
	data->time_to_die = ft_simple_atoi(argv[2]);
	data->time_to_eat = ft_simple_atoi(argv[3]);
	data->time_to_sleep = ft_simple_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_simple_atoi(argv[5]);
	else
		data->must_eat = 0;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (printf("Error: Invalid argument values.\n"), 1);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}
