/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:36:05 by dkros             #+#    #+#             */
/*   Updated: 2024/12/12 19:45:38 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// Structs
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	t_philo			*philos;
}	t_data;

// Function Prototypes

/* utils.c */
int			is_num(char c);
int			ft_simple_atoi(char *number_str);
int			parse_args(t_data *data, int argc, char **argv);
void		cleanup(t_data *data);

/* printing.c */
void		safe_print(t_data *data, int id, const char *msg, int force_print);

/* actions.c */
void		take_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		eat(t_philo *philo);
void		go_to_sleep(t_philo *philo);
void		think(t_philo *philo);

/* monitoring.c */

void		*monitor_routine(void *arg);

/* checks.c */
int			is_simulation_dead(t_data *data);
int			philo_died(t_data *data, int i);
void		handle_philo_death(t_data *data, int i);
int			all_philos_ate_enough(t_data *data);
void		set_dead_flag(t_data *data);

/* philo_routine.c */
void		handle_single_philo(t_philo *philo);
void		*philo_routine(void *arg);

/* time.c */
int			check_dead(t_philo *philo);
int			ft_usleep(long int time, t_philo *philo);
long long	get_current_time(void);
long long	get_timestamp(t_data *data);

/* init.c */
t_philo		create_philo(int id, t_data *data);
int			init_philos(t_data *data);
int			init_data(t_data *data);
int			create_threads(t_data *data);

/* main.c */
int			main(int argc, char **argv);

#endif