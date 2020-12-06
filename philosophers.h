/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 09:50:30 by avan-ber      #+#    #+#                 */
/*   Updated: 2020/12/06 14:54:51 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>

# define FORMAT_ERROR "./philo_one nb_of_philo time_to_die time_to_eat \
time_to_sleap [must_eat]\n"

typedef struct		s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	bool			must_eat;
}					t_data;

int					ft_strlen(char *str);
void				ft_put_unsigned_nbr(unsigned long long nb);
int					is_nbr(char *str);
int					simple_atoi(char *nb);

#endif
