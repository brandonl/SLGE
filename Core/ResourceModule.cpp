#include "ResourceModule.h"
#include <cstdio>

using namespace slge;

Resources *Resources::instance = nullptr;

Resources::Resources()
{
	if( instance != nullptr )
		printf( "Only one Resource module allowed.\n" );

	instance = this;
	workingDirectory =  "../../Resources/";
}