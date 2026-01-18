/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_coder_routine.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:57:36 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 19:10:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_CODER_ROUTINE_H
# define PRIVATE_CODER_ROUTINE_H

# include "public_coder_routine.h"

// CODER TASKS
enum
{
	COMPILE,
	DEBUG,
	REFACTOR,
	NUMBER_OF_TASKS
};

typedef struct s_coder_config
{
	uint32_t	tasks[NUMBER_OF_TASKS];
	uint32_t	burnout;
}	t_coder_config;

const t_coder_config	*coder_config(uint32_t *compile, uint32_t *debug, uint32_t *refactor, uint32_t *burnout);

#endif
