#include "Parser.h"
#include "Error.h"


namespace civitasv {
	namespace json
	{
		using jsonTokenkey = Scanner::jsonTokentype;
		jsonElement* Parser::parse()
		{
			jsonElement* element = new jsonElement();
			jsonTokenkey token_key = scanner_.Scan();
			if (token_key != jsonTokenkey::END_OBJECT) 
			{
				switch (token_key)
				{
				case jsonTokenkey::END_OF_SOURCE: //结束
				{
					break;
				}
				case jsonTokenkey::BEGIN_OBJECT: //开始解析对象
				{
					jsonobject* object = Parserobject();
					//获取一个json的对象 map<string,jsonElement>
					element->value(object);
					break;
				}
				case jsonTokenkey::BEGIN_ARRAY:
				{
					jsonArray* array = Parserarray();
					element->value(array);
					break;
				}
				case jsonTokenkey::VALUE_STRING:
				{
					std::string* val = new std::string(scanner_.get_value_string());
					element->value(val);
					break;
				}
				case jsonTokenkey::VALUE_NUMBER:
				{
					float val = scanner_.get_value_number();
					element->value(val);
					break;
				}
				case jsonTokenkey::LITERAL_TRUE:
				{
					element->value(true);
					break;
				}
				case jsonTokenkey::LITERAL_FALSE:
				{
					element->value(false);
					break;
				}
				case jsonTokenkey::LITERAL_NULL:
				{
					break;
				}
				default:
					break;
				}
			}
			return element;

		}

		jsonobject* Parser::Parserobject()
		{
			jsonobject* res = new jsonobject();
			jsonTokenkey next = scanner_.Scan();
			if (next == jsonTokenkey::END_OBJECT)
			{
				return res;
			}
			scanner_.rollback(); //退后一步，判断不是END_OBJECT 回退
			while (true)
			{
				next = scanner_.Scan(); //返回jsonTokenkey同时,处理对应的scanstring()
				if (next != jsonTokenkey::VALUE_STRING)
				{
					Error("key must be string");
				}
				std::string key = scanner_.get_value_string(); //Scanner的value_string对外get接口
				next = scanner_.Scan();
				if (next != jsonTokenkey::NAME_SEPRATOR)
				{
					Error("key between and value must be :");
				}
				(*res)[key] = parse();  //相当于插入数据
				next = scanner_.Scan();
				if (next == jsonTokenkey::END_OBJECT)
				{
					break;
				}
				if (next != jsonTokenkey::VALUE_SEPRATOR)
				{
					Error("Expected ','!");
				}
			}
			return res;

		}

		jsonArray* Parser::Parserarray()
		{
			jsonArray* res = new jsonArray();
			jsonTokenkey next = scanner_.Scan();
			if (next == jsonTokenkey::END_ARRAY)
			{
				return res;
			}
			scanner_.rollback();

			while (true)
			{
				res->push_back(parse());
				next = scanner_.Scan();
				if (next == jsonTokenkey::END_ARRAY)
				{
					break;
				}
				if (next == jsonTokenkey::VALUE_SEPRATOR)
				{
					Error("expected ,");
				}
			}
			return res;
		}
	}
}