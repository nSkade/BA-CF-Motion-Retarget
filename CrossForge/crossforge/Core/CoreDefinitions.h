/*****************************************************************************\
*                                                                           *
* File(s): CoreDefinitions.h                                                *
*                                                                           *
* Content: API definition and important includes.                           *
*                                                                           *
*                                                                           *
*                                                                           *
* Author(s): Tom Uhlmann                                                    *
*                                                                           *
*                                                                           *
* The file(s) mentioned above are provided as is under the terms of the     *
* MIT License without any warranty or guaranty to work properly.            *
* For additional license, copyright and contact/support issues see the      *
* supplied documentation.                                                   *
*                                                                           *
\****************************************************************************/

#include <inttypes.h>

#ifdef CFORGE_EXPORTS
#define CFORGE_API __declspec(dllexport)
#elif defined __WINDLL
#define CFORGE_API __declspec(dllimport)
#else
#define CFORGE_API
#endif