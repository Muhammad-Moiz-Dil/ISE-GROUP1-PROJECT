#include "../../logs/include/lender.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    // Create lender manager with path to applications file
    LenderManager manager("output/applications.txt");

    // Run the lender portal
    runLenderPortal(manager);

    return 0;
}