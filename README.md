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
