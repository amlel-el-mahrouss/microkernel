/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <iostream> /* TODO: implement that */
#include <initializer_list> /* freestanding header */

namespace system
{
	template <typename T>
	void print(std::initializer_list<T> init)
	{
		if (init.begin() == init.end()) return;

		std::cout.sync_with_stdio(false);

		for (auto i = init.begin(); i != init.end(); ++i)
        {
			std::cout << *i;
		}
	}
}
