#pragma once
#include <string>

namespace civitasv {
	namespace json
	{

		class Scanner {
		public:
			Scanner(std::string sorce) :source(sorce), current(0),prev_pos(0),
				value_number(0){}
			//构造函数

			void rollback();

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
			jsonTokentype Scan(); 
			//从当前位置扫描下一个，返回下一个Tokentype
			float get_value_number();
			std::string get_value_string();
			//私有成员对外接口


		private:
			bool IsAtEnd(); //
			char Advance(); //获取下一个字符
			void scannumber();
			void scanstring();
			void scantrue();
			void scanfalse();
			void scannull();
			char Peek();
			bool isDigit(char c);
			char Peeknext();
			



			
			std::string source;  /// json source,当前的字符串
			size_t current; ///current handling position 当前处理到的位置
			size_t prev_pos; /// prev handling position

			std::string value_string;
			float value_number;
			///对外提供呈现接口

		};



	}
}