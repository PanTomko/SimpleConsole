#pragma once

#ifdef SIMPLECONSOLE_EXPORTS
#define DllS __declspec(dllexport)
#else
#define DllS __declspec(dllimport)
#endif

class SingleTest {
public:

	int a = 90;
	__declspec(dllexport) void printD();

	DllS static SingleTest *getInstance();
	~SingleTest();

private:
	SingleTest();
	
};

