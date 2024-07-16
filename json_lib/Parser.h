#pragma once

#include "scanner.h"
#include "jsonElement.h"
# define Json_API _declspec(dllexport)
namespace civitasv
{
	namespace json
	{
		Json_API class Parser
		{
		public:
			Parser(Scanner scanner) :scanner_(scanner){};
			jsonElement* parse();
			
		private:
			jsonobject* Parserobject();
			jsonArray* Parserarray();
			Scanner scanner_;

		};
	}
}