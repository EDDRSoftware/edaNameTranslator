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

#include "edaNameTranslator.h"

#include <string.h>

#include <iostream>

using namespace std;

namespace edant
{
    #define SPACE           "~SP"   //space
    #define SOLIDUS         "~SO"   //forward slash
    #define SOLIDUS_REV     "~SR"   //back slash
    #define BRACKET_OPEN    "~BO"   //bracket open
    #define BRACKET_CLOSE   "~BC"   //bracket close
    #define HIERARCHY       "~HI"   //hierarchy

    edaNameTranslator::edaNameTranslator()
        : type(UTF8)
    {
        inConv = iconv_open("UTF-8", "ASCII");
        if(inConv==reinterpret_cast<iconv_t>(-1)){
            throw -1;
        }
        
        outConv = iconv_open("ASCII", "UTF-8");
        if(outConv==reinterpret_cast<iconv_t>(-1)){
            throw -2;
        }
    }

    edaNameTranslator::~edaNameTranslator()
    {
        iconv_close(inConv);   
        iconv_close(outConv);   
    }

    bool edaNameTranslator::operator==(edaNameTranslator& other)
    {
        string first, second;
        this->outputUTF8(&first);
        other.outputUTF8(&second);
        if(first==second)
            return true;
        return false;
    }

    int edaNameTranslator::convert(const string &inStr, const Syntax inSyntax, string *outStr, const Syntax outSyntax)
    {
        switch(inSyntax){
            case UTF8:      inputUTF8(inStr);        break;
            case CDBA:      inputCDBA(inStr);        break;
            case DEF:       inputDEF(inStr);         break;
            case EDIF:      inputEDIF(inStr);        break;
            case LEF:       inputLEF(inStr);         break;
            case OA:        inputOA(inStr);          break;
            case SPEF:      inputSPEF(inStr);        break;
            case SPF:       inputSPF(inStr);         break;
            case SPICE:     inputSPICE(inStr);       break;
            case UNIX:      inputUNIX(inStr);        break;
            case VERILOG:   inputVERILOG(inStr);     break;
            case VHDL:      inputVHDL(inStr);        break;
            case WINDOWS:   inputWINDOWS(inStr);     break;
            default:        return -1;               break; 
        }

        switch(outSyntax){
            case UTF8:      outputUTF8(outStr);      break;
            case CDBA:      outputCDBA(outStr);      break;
            case DEF:       outputDEF(outStr);       break;
            case EDIF:      outputEDIF(outStr);      break;
            case LEF:       outputLEF(outStr);       break;
            case OA:        outputOA(outStr);        break;
            case SPEF:      outputSPEF(outStr);      break;
            case SPF:       outputSPF(outStr);       break;
            case SPICE:     outputSPICE(outStr);     break;
            case UNIX:      outputUNIX(outStr);      break;
            case VERILOG:   outputVERILOG(outStr);   break;
            case VHDL:      outputVHDL(outStr);      break;
            case WINDOWS:   outputWINDOWS(outStr);   break;
            default:        return -2;               break;
        }

        return 0;
    }
 
    void edaNameTranslator::inputUTF8(const string &inStr)
    {
        size_t size = inStr.size();
        size_t outSize = size*2+2;  
        char outBuffer[outSize];
        memset(&outBuffer, 0, outSize);
        char *outPtr = &outBuffer[0];
        char *inPtr = (char*)inStr.c_str();
        int retVal;

        retVal = iconv(inConv, &inPtr, &size, &outPtr, &outSize);
        if(retVal==-1){
            throw 2;
        }

        buffer.write((char*)outBuffer, outSize);
    }

    void edaNameTranslator::outputUTF8(string *outStr)
    {
        *outStr = buffer.str();
    }

    static void replace(string *in, const char *find, const char *replace)
    {
        size_t pos = 0;
        do{
            pos = in->find(find);
            if(pos!=string::npos){
                in->replace(pos, strlen(find), replace);
            }
        } while(pos!=string::npos);
    }

    void edaNameTranslator::inputCDBA(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE); 
        replace(&in, "`", HIERARCHY); 
        replace(&in, "#2f", SOLIDUS); 
        replace(&in, "#5c", SOLIDUS_REV); 
        replace(&in, "<", BRACKET_OPEN); 
        replace(&in, ">", BRACKET_CLOSE); 
        inputUTF8(in);
    }

    void edaNameTranslator::outputCDBA(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, "`");
        replace(&out, SOLIDUS, "#2f");
        replace(&out, SOLIDUS_REV, "#5c");
        replace(&out, BRACKET_OPEN, "<");
        replace(&out, BRACKET_CLOSE, ">");
        *outStr = out;
    }

    void edaNameTranslator::inputDEF(const string &inStr)
    {
        string in = inStr;
        replace(&in, "%20", SPACE);
        replace(&in, "\\/", SOLIDUS); 
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "/", HIERARCHY);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputDEF(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "%20");
        replace(&out, SOLIDUS, "\\/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, HIERARCHY, "/");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputEDIF(const string &inStr)
    {
        string in = inStr;
        inputUTF8(in);
    }

    void edaNameTranslator::outputEDIF(string *outStr)
    {
        string out;
        outputUTF8(&out);
        *outStr = out;
    }

    void edaNameTranslator::inputLEF(const string &inStr)
    {
        string in = inStr;
        replace(&in, "%20", SPACE);
        replace(&in, "\\/", SOLIDUS); 
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "/", HIERARCHY);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputLEF(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "%20");
        replace(&out, SOLIDUS, "\\/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, HIERARCHY, "/");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputOA(const string &inStr)
    {
        string in = inStr;
        replace(&in, " ", SPACE);
        replace(&in, "/", HIERARCHY); 
        replace(&in, "#2f", SOLIDUS); 
        replace(&in, "\\", SOLIDUS_REV);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputOA(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, " ");
        replace(&out, HIERARCHY, "/");
        replace(&out, SOLIDUS, "#2f");
        replace(&out, SOLIDUS_REV, "\\");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputSPEF(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, "\\/", SOLIDUS);
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "/", HIERARCHY);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputSPEF(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, SOLIDUS, "\\/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, HIERARCHY, "/");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputSPF(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, "\\/", SOLIDUS);
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "/", HIERARCHY);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputSPF(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, SOLIDUS, "\\/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, HIERARCHY, "/");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputSPICE(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, ".", HIERARCHY);
        replace(&in, "/", SOLIDUS);
        replace(&in, "#5c", SOLIDUS_REV);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputSPICE(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, ".");
        replace(&out, SOLIDUS, "/");
        replace(&out, SOLIDUS_REV, "#5c");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputUNIX(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, "/", HIERARCHY);
        replace(&in, "#2f", SOLIDUS);
        replace(&in, "#5c", SOLIDUS_REV);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputUNIX(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, "/");
        replace(&out, SOLIDUS, "#2f");
        replace(&out, SOLIDUS_REV, "#5c");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputVERILOG(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, ".", HIERARCHY);
        replace(&in, "\\/", SOLIDUS);
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputVERILOG(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, ".");
        replace(&out, SOLIDUS, "\\/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }

    void edaNameTranslator::inputVHDL(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, ":", HIERARCHY);
        replace(&in, "/", SOLIDUS);
        replace(&in, "\\\\", SOLIDUS_REV);
        replace(&in, "(", BRACKET_OPEN);
        replace(&in, ")", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputVHDL(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, ":");
        replace(&out, SOLIDUS, "/");
        replace(&out, SOLIDUS_REV, "\\\\");
        replace(&out, BRACKET_OPEN, "(");
        replace(&out, BRACKET_CLOSE, ")");
        *outStr = out;
    }

    void edaNameTranslator::inputWINDOWS(const string &inStr)
    {
        string in = inStr;
        replace(&in, "#20", SPACE);
        replace(&in, "\\", HIERARCHY);
        replace(&in, "#2f", SOLIDUS);
        replace(&in, "#5c", SOLIDUS_REV);
        replace(&in, "[", BRACKET_OPEN);
        replace(&in, "]", BRACKET_CLOSE);
        inputUTF8(in);
    }

    void edaNameTranslator::outputWINDOWS(string *outStr)
    {
        string out;
        outputUTF8(&out);
        replace(&out, SPACE, "#20");
        replace(&out, HIERARCHY, "\\");
        replace(&out, SOLIDUS, "#2f");
        replace(&out, SOLIDUS_REV, "#5c");
        replace(&out, BRACKET_OPEN, "[");
        replace(&out, BRACKET_CLOSE, "]");
        *outStr = out;
    }
    const char *edaNameTranslator::toUTF8()
    {
        string out;
        outputUTF8(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toCDBA()
    {
        string out;
        outputCDBA(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toDEF()
    {
        string out;
        outputDEF(&out);
        return out.c_str();
    }
    
    const char *edaNameTranslator::toEDIF()
    {
        string out;
        outputEDIF(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toLEF()
    {
        string out;
        outputLEF(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toOA()
    {
        string out;
        outputOA(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toSPEF()
    {
        string out;
        outputSPEF(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toSPF()
    {
        string out;
        outputSPF(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toSPICE()
    {
        string out;
        outputSPICE(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toUNIX()
    {
        string out;
        outputUNIX(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toVERILOG()
    {
        string out;
        outputVERILOG(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toVHDL()
    {
        string out;
        outputVHDL(&out);
        return out.c_str();
    }

    const char *edaNameTranslator::toWINDOWS()
    {
        string out;
        outputWINDOWS(&out);
        return out.c_str();
    }

    edaUTF8::edaUTF8()
    {
    }

    edaUTF8::edaUTF8(const char *str)
    {
        inputUTF8(str);
    }

    edaCDBA::edaCDBA()
    {
    }

    edaCDBA::edaCDBA(const char *str)
    {
        inputCDBA(str);
    }

    edaDEF::edaDEF()
    {
    }

    edaDEF::edaDEF(const char *str)
    {
        inputDEF(str);
    }

    edaEDIF::edaEDIF()
    {
    }

    edaEDIF::edaEDIF(const char *str)
    {
        inputEDIF(str);
    }

    edaLEF::edaLEF()
    {
    }

    edaLEF::edaLEF(const char *str)
    {
        inputLEF(str);
    }

    edaOA::edaOA()
    {
    }

    edaOA::edaOA(const char *str)
    {
        inputOA(str);
    }

    edaSPEF::edaSPEF()
    {
    }

    edaSPEF::edaSPEF(const char *str)
    {
        inputSPEF(str);
    }

    edaSPF::edaSPF()
    {
    }

    edaSPF::edaSPF(const char *str)
    {
        inputSPF(str);
    }

    edaSPICE::edaSPICE()
    {
    }

    edaSPICE::edaSPICE(const char *str)
    {
        inputSPICE(str);
    }

    edaUNIX::edaUNIX()
    {
    }

    edaUNIX::edaUNIX(const char *str)
    {
        inputUNIX(str);
    }

    edaVERILOG::edaVERILOG()
    {
    }

    edaVERILOG::edaVERILOG(const char *str)
    {
        inputVERILOG(str);
    }

    edaVHDL::edaVHDL()
    {
    }

    edaVHDL::edaVHDL(const char *str)
    {
        inputVHDL(str);
    }

    edaWINDOWS::edaWINDOWS()
    {
    }

    edaWINDOWS::edaWINDOWS(const char *str)
    {
        inputWINDOWS(str);
    }



} // End namespace edant
