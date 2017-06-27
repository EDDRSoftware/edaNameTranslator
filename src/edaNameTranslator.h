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

#ifndef EDANAMETRANSLATOR_H_
#define EDANAMETRANSLATOR_H_

#include <iconv.h>
#include <sstream>

namespace edant
{

    enum Syntax {
        UTF8    = 0,
        CDBA,
        DEF,
        EDIF,
        LEF,
        OA,
        SPEF,
        SPF,
        SPICE,
        UNIX,
        VERILOG,
        VHDL,
        WINDOWS
    };

    enum CaseSensitivity {
        lowerCase = 0,
        insensitive,
        sensitive
    }; 
   
    class edaNameTranslator
    {
    public:
        edaNameTranslator();
        virtual ~edaNameTranslator();

        int convert(const std::string &inStr, const Syntax inSyntax, std::string *outStr, const Syntax outSyntax);

        void inputUTF8(const std::string &inStr);
        void inputCDBA(const std::string &inStr);
        void inputDEF(const std::string &inStr);
        void inputEDIF(const std::string &inStr);
        void inputLEF(const std::string &inStr);
        void inputOA(const std::string &inStr);
        void inputSPEF(const std::string &inStr);
        void inputSPF(const std::string &inStr);
        void inputSPICE(const std::string &inStr);
        void inputUNIX(const std::string &inStr);
        void inputVERILOG(const std::string &inStr);
        void inputVHDL(const std::string &inStr);
        void inputWINDOWS(const std::string &inStr);

        void outputUTF8(std::string *outStr);
        void outputCDBA(std::string *outStr);
        void outputDEF(std::string *outStr);
        void outputEDIF(std::string *outStr);
        void outputLEF(std::string *outStr);
        void outputOA(std::string *outStr);
        void outputSPEF(std::string *outStr);
        void outputSPF(std::string *outStr);
        void outputSPICE(std::string *outStr);
        void outputUNIX(std::string *outStr);
        void outputVERILOG(std::string *outStr);
        void outputVHDL(std::string *outStr);
        void outputWINDOWS(std::string *outStr);

        const char *toUTF8();
        const char *toCDBA();
        const char *toDEF();
        const char *toEDIF();
        const char *toLEF();
        const char *toOA();
        const char *toSPEF();
        const char *toSPF();
        const char *toSPICE();
        const char *toUNIX();
        const char *toVERILOG();
        const char *toVHDL();
        const char *toWINDOWS();

        virtual bool operator==(edaNameTranslator& other);

    protected:
        Syntax type;

    private:
        iconv_t inConv;
        iconv_t outConv;
        std::stringstream   buffer; 
    };

    class edaUTF8 : public edaNameTranslator
    {
    public:
        edaUTF8();
        edaUTF8(const char *str);
    };

    class edaCDBA : public edaNameTranslator
    {
    public:
        edaCDBA();
        edaCDBA(const char *str);
    }; 

    class edaDEF : public edaNameTranslator
    {
    public:
        edaDEF();
        edaDEF(const char *str);
    }; 

    class edaEDIF : public edaNameTranslator
    {
    public:
        edaEDIF();
        edaEDIF(const char *str);
    }; 

    class edaLEF : public edaNameTranslator
    {
    public:
        edaLEF();
        edaLEF(const char *str);
    }; 

    class edaOA : public edaNameTranslator
    {
    public:
        edaOA();
        edaOA(const char *str);
    }; 

    class edaSPEF : public edaNameTranslator
    {
    public:
        edaSPEF();
        edaSPEF(const char *str);
    }; 

    class edaSPF : public edaNameTranslator
    {
    public:
        edaSPF();
        edaSPF(const char *str);
    }; 

    class edaSPICE : public edaNameTranslator
    {
    public:
        edaSPICE();
        edaSPICE(const char *str);
    }; 

    class edaUNIX : public edaNameTranslator
    {
    public:
        edaUNIX();
        edaUNIX(const char *str);
    }; 

    class edaVERILOG : public edaNameTranslator
    {
    public:
        edaVERILOG();
        edaVERILOG(const char *str);
    }; 

    class edaVHDL : public edaNameTranslator
    {
    public:
        edaVHDL();
        edaVHDL(const char *str);
    }; 

    class edaWINDOWS : public edaNameTranslator
    {
    public:
        edaWINDOWS();
        edaWINDOWS(const char *str);
    }; 

} // End namespace edant

#endif //EDANAMETRANSLATOR_H_
