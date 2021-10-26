/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/18 13:03:59 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/08/31 14:22:29 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <ctype.h>
# include <pthread.h>

typedef struct s_philo_info
{
	unsigned int	philo_amount;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	bool			must_eat;
	unsigned int	nb_must_eat;
	pthread_mutex_t	*forks;
	bool			philo_died;
	pthread_mutex_t	m_philo_died;
	pthread_mutex_t	print;
	unsigned long	time;
}					t_philo_info;

typedef struct s_philo
{
	unsigned int	number;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned long	time_last_eat;
	pthread_t		thread_id;
	bool			done_eating;
	t_philo_info	*info;
}					t_philo;

/*
** error messages functions +--------------------------------------------------+
*/

int				error_argument_amount(void);
int				error_argument_numbers(int index, char *arg);
int				error_philo_amount(unsigned int amount);
int				error_time_to_low(char *time);
int				error_amount_to_eat_zero(void);
int				error_malloc_failed(void);
int				error_threads_failed(t_philo *philo);
int				error_mutex_failed(void);
int				error_argument_empty_string(int index);

/*
** utils +---------------------------------------------------------------------+
*/

void			ft_sleep(unsigned int time_to_pass);
unsigned long	get_time_ms(void);
unsigned int	ft_atoui(char *str);
int				ft_isnumber(char *str);

/*
** parse functions +-----------------------------------------------------------+
*/
int				parse_input(int ac, char **av, t_philo_info *info);

/*
** mutex functions +-----------------------------------------------------------+
*/
void			close_all_forks(t_philo_info *info, int index);
void			close_forks_death_mutex(t_philo_info *info);
void			close_all_mutex(t_philo_info *info);
int				set_mutex(t_philo_info *info);

/*
** philo functions +-----------------------------------------------------------+
*/
int				is_philo_dead(t_philo *philo);
void			write_philo_message(t_philo *philo, char *msg, bool dead);
void			*philo_being_philo(void *varg);
int				philo_check(t_philo *philo);
int				create_threads(t_philo_info *info);

#endif
