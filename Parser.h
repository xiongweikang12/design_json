#pragma once

#include "scanner.h"
#include "jsonElement.h"

namespace civitasv
{
	namespace json
	{
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
	}
}