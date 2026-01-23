/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:58:38 by glions            #+#    #+#             */
/*   Updated: 2026/01/23 12:30:58 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

State::State(std::vector<std::vector<int>> grid) : 
	values(grid)
{

}

std::vector<std::vector<int>>	State::getValues() const
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

Pos	State::getEmptySlot()
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

State	*State::genNeighbor(Direction dir)
{
	State 	*newState = this;
	Pos		emptySlot = newState->getEmptySlot();
	if (emptySlot.x == -1 || emptySlot.y)
		return (NULL);
	switch (dir)
	{
		case UP:
			if (emptySlot.y > 0) 
				std::swap(newState->values[emptySlot.y][emptySlot.x],
						newState->values[emptySlot.y - 1][emptySlot.x]);
			else
				return (NULL);
			break ;
		case DOWN:
			if (emptySlot.y < newState->values.size() - 1) 
				std::swap(newState->values[emptySlot.y][emptySlot.x],
						newState->values[emptySlot.y + 1][emptySlot.x]);
			else
				return (NULL);
			break ;
		case LEFT:
			if (emptySlot.x > 0) 
				std::swap(newState->values[emptySlot.y][emptySlot.x],
						newState->values[emptySlot.y][emptySlot.x - 1]);
			else
				return (NULL);
			break ;
		case RIGHT:
			if (emptySlot.x < newState->values[emptySlot.y].size() - 1) 
				std::swap(newState->values[emptySlot.y][emptySlot.x],
						newState->values[emptySlot.y][emptySlot.x + 1]);
			else
				return (NULL);
			break ;
		default:
			std::cerr << "Direction unknown" << std::endl;
			return (NULL);
	}
	return (newState);
}