#pragma once

#include <iostream>
#include <stdlib.h>

#ifdef DEBUG
	//defines
	#define if_d(x) if(x)

	//includes

// !DEBUG
#else
	//defines
	#define if_d(x) if(false)

	//includes
#endif // DEBUG

//general includes
#include "../Src/Error/Error.h"