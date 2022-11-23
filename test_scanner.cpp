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