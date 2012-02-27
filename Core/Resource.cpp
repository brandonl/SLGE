#include "Resource.h"
#include <iostream>

using namespace slge;

Resource::~Resource() { std::cout << "Deleting resource\n"; };
