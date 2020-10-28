%module sm
%{
    #include "sm.h"
    #include "key.h"
%}
%include <cstring.i>
%include <std_string.i>
%begin %{
#define SWIG_PYTHON_STRICT_BYTE_CHAR
%}
%include "sm.h"
%include "key.h"