/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:58:18 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:32:26 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int			i;
	t_data		data;
	pthread_t	monitor_thread;

	if (parse_args(&data, argc, argv) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (cleanup(&data), 1);
	if (init_philos(&data) != 0)
		return (1);
	if (create_threads(&data) != 0)
		return (1);
	if (data.num_philos != 1)
	{
		if (pthread_create(&monitor_thread, NULL, monitor_routine, &data) != 0)
			return (printf("Error: pthread_create failed for monitor.\n"), 1);
		pthread_join(monitor_thread, NULL);
	}
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	return (cleanup(&data), 0);
}
