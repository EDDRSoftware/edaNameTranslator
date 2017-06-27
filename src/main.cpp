/*
 * MIT License
 *
 * Copyright (c) 2017 EDDR Software, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Changes:
 * 2017-01-01: First & Last Name: What you did.
 * 2017-06-22: Thomas Burri: Initial contribution.
 *
 */

#include <stdlib.h>

#include <iostream>

#include "edaNameTranslator.h"

using namespace std;
using namespace edant;

// ****************************************************************************
// main()
//
// This is the top level function that tests the parser.
// ****************************************************************************
int main(int argc, char *argv[])
{
    const char *inputBusCDBA = "bus<1:2>";
    edaCDBA busCDBA(inputBusCDBA);
    const char *inputBusOA = "bus[1:2]";
    edaOA busOA(inputBusOA);
    
    cout << "input CDBA:  " << inputBusCDBA << endl;
    cout << "input OA:    " << inputBusOA   << endl;

    bool same = (busCDBA==busOA);
    cout << "same: " << (int)same << endl;
    cout << "CDBA to OA:   " << busCDBA.toOA()   << endl;
    cout << "CDBA to CDBA: " << busCDBA.toCDBA() << endl;
    cout << "CDBA to VHDL: " << busCDBA.toVHDL() << endl;

    const char *inputHierarchy = "lib/cell/view";
    edaOA heirOA(inputHierarchy);

    cout << "OA heirarchy:          " << heirOA.toOA() << endl;
    cout << "OA to CDBA heirarchy:  " << heirOA.toCDBA() << endl;
    cout << "OA to SPICE heirarchy: " << heirOA.toSPICE() << endl;
    cout << "OA to VHDL heirarchy:  " << heirOA.toVHDL() << endl;

    return 0;
}

