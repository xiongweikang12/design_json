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

		//��Ԫ��������ȫ�ֺ���������������Ҫ�����ڲ����� friend;
	}
}