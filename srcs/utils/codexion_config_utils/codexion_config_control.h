/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_config_control.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:35:44 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 20:28:51 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_CONFIG_CONTROL_H
# define CODEXION_CONFIG_CONTROL_H

# include <unistd.h>

typedef struct s_codexion_config	t_codexion_config;

const t_codexion_config	*codexion_config_control(const t_codexion_config *set_config);
void					set_program_start(t_codexion_config *config);

static inline
void	set_codexion_config(const t_codexion_config *set_config)
{
	codexion_config_control(set_config);
}

static inline
const t_codexion_config	*get_codexion_config(void)
{
	return (codexion_config_control(NULL));
}

#endif
