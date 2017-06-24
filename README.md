# edaNameTranslator
This library translates strings between common EDA naming conventions.
The need for this library arises from differences in EDA standards and
languages.  VHDL is case insensitive whereas Verilog is.  Bit index
identifiers are also a difference between naming conventions.  Cdba uses
< > whereas SPEF uses [ ].

# Supported Naming Conventions
This library will internally store all strings as UTF-8, thus allowing for
International and wide character string support.  To start this library
will support:
- UTF-8 (default)
- Cdba
- DEF
- EDIF
- LEF
- OA
- SPEF
- SPF
- SPICE
- UNIX (filesystem naming convention)
- Verilog
- VHDL
- Windows (filesystem naming convention)

# Get Involved
If you or your company would like to participate in this project, please 
email us at support@eddrs.com.  If you want to do simple code or 
documentation fixes but do not want to be a participating party, please take
a look at these instructions on how to create a new pull request
https://help.github.com/articles/creating-a-pull-request/.

If you would like to ensure that this library covers a particular convention 
or coverage of data in a file, please email us a test case file at 
support@eddrs.com or check it into the testData directory by following these
instructions: https://help.github.com/articles/creating-a-pull-request/.  
Please do not check-in any data that you don't want shared with the world.  
We do not take any responsibility for design data that is part of this 
repository.

# The Test Data
Make sure you pull down this repository using the recursive flag.  This will 
supply more test data.
```sh
git clone --recursive https://github.com/EDDRSoftware/edaNameTranslator
```
