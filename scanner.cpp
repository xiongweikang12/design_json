#include "scanner.h"
#include "Error.h"

namespace civitasv {
	namespace json
	{
		char Scanner::Peek()
		{
			if (IsAtEnd())
			{	return '\0';}
			return source[current];
		}

		bool Scanner::isDigit(char c)
		{
			return c>='0'&& c<='9';
		}

		char Scanner::Peeknext()
		{
			if (current + 1 >= source.size())
			{
				return '\0';
			}
			return source[current + 1];
		}

		void Scanner::rollback()
		{
			current = prev_pos;
		}


		bool Scanner::IsAtEnd()
		{
			return current >= source.size();
		}

		char Scanner::Advance()
		{
			return source[current++];
		}

		void Scanner::scannumber()
		{
			///{"size":120}
			size_t pos = current;
			while (isDigit(Peek()))
			{
				Advance();
			}//不是数字时退出

			//	120.22
			if (Peek() == '.' && isDigit(Peeknext()))
			{
				Advance();
				while (isDigit(Peek()))
				{
					Advance();
				}
			}
			value_number = std::atof(source.substr(pos, current - pos).c_str());

		}

		void Scanner::scanstring()
		{
			///{"test"}
			size_t pos = current;
			while (Peek()!='\"' && !IsAtEnd())
			{
				Advance();
			}
			if (IsAtEnd())
			{
				Error("scan string_end error");
			}
			Advance();
			value_string = source.substr(pos, current - pos - 1);
		}

		void Scanner::scantrue()
		{
			if (source.compare(current, 3, "rue") == 0)
			{
				current += 3;
			}
			else
			{
				Error("scan true error");
			}

		}

		void Scanner::scanfalse()
		{
			if (source.compare(current, 4, "alse") == 0)
			{
				current += 4;
			}
			else
			{
				Error("scan false error");
			}
		}

		void Scanner::scannull()
		{
			if (source.compare(current, 3, "ull") == 0)
			{
				current += 3;
			}
			else
			{
				Error("scan null error");
			}
		}

		float Scanner::get_value_number() { return value_number; }
		std::string Scanner::get_value_string() { return value_string; }







		Scanner::jsonTokentype Scanner::Scan()
		{
			if (IsAtEnd())
			{
				return jsonTokentype::END_OF_SOURCE;
			}
			prev_pos = current;

			char c = Advance();
			switch (c)
			{
			case '{':
				return jsonTokentype::BEGIN_OBJECT;
			case '}':
				return jsonTokentype::END_OBJECT;
			case '[':
				return jsonTokentype::BEGIN_ARRAY;
			case ']':
				return jsonTokentype::END_ARRAY;
			case ',':
				return jsonTokentype::VALUE_SEPRATOR;
			case ':':
				return jsonTokentype::NAME_SEPRATOR;
			case 't':
				scantrue();
				return jsonTokentype::LITERAL_TRUE;
			case 'f':
				scanfalse();
				return jsonTokentype::LITERAL_FALSE;
			case 'n':
				return jsonTokentype::LITERAL_NULL;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				return Scan();
			case '\"':
				scanstring();
				return jsonTokentype::VALUE_STRING;
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				scannumber();
				return jsonTokentype::VALUE_NUMBER;
			default:
				Error("Unsupported Tokentype" + c);
			}
		}

	}
}