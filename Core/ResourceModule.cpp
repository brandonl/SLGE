#include "ResourceModule.h"
#include <iostream>
#include "Resource.h"

using namespace slge;

Resources *Resources::instance = NULL;

Resources::Resources()
{
	if( instance != NULL )
		std::cerr << "Only one Resource module allowed.\n";;

	instance = this;
	workingDirectory =  "../../Resources/";
}