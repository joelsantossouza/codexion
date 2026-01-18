/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:30 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 18:39:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_ROUTINE_H
# define CODER_ROUTINE_H

# include <stdint.h>
# include <pthread.h>
# include "queue.h"

// CODER TASKS
enum
{
	COMPILE,
	DEBUG,
	REFACTOR,
	NUMBER_OF_TASKS
};

// CODER STATES
enum
{
	GIVE_ONE_DONGLE		= 1 << 0,
	TWO_DONGLES			= 1 << 1,
	WAITING_TO_COMPILE	= 1 << 3 
};

typedef struct s_coder
{
	uint32_t		id;
	pthread_t		thread;
	pthread_mutex_t	local_mutex;
	pthread_mutex_t	*global_mutex;
	uint8_t			state;
	uint32_t		compilations_done;
	t_queue			last_compilations_queue;
}	t_coder;

typedef struct s_coder_config
{
	uint32_t	tasks[NUMBER_OF_TASKS];
	uint32_t	burnout;
}	t_coder_config;

const t_coder_config	*coder_config(uint32_t *compile, uint32_t *debug, uint32_t *refactor, uint32_t *burnout);
int						wait_to_compile(uint8_t *coder_state, pthread_mutex_t *mutex, uint32_t *time_left);
void					*start_working(t_coder *coder);

#endif
