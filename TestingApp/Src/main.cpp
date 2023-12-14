#include "../Include/include.h"
RESULT DoSomething() {RETURN(Failed); }

int main()
{
	Internal::ErrorHandler::Get()->PrintOnPost(true);
	WARN("This is a classic warning!");

	INFO("now this should work too!");
	Internal::ErrorHandler::Get()->SelfWarning(false);
	INFO("now this should work too!");


}