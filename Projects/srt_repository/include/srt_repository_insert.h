////////////////////////////////////////////////////////////////////////////////
// DESCRIPTION
//       LogFilter pipeline I/O routine
//       GRID event report
//       Release: V0.2 24/feb/2006
//       Contributors: A.A., A.G., S.V., S.M.
//       Author: Alessio Trois (IASF-Milano)
//		Alberto Pellizzoni
//
// INPUT
//       TBD
//
// OUTPUT
//       TBD
//
//
// FILE HISTORY
//       25/Apr/2005
//       28/May/2008
//                      First release: V1.0
//                      Authors:       Alessio Trois (IASF-Milano)
// NOTICE
//       Any information contained in this software
//       is property of the SRT TEAM and is strictly
//       private and confidential.
//       All rights reserved.
////////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include "fitsio.h"
#include <unistd.h>
#include <ctype.h>
#include <cstring>
// #include <pil.h>
#include <iostream>
// #include "GridUtilities.h"
// #include <alikeQuat.h>
using namespace std;
const char * version = "version 0.0 17/10/2016";

