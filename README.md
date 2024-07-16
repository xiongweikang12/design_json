# design_json

<u>*基于c++的一个json解析器设计*</u>  :s

- scanner
用于对json字符串进行扫描主要是Scan方法对其成员变量进行操作分析
~~~ c
std::string source;  /// json source,当前的字符串
size_t current; ///current handling position 当前处理到的位置
size_t prev_pos; /// prev handling position

std::string value_string;
float value_number;
~~~
以及一系列成员函数,一个说明类型的枚举类对source进行扫描，改变current,pre_pos，赋值成员变量
~~~ c
private:
	bool IsAtEnd(); //
	char Advance(); //获取下一个字符
	void scannumber(); 
        //value_number = std::atof(source.substr(pos, current - pos).c_str());
        //substr表示赋值字串，也就是数值部分，c_str()生成一个char*指针 ，atof将字符串转化为浮点数
        //将扫描到的赋值给value_number
	void scanstring();
	void scantrue();
	void scanfalse();
	void scannull();
	char Peek();
	bool isDigit(char c);
	char Peeknext();
        //两个对外的get接口
	float Scanner::get_value_number() { return value_number; }
	std::string Scanner::get_value_string() { return value_string; }


    enum class jsonTokentype
    {
        BEGIN_OBJECT ,///<{
        END_OBJECT, ///< }
            
        VALUE_SEPRATOR, ///< ,
        NAME_SEPRATOR, ///< :
            
        VALUE_STRING ,///"STRING"
        VALUE_NUMBER, /// 1,2,2E10
            
        LITERAL_TRUE, //TRUE
        LITERAL_FALSE, //FLASE
        LITERAL_NULL, //NULL

        BEGIN_ARRAY, ///[
        END_ARRAY, /// ]

        END_OF_SOURCE ///<EOF

    };
~~~

- parser包含一个Scanner对象，
~~~ c

    class Parser
    {
    public:
        Parser(Scanner scanner) :scanner_(scanner){};
        jsonElement* parse();
        
    private:
        jsonobject* Parserobject();   
        jsonArray* Parserarray();
        Scanner scanner_;

    };
~~~

parse：：parser方法通过对scanner_成员变量 scan()的调用解析出jsonTokentype,通过条件选择进行处理,同时创建一个jsonElement 成员来接受

~~~ c
    jsonTokenkey token_key = scanner_.Scan();

    jsonElement* element = new jsonElement();

    //以下是定义在 jsonElement.h中的
    //对于object其结构是
    jsonobject = std::map<std::string, jsonElement*>;
    //对于objectarray其结构是
    jsonArray = std::vector<jsonElement*>;


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
			jsonobject* object = Parserobject();  // (*res)[key] = parse();  //相当于插入数据，其中的操作
            //函数里有对细分的解析，如：，，不是 jsonTokenkey::END_OBJECT不结束
			//获取一个json的对象 map<string,jsonElement>
			element->value(object);
			break;
		}
		case jsonTokenkey::BEGIN_ARRAY:
		{
			jsonArray* array = Parserarray(); //res->push_back(parse());同理不是jsonTokenkey::END_ARRAY不结束
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

//string ,number由scanner处理，jsonobject和jsonarray需要通过容器来完成，整体上json是一个大的jsonobject 及std::map<std::string, jsonElement*>;多个键值对的容器


~~~

- jsonElement 
通过在parser中创建jsonElement 对其赋值，返回
~~~C

    case jsonTokenkey::BEGIN_ARRAY:
		{
			jsonArray* array = Parserarray();
			element->value(array);
			break;
		}
    // jsonElement 对象中有关于其 value的各种重载 
    void value(std::string* value_string)
    {
	    type_ = Type::JSON_STRING;
	    value_.value_string = value_string;
    }

    Type type_; 成员变量 ，一个枚举类
    Value value_; 对应的值
~~~~

jsonElement中有一个dump方法是将jsonobject以字符串形式输出，及遍历一个set根据其Type来在输出流中添加东西，如 {}，[].
~~~ c
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
~~~

其中对于type为Type::JSON_OBJECT，Type::JSON_ARRAY其value类型是 set,vector,需要对其进行<<的操作符重载

~~~ c
std::ostream& operator<<(std::ostream& os, const jsonobject& object)
{
	os << "{";
	for (auto iter = object.begin(); iter != object.end(); iter++)
	{
		os << '\"' << iter->first << '\"' << ":" << iter->second->Dumps(); //其first为string 所以要加上“ ”的转义，second为josnElement所以需要调用Dumps
		if (iter != --object.end())
		{
			os << ",";
		}
	}
	os << "}";
	return os;
}
~~~

- 最后是一个测试用例
~~~ c
#include <iostream>

#include "Parser.h"

int main()
{
	using namespace civitasv::json;
	auto source= R"(
    {
      "name": "weikang",
      "university": "whu",
      "age": -22,
      "gender": "men",
      "isProgrammer": true,
      "skills": ["C++", "JS/TS", "Java"]
    }
  )";

    Scanner scanner(source);
    Parser parser(scanner);

    jsonElement* res = parser.parse();
    std::cout << res->Dumps() << "\n";
    delete res;
    

}
~~~




