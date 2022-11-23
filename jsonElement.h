#pragma once
#include <string>
#include <vector>
#include<map>
#include "Error.h"
#include <iostream>
#include <sstream>


namespace civitasv {
	namespace json
	{
		class jsonElement;
		using jsonobject = std::map<std::string, jsonElement*>;
		//表示一个json对象 
		using jsonArray = std::vector<jsonElement*>;
		//json对象，和数组都允许数据类型嵌套

		class jsonElement
		{
		public:
			enum class Type
			{
				JSON_OBJECT,///JSON_OBJECT {...}
				JSON_ARRAY, ///JSON_ARRAY [...]
				JSON_STRING, ///JSON_STRING "..."
				JSON_NUMBER, ///
				JSON_BOOL,
				JSON_NULL

			};//定义json元素的内容的类型

			struct Value
			{
				jsonobject*  value_object;
				jsonArray*  value_array;

				std::string* value_string;
				float value_number;
				bool  value_bool;

			};//定义内容（单位）的类型

		
			jsonElement() :type_(Type::JSON_NULL){}

			jsonElement(Type type):type_(type)
			{
				switch (type)
				{
					//以上从堆栈创建的对象都需要析构
				case Type::JSON_OBJECT:
					value_.value_object = new std::map<std::string,jsonElement*>();
					break;
				case Type::JSON_ARRAY:
					value_.value_array = new std::vector<jsonElement*> ();
					break;
				case Type::JSON_STRING:
					value_.value_string = new std::string(" ");
					break;
				case Type::JSON_BOOL:
					value_.value_bool = false;
					break;
				case Type::JSON_NUMBER:
					value_.value_number = 0;
					break;
				case Type::JSON_NULL:
					break;
				default:
					break;
				}
			}

			~jsonElement()
			{
				if (type_ == Type::JSON_OBJECT)
				{
					jsonobject* object = value_.value_object;
					for (auto& i : *object)
					{
						delete i.second;
					}
					delete object;
				}
				else if (type_ == Type::JSON_ARRAY)
				{
					jsonArray* array = value_.value_array;
					for (auto& j : *array)
					{
						delete j;
					}
					delete array;
				}
				else if (type_ == Type::JSON_STRING)
				{
					std::string* val = value_.value_string;
					delete val;
				}
			};

			jsonElement(jsonobject* value_object){value(value_object); }
			jsonElement(jsonArray* value_array) { value(value_array); }
			jsonElement(std::string* value_string) { value(value_string); }
			jsonElement(float value_number) { value(value_number); }
			jsonElement(bool value_bool) { value(value_bool); }
			

			jsonobject* Asobject()
			{
				if (type_ == Type::JSON_OBJECT)
				{
					return value_.value_object;
				}
				Error("Type of jsonElement isnt jsonobject");
			}
			jsonArray* Asarray()
			{
				if (type_ == Type::JSON_ARRAY)
				{
					return value_.value_array;
				}
				Error("Type of jsonElement isnt jsonarray");
			}
			std::string Asstring()
			{
				if (type_ == Type::JSON_STRING)
				{
					return *(value_.value_string);
				}
				Error("Type of jsonElement isnt jsonstring");
			}
			float AsNumber()
			{
				if (type_ == Type::JSON_NUMBER)
				{
					return value_.value_number;
				}
				Error("Type of jsonElement isnt jsonnumber");
			}
			bool AsBool()
			{
				if (type_ == Type::JSON_BOOL)
				{
					return value_.value_bool;
				}
				Error("Type of jsonElement isnt jsonbool");
			}
			/// <summary>
			/// 以上为对外的访问接口
			/// </summary>
			/// <param name="value_object"></param>

			Type type() { return type_; }

			void value(jsonobject* value_object)
			{
				type_ = Type::JSON_OBJECT;
				value_.value_object = value_object;
			}
			void value(jsonArray* value_array)
			{
				type_ = Type::JSON_ARRAY;
				value_.value_array = value_array;
			}
			void value(std::string* value_string)
			{
				type_ = Type::JSON_STRING;
				value_.value_string = value_string;
			}
			void value(float value_number)
			{
				type_ = Type::JSON_NUMBER;
				value_.value_number = value_number;
			}
			void value(bool value_bool)
			{
				type_ = Type::JSON_BOOL;
				value_.value_bool = value_bool;
			}

			std::string Dumps() //将 jsonElement ->string
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
			friend std::ostream& operator << (std::ostream& os, const jsonobject& object);
			

			friend std::ostream& operator << (std::ostream& os, const jsonArray& array);
			
			

		private:
			Type type_;
			Value value_;

		};	
	}
}