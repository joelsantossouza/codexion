/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:24:01 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 23:21:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <pthread.h>
# include <stdint.h>
# include "simulation_control.h"

typedef struct s_coder	t_coder;
typedef struct s_dongle t_dongle;
typedef enum e_simulation_status	(*t_wait_turn_f)(t_coder *coder);

typedef struct s_coder
{
	uint32_t		id;

	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_mutex_t	*log_mutex;

	uint64_t		deadline_ms;
	struct timespec	deadline_ts;

	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

	struct s_coder	*left_neighboor;
	struct s_coder	*right_neighboor;

	t_wait_turn_f	wait_my_turn;
}	t_coder;

#endif
