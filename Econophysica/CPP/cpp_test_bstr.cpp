#include <cstdlib>
#include <cstdio>
#include <cstring>

//I defined this struct as it was described
struct BSTR
{
	unsigned int length;
	wchar_t* pwstring;
};

//I decided to use BSTR* pbstr to avoid problems with creating an allocated pointer in return block. Just to simplify debugging
void Alloc(BSTR* pbstr, const char* buf)
{
	//In case of *nix (32 bits for unicode character or non-default windows locale)	
	pbstr->length = (unsigned)strlen(buf) * sizeof(wchar_t)/sizeof(char);
	//I used new-delete instead of malloc-free only just to notice that this is c++, not pure c code
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
