// StaticLib1.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <string.h>
#include <array>
///#include "comutil.h"
#include <vector>
//#include "atlcomcli.h"
using namespace std;



class SimpleAdder
{
public:
	int Add(int* a, int* b)
	{
		return( *a + *b);
	}

	int Add()
	{
		return(*a + *b);
	}

	SimpleAdder()
	{

	}

	SimpleAdder(int x,int y)
	{
		// Issue, memory leak not detected
		a = new int(x);
		// Issue, memory leak not detected
		b = new int(y);	
	}

	~SimpleAdder()
	{
		/*if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
		if (b != nullptr)
		{
			delete b;
			b = nullptr;
		}*/
	}

private:
	int* a = nullptr;
	int* b = nullptr;
};

static int Add(int* p1, int* p2)
{
	int sum = 0;

	sum = *p1 + *p2;

	return sum;
}

// TODO: This is an example of a library function
void fnStaticLib1()
{

	char* temp = new char[100];	
#ifdef _WIN32
	strcpy_s(temp, 100, "Hello from StaticLib1!");
#else
	strncpy(temp, "Hello from StaticLib1!", 99);
	temp[99] = '\0'; // Ensure null termination
#endif
	// resource leak

	char x[4];
	const char* y = "abcddfdf";
	strcpy(x, y); // buffer overflow


	char a[4];
	// No issue, This code declares a local variable, which is an array allocated on the stack. Stack memory is managed automatically.
	char temp1[26] = "abcdefghijklmnopqrstuvwxy";

	// Issue, buffer overflow not detected
	strcpy(a, temp1); // buffer overflow

	//BSTR bstr = SysAllocString(L"Hello from StaticLib1!"); // resource leak	
	
	
	// Issue, memory leak not detected at return statement, only temp are mentioned
	int* p1 = new int(10);
	int* p2 = nullptr;

	// Issue, memory leak not detected
	SimpleAdder*	adder = new SimpleAdder();
	int result = adder->Add(p1, p2); // dereferncing a null pointer variable
	int sum = Add(p1, p2);

	// Issue, memory leak not detected
	SimpleAdder* adder1 = new SimpleAdder(9,9);
	adder1->Add();

	/*std::vector<CComBSTR> vec;
	char token[256] = "fksdfdshfhdfdbf";
	BSTR bstrToken = _com_util::ConvertStringToBSTR(token);
	vec.push_back(bstrToken);*/

	return;

}



