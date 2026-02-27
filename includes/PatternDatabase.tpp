/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.tpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:04:54 by glions            #+#    #+#             */
/*   Updated: 2026/02/27 12:45:13 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
PatternDatabase<T, AbstractFn, NeighborsFn>::PatternDatabase(
	const std::vector<TileType>& 	pattern,
	T								goal,
	AbstractFn 						abstractFn,
	NeighborsFn 					neighborsFn
):
	_pattern(pattern.begin(), pattern.end()),
	_goal(goal),
	_abstractFn(abstractFn),
	_neighborsFn(neighborsFn)
{}

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
void PatternDatabase<T, AbstractFn, NeighborsFn>::build()
{
	std::queue<T>	open;
	open.push(this->_goal);
	T goalPattern = _abstractFn(this->_goal);
	this->_distances[goalPattern] = 0;
	while (!open.empty())
	{
		T	curr = open.front();
		open.pop();
		T currPattern = this->_abstractFn(curr);
		int	currDist = this->_distances[currPattern];
		for (const auto &n : this->_neighborsFn(curr))
		{
			T nPattern = this->_abstractFn(n);
			if (this->_distances.find(nPattern) == this->_distances.end())
			{
				this->_distances[nPattern] = currDist + 1;
				open.push(n);
			}
		}	
	}
}

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
int PatternDatabase<T, AbstractFn, NeighborsFn>::getDistance(const T& state) const
{
	T abs = this->_abstractFn(state);
    auto it = this->_distances.find(abs);
    if (it != this->_distances.end())
        return (it->second);
    return (0);
}


