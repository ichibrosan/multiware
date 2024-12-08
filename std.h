////////////////////////////////////////////////////////////////////////
// /home/doug/CLionProjects/multiware/std.h 2024/12/05 dwg - created  //
// Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.     //
///////////////////////////////////////////////////////////////////////
// The purpose of this file is to emulate the functionality if the   //
// "import std;" line which is not yet supported in our devo tools.  //
// Each time a new standard header becomes required it should be     //
// here so that modules having "#include "std.h" have the effect of  //
// having "import std;"                                              //
///////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_STD_H
#define MULTIWARE_STD_H

#include <cassert>
#include <iostream>
#include <cstring>
#include <ctime>

#endif //MULTIWARE_STD_H
