/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:58:38 by glions            #+#    #+#             */
/*   Updated: 2026/01/24 01:46:18 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include <ostream>


State::State(std::vector<std::vector<int>> grid) : 
	values(grid)
{}

const std::vector<std::vector<int>>	&State::getValues() const
{
	return (this->values);
}

bool	State::operator==(const State &other) const
{
	return (values == other.getValues());
}

bool	State::operator!=(const State &other) const
{
	return (values != other.getValues());
}

Pos	State::getEmptySlot() const
{
	for (size_t i = 0; i < this->values.size(); i++)
	{
		for (size_t j = 0; j < this->values[i].size(); j++)
		{
			if (this->values[i][j] == 0)
				return (Pos{.y= (int)i, .x= (int)j});
		}
	}
	return (Pos{.y= -1, .x= -1});
}

void	State::genNeighbor(std::vector<State> &n, int dirY, int dirX)
{
	State newState = *this;
	Pos	emptySlot = newState.getEmptySlot();
	std::swap(newState.values[emptySlot.y][emptySlot.x],
		newState.values[emptySlot.y + dirY][emptySlot.x + dirX]);
	n.push_back(newState);
}

std::vector<State>	State::genNeighbors()
{
	std::vector<State> neighbors;
	Pos emptySlot = this->getEmptySlot();
	if (emptySlot.y > 0)
		genNeighbor(neighbors, -1, 0);
	if (emptySlot.y < (int)this->values.size() - 1) 
		genNeighbor(neighbors, 1, 0);
	if (emptySlot.x > 0) 
		genNeighbor(neighbors, 0, -1);
	if (emptySlot.x < (int)this->values[emptySlot.y].size() - 1) 
		genNeighbor(neighbors, 0, 1);
	return (neighbors);
}

std::ostream &operator<<(std::ostream &os, const State &state)
{
	for (size_t i = 0; i < state.getValues().size(); i++)
	{
		for (size_t j = 0; j < state.getValues()[i].size(); j++)
		{
			os << " " << state.getValues()[i][j];
		}
		os << std::endl;
	}
	return (os);
}
