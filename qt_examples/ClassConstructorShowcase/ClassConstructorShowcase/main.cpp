#include <iostream>
#include "vec3.h"

using std::cout;
using std::endl;

int main()
{
    // Test-case for different constructors
    cout << ">>> initializes v1(1,1,1)" << endl;
    vec3 v1(1,1,1);

    cout << ">>> initializes v2(2,2,2)" << endl;
    vec3 v2(2,2,2);

    cout << ">>> initializes v3 then v4" << endl;
    vec3 v3, v4;

    cout << ">>> v5 = v2" << endl;
    vec3 v5 = v2;

    cout << ">>> v3 = v1 + v2" << endl;
    v3 = v1 + v2;

    cout << ">>> Destroys objects" << endl;

    return 0;
}
