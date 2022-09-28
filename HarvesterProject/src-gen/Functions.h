
#ifndef ROBOCALC_FUNCTIONS_H_
#define ROBOCALC_FUNCTIONS_H_

#include "DataTypes.h"
#include <vector>
#include <set>

namespace robocalc
{
	namespace functions
	{
		 jointFruit(null apple);
		bool jointInLimit(null position);
		 choose(std::set<> s);
		bool reachable(null apple);
		 jointApproach(null apple);
		 jointStorage(null apple);
		 fdiff(null apple,  lut);
		 addApple( ps, null a, null j1, null j2, null j3);
		bool isEmpty( lut);
		
		template<typename T>
		std::set<T> set_union(std::set<T> s1, std::set<T> s2)
		{
			std::set<T> ret;
			ret.insert(s1.begin(), s1.end());
			ret.insert(s2.begin(), s2.end());
			return ret;
		}
		
		template<typename T>
		unsigned int size(std::set<T> s)
		{
			return s.size();
		}
	}
}

#endif
