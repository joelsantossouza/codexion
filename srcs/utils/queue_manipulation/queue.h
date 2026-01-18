/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 00:13:44 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 20:48:38 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <stdint.h>
# include "errors.h"

# define BUFFER_SIZE	1024

typedef struct s_queue
{
	uint64_t		data[BUFFER_SIZE];
	uint64_t		first;
	uint64_t		last;
}	t_queue;

static inline
int	enqueue(t_queue *queue, uint64_t data)
{
	const uint64_t	next = (queue->last + 1) % BUFFER_SIZE;

	if (next == queue->first)
		return (FULL_QUEUE_ERROR);
	queue->data[queue->last] = data;
	queue->last = next;
	return (SUCCESS);
}

static inline
int	queue_peek(t_queue *queue, uint64_t *data)
{
	const uint64_t	first = queue->first;

	if (first == queue->last)
		return (EMPTY_QUEUE_ERROR);
	*data = queue->data[first];
	return (SUCCESS);
}

#endif
