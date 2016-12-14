#include <cstdlib>
#include <cstdio>
#include <cstring>


struct BSTR
{
	unsigned int length;
	wchar_t* pwstring;
};

void Alloc(BSTR* pbstr, const char* buf)
{
	pbstr->length = (unsigned)strlen(buf) * sizeof(wchar_t)/sizeof(char);
	pbstr->pwstring = new wchar_t(pbstr->length);
	mbstowcs(pbstr->pwstring, buf, strlen(buf));
}

void Free(BSTR* pbstr)
{
	pbstr->length = 0;
	delete pbstr->pwstring;
}

int main()
{
	BSTR* bstring = new BSTR();
	Alloc(bstring, "Text");
	Free(bstring);    
	return 0;
}
