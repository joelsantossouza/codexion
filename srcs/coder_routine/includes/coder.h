/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:24:01 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 12:02:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <pthread.h>
# include <stdint.h>
# include "simulation_control.h"
# include "dongle_protocols.h"

enum e_start_pattern
{
	SEQUENTIAL = 1,
	ODD_EVEN,
};

# ifndef START_PATTERN
#  define START_PATTERN	ODD_EVEN
# endif

# ifndef START_INTERVAL_MS
#  define START_INTERVAL_MS	1
# endif

# if START_INTERVAL_MS < 0 || START_INTERVAL_MS > 2147483647
#  error "START_INTERVAL must be in range of 0 and INT32_MAX"
# endif

typedef enum e_enqueue_status	(*t_enqueue_f)(t_dongle_queue *, t_coder *);

typedef struct s_coder
{
	uint32_t		id;

	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_mutex_t	*log_mutex;

	uint64_t		deadline_ms;
	struct timespec	deadline_ts;
	uint32_t		compilations_done;

	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

	struct s_coder	*left_neighbor;
	struct s_coder	*right_neighbor;

	t_enqueue_f		enqueue;
}	t_coder;

void	init_coder_log(void);
int		init_coders(uint32_t ncoders, t_coder coders[ncoders],
			t_dongle dongles[ncoders]);
int		destroy_coders(uint32_t ncoders, t_coder coders[ncoders]);

int		start_coders(uint32_t size, t_coder coders[size], uint32_t stride);
void	*coder_routine(t_coder *coder);

#endif
