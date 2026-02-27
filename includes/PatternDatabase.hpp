/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:49:24 by glions            #+#    #+#             */
/*   Updated: 2026/02/27 12:44:49 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNDATABASE_HPP
# define PATTERNDATABASE_HPP

# include <vector>
# include <functional>
# include <concepts>
# include <cstddef>
# include <unordered_map>
# include <unordered_set>

# include "nPuzzle.hpp"

template<typename T>
concept Hashable =
	requires(T a){
		{ std::hash<T>{}(a) } -> std::convertible_to<size_t>;
	};

template<typename T>
concept PatternState =
	requires(T a) {
		typename T::TileType;
		{a == a} -> std::convertible_to<bool>;
	} && Hashable<T>;

template<
	PatternState T,
	typename	AbstractFn,
	typename	NeighborsFn
>
class PatternDatabase
{
	public:
		using TileType = typename T::TileType;
		PatternDatabase(
			const std::vector<TileType>&,
			T,
			AbstractFn,
			NeighborsFn
		);
		// methods
		void	build();
		int		getDistance(const T &) const;
	private:
		// props
		std::unordered_set<TileType>	_pattern;
		T								_goal;
		std::unordered_map<T, int>		_distances;
		AbstractFn						_abstractFn;
		NeighborsFn						_neighborsFn;
};

#include "PatternDatabase.tpp"

#endif