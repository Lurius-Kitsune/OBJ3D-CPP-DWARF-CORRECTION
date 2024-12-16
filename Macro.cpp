#include "Macro.h"

void ChangeEncoding()
{
#ifdef UTF8
	#undef UTF8
#else 
	#define UTF8
#endif // UTF8
}
