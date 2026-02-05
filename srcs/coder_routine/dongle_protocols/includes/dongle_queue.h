/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_queue.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:34:39 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 16:32:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_QUEUE_H
# define DONGLE_QUEUE_H

# include <pthread.h>
# include <stdint.h>
# include "errors.h"

typedef struct s_coder t_coder;

enum e_dongle_queue_config
{
	QUEUE_SIZE = 4,
	QUEUE_MASK = QUEUE_SIZE - 1
};

enum e_enqueue_status
{
	ENQUEUE_SUCCESS,
	ENQUEUE_FULL
};

typedef struct s_dongle_queue
{
	t_coder			*coders[QUEUE_SIZE];
	uint32_t		head;
	uint32_t		tail;
	pthread_mutex_t	mutex;
}	t_dongle_queue;

int						init_dongle_queue(t_dongle_queue *queue);
int						destroy_dongle_queue(t_dongle_queue *queue);
enum e_enqueue_status	enqueue(t_dongle_queue *queue, t_coder *coder);
enum e_enqueue_status	priority_enqueue(t_dongle_queue *queue, t_coder *coder);
t_coder					*dequeue(t_dongle_queue *queue);

#endif
