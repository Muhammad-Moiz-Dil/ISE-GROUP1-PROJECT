#include "core/lender.h"
#include <iostream>

using std::cout;
using std::endl;

/* [LENDER.EXE COMPILATION]
g++ -I..\..\logs\include ^
lender_main.cpp ^
core\lender.cpp ^
core\application.cpp ^
helpers\utils.cpp ^
helpers\error_handling.cpp ^
helpers\ui_display.cpp ^
-o lender.exe
*/

int main()
{
    // Create lender manager with path to applications file
    LenderManager manager("output/applications.txt");

    // Run the lender portal
    runLenderPortal(manager);

    return 0;
}