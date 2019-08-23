#include <iostream>
#include "INIParser.h"

using namespace std;
using namespace cppiniparser;

void TestWrite()
{
	INIConfig config;
    config.AddSection("foo");
    config.AddOption("foo", "key1", "value1");
    config.AddOption("foo", "key2", "value2");
    config.AddOption("foo", "key3", "value3");

    config.AddSection("bar");
    config.AddOption("bar", "key4", "value4");
    config.AddOption("bar", "key5", "value5");
    
    config.AddSection("type");
    config.AddOption("type", "str", "Hello World!");
    config.AddOption("type", "bool", "true"); // true, yes, 1; false, no, 0
    config.AddOption("type", "int", "123");
    config.AddOption("type", "double", "3.14");

    INIParser::Write(config, "config.ini");
}

void TestRead()
{
    INIConfig config;
	INIParser::Read(config, "config.ini");
    vector<string> sections = config.Sections();
    vector<string>::const_iterator s = sections.begin();
    for (; s != sections.end(); ++s)
	{
        if (*s == "type")
        	break;
        cout << "Section: " << *s << endl;
        vector<string> opts = config.Options(*s);
        vector<string>::const_iterator o = opts.begin();
        for (; o != opts.end(); ++o)
		{
            string value = config.Get(*s, *o);
            cout << "   - " << *o << "=" << value << endl;
        }
        cout << endl;
    }
    
    string v1 = config.Get("type", "str");
    bool v2 = config.GetBoolean("type", "bool");
    int v3 = config.GetInteger("type", "int");
    double v4 = config.GetReal("type", "double");
    
    cout << "Section: " << *s << endl;
    cout << "   - str=" << v1 << endl;
    cout << "   - bool=" << v2 << endl;
    cout << "   - int=" << v3 << endl;
    cout << "   - double=" << v4 << endl;
}

int main()
{
	TestWrite();
	TestRead();
	
	return 0;
}
