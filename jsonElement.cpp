#include "jsonElement.h"

namespace civitasv {
	namespace json
	{
		std::ostream& operator<<(std::ostream& os, const jsonobject& object)
		{
			os << "{";
			for (auto iter = object.begin(); iter != object.end(); iter++)
			{
				os << '\"' << iter->first << '\"' << ":" << iter->second->Dumps();
				if (iter != --object.end())
				{
					os << ",";
				}
			}
			os << "}";
			return os;
		}

		std::ostream& operator<<(std::ostream& os, const jsonArray& array)
		{
			os << "[";
			for (size_t i = 0; i < array.size(); i++)
			{
				os << array[i]->Dumps();
				if (i != array.size() - 1)
				{
					os << ",";
				}
			}
			os << "]";
			return os;
		}

		//友元函数，像全局函数，但其在声明要在类内部声明 friend;
	}
}