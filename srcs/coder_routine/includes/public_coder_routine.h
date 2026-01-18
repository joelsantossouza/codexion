/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_coder_routine.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:30 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 21:17:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUBLIC_CODER_ROUTINE_H
# define PUBLIC_CODER_ROUTINE_H

# include <stdint.h>
# include <pthread.h>
# include "queue.h"

// CODER STATES
enum
{
	ONE_DONGLE			= 1 << 0,
	TWO_DONGLES			= 1 << 1,
	WAITING_TO_COMPILE	= 1 << 2,
};

typedef struct s_coder
{
	uint32_t		id;
	pthread_t		thread;
	pthread_mutex_t	local_mutex;
	pthread_mutex_t	*global_mutex;
	uint8_t			state;
	uint32_t		burnout_remaining;
	uint32_t		compilations_done;
	t_queue			compilations_history;
}	t_coder;

void	*start_working(t_coder *coder);

#endif
