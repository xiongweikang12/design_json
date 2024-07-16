#include "jsonElement.h"

namespace civitasv {
	namespace json
	{


		jsonobject* jsonElement::Asobject()
		{
			
			if (type_ == Type::JSON_OBJECT)
			{
				return value_.value_object;
			}
			Error("Type of jsonElement isnt jsonobject");
			
		}

		jsonArray* jsonElement::Asarray()
		{
			if (type_ == Type::JSON_ARRAY)
			{
				return value_.value_array;
			}
			Error("Type of jsonElement isnt jsonarray");
		
		}

		float jsonElement::AsNumber()
		{
			if (type_ == Type::JSON_NUMBER)
			{
				return value_.value_number;
			}
			Error("Type of jsonElement isnt jsonnumber");
		}

		bool jsonElement::AsBool()
		{
			if (type_ == Type::JSON_BOOL)
			{
				return value_.value_bool;
			}
			Error("Type of jsonElement isnt jsonbool");
		}

		std::string jsonElement::Asstring()
		{
			if (type_ == Type::JSON_STRING)
			{
				return *(value_.value_string);
			}
			Error("Type of jsonElement isnt jsonstring");
		}

		std::string jsonElement::Dumps()
		{
			std::stringstream ss;
			switch (type_)
			{
			case Type::JSON_OBJECT:
			{
				ss << (*(value_.value_object));
				break;
			}
			case Type::JSON_ARRAY:
			{
				ss << (*(value_.value_array));
				break;
			}
			case Type::JSON_STRING:
			{
				ss << '\"' << *(value_.value_string) << '\"';
				break;
			}
			case Type::JSON_NUMBER:
			{
				ss << value_.value_number;
				break;
			}
			case Type::JSON_BOOL:
			{
				ss << (value_.value_bool == true ? "true" : "false");
				break;
			}
			case Type::JSON_NULL:
			{
				ss << "null";
				break;
			}
			default:
				break;
			}
			return ss.str();
		}

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
		//重载运算符，打印{}

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