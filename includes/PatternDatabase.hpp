/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:17:13 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 15:21:54 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNDATABASE_HPP
# define PATTERNDATABASE_HPP

# include <algorithm>
# include <unordered_map>
# include <queue>
# include "PatternState.hpp"

using PDBTable = std::unordered_map<PatternState, int, PatternHash>;

class PatternDatabase
{
	public:
		// constructor
		PatternDatabase();
		// methods
		void	buildAllPDBs(const Node &goal);
		void	buildPatterns(int size);
		// getters
		std::vector<std::unordered_set<int>>	getPatterns() const;
		std::vector<PDBTable>					getPDBs() const;
	private:
		// props
		std::vector<std::unordered_set<int>>	_patterns;
		std::vector<PDBTable>					_PDBs;
		// methods	
		PDBTable	buildPDB(const Node &goal, std::unordered_set<int> &pattern);
};

#endif