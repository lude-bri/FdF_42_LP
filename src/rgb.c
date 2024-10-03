/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:52:44 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 12:56:05 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

unsigned char	get_t_c(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r_c(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g_c(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b_c(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}
