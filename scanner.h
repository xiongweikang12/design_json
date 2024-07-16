#pragma once
#include <string>

namespace civitasv {
	namespace json
	{

		class Scanner {
		public:
			Scanner(std::string sorce) :source(sorce), current(0),prev_pos(0),
				value_number(0){}
			//���캯��

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
			//�ӵ�ǰλ��ɨ����һ����������һ��Tokentype
			float get_value_number();
			std::string get_value_string();
			//˽�г�Ա����ӿ�


		private:
			bool IsAtEnd(); //
			char Advance(); //��ȡ��һ���ַ�
			void scannumber();
			void scanstring();
			void scantrue();
			void scanfalse();
			void scannull();
			char Peek();
			bool isDigit(char c);
			char Peeknext();
			



			
			std::string source;  /// json source,��ǰ���ַ���
			size_t current; ///current handling position ��ǰ������λ��
			size_t prev_pos; /// prev handling position

			std::string value_string;
			float value_number;
			///�����ṩ���ֽӿ�

		};



	}
}