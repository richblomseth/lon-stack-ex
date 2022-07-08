////////////////////////////////////////////////////////////////////////////////
//
// Copyright � 2022 Dialog Semiconductor
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// StdHelper.h - An include file to help hide the difference between
//               Microsoft's implementation of the C++ Standard Template
//               Library and other versions (on other platforms).
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _STDHELPER_H
#define _STDHELPER_H


#ifdef _MSC_VER

// Use the STLPORT namespace when using Microsoft Visual C++.  This bypasses
// the Standard C++ Library that comes with VC++, which is not portable at all.
#define STL_NAMESPACE               STLPORT

//Ignore a bunch of warnings now generated by new stl/code interaction.
#pragma warning(disable : 4786) // name truncated warnings
//#pragma warning(disable : 4244 4018) //possible loss of data in implicit conversion and signed mismatch warnings.

#undef min
#undef max
#ifndef ILON_PLATFORM
// These templates are useful for preventing conflicts within
// ATL files...
template <class _Tp>
inline const _Tp& min(const _Tp& __a, const _Tp& __b) {
    return __b < __a ? __b : __a;
}

template <class _Tp>
inline const _Tp& max(const _Tp& __a, const _Tp& __b) {
    return  __a < __b ? __b : __a;
}
#endif // !ILON_PLATFORM

#else

#define STL_NAMESPACE               std
// All other users.  For us, this means the Tornado development
// environment, which uses the GNU C++ compiler, version 2.72.
// No namespace needed.

#endif



#ifdef STL_NAMESPACE
#define STL_NAMESPACE_PREFIX        STL_NAMESPACE::
#define STL_IOS_NAMESPACE_PREFIX    STL_NAMESPACE::ios::
#else
#define STL_NAMESPACE_PREFIX
#define STL_IOS_NAMESPACE_PREFIX
#endif


// Standard Containers
#define stdAutoPtr                  STL_NAMESPACE_PREFIX auto_ptr
#define stdDeque                    STL_NAMESPACE_PREFIX deque
#define stdHashMap                  STL_NAMESPACE_PREFIX hash_map
#define stdList                     STL_NAMESPACE_PREFIX list
#define stdMap                      STL_NAMESPACE_PREFIX map
#define stdMultiMap                 STL_NAMESPACE_PREFIX multimap
#define stdPair                     STL_NAMESPACE_PREFIX pair
#define stdQueue                    STL_NAMESPACE_PREFIX queue
#define stdSet                      STL_NAMESPACE_PREFIX set
#define stdMultiSet                 STL_NAMESPACE_PREFIX multiset
#define stdString                   STL_NAMESPACE_PREFIX string
#define stdVector                   STL_NAMESPACE_PREFIX vector


// Standard Algorithms - #include <algorithm>
#define stdAdvance                  STL_NAMESPACE_PREFIX advance
#define stdAllocator                STL_NAMESPACE_PREFIX allocator
#define stdBinaryFunction           STL_NAMESPACE_PREFIX binary_function
#define stdCopy                     STL_NAMESPACE_PREFIX copy
#define stdEqualTo                  STL_NAMESPACE_PREFIX equal_to
#define stdFind                     STL_NAMESPACE_PREFIX find
#define stdFindIf                   STL_NAMESPACE_PREFIX find_if
#define stdForEach                  STL_NAMESPACE_PREFIX for_each
#define stdHash                     STL_NAMESPACE_PREFIX hash
#define stdLess                     STL_NAMESPACE_PREFIX less
#define stdMakePair                 STL_NAMESPACE_PREFIX make_pair
#define stdMax                      STL_NAMESPACE_PREFIX max
#define stdMin                      STL_NAMESPACE_PREFIX min
#define stdRemove                   STL_NAMESPACE_PREFIX remove
#define stdSwap                     STL_NAMESPACE_PREFIX swap
#define stdTransform                STL_NAMESPACE_PREFIX transform


// Standard Streams
#define stdIOStream                 STL_NAMESPACE_PREFIX iostream
#define stdIStream                  STL_NAMESPACE_PREFIX istream
#define stdOStream                  STL_NAMESPACE_PREFIX ostream

// Standard File Streams - #include <fstream>
#define stdFStream                  STL_NAMESPACE_PREFIX fstream
#define stdIFStream                 STL_NAMESPACE_PREFIX ifstream
#define stdOFStream                 STL_NAMESPACE_PREFIX ofstream

// Standard String Streams - #include <sstream>
#define stdStringStream             STL_NAMESPACE_PREFIX stringstream
#define stdIStringStream            STL_NAMESPACE_PREFIX istringstream
#define stdOStringStream            STL_NAMESPACE_PREFIX ostringstream

// Standard Char* Streams - #include <strstream>
// (Deprecated - use String Streams instead)
//#define stdStrStream              STL_NAMESPACE_PREFIX strstream
//#define stdIStrStream             STL_NAMESPACE_PREFIX istrstream
//#define stdOStrStream             STL_NAMESPACE_PREFIX ostrstream


// Standard Stream Manipulators
#define stdDec                      STL_NAMESPACE_PREFIX dec
#define stdEndL                     STL_NAMESPACE_PREFIX endl
#define stdEndS                     STL_NAMESPACE_PREFIX ends
#define stdFixed                    STL_NAMESPACE_PREFIX fixed
#define stdFlush                    STL_NAMESPACE_PREFIX flush
#define stdHex                      STL_NAMESPACE_PREFIX hex
#define stdInternal                 STL_NAMESPACE_PREFIX internal
#define stdLeft                     STL_NAMESPACE_PREFIX left
#define stdNoShowBase               STL_NAMESPACE_PREFIX noshowbase
#define stdNoShowPoint              STL_NAMESPACE_PREFIX noshowpoint
#define stdNoUppercase              STL_NAMESPACE_PREFIX nouppercase
#define stdOct                      STL_NAMESPACE_PREFIX oct
#define stdRight                    STL_NAMESPACE_PREFIX right
#define stdScientific               STL_NAMESPACE_PREFIX scientific
#define stdSetFill                  STL_NAMESPACE_PREFIX setfill
#define stdSetPrecision             STL_NAMESPACE_PREFIX setprecision
#define stdSetW                     STL_NAMESPACE_PREFIX setw
#define stdShowBase                 STL_NAMESPACE_PREFIX showbase
#define stdShowPoint                STL_NAMESPACE_PREFIX showpoint
#define stdUppercase                STL_NAMESPACE_PREFIX uppercase
#define stdWS                       STL_NAMESPACE_PREFIX ws


// Standard IOS Format Flags
#define flgAdjustField              STL_IOS_NAMESPACE_PREFIX adjustfield
#define flgBaseField                STL_IOS_NAMESPACE_PREFIX basefield
#define flgBoolAlpha                STL_IOS_NAMESPACE_PREFIX boolalpha
#define flgDec                      STL_IOS_NAMESPACE_PREFIX dec
#define flgFixed                    STL_IOS_NAMESPACE_PREFIX fixed
#define flgFloatField               STL_IOS_NAMESPACE_PREFIX floatfield
#define flgHex                      STL_IOS_NAMESPACE_PREFIX hex
#define flgInternal                 STL_IOS_NAMESPACE_PREFIX internal
#define flgLeft                     STL_IOS_NAMESPACE_PREFIX left
#define flgOct                      STL_IOS_NAMESPACE_PREFIX oct
#define flgRight                    STL_IOS_NAMESPACE_PREFIX right
#define flgScientific               STL_IOS_NAMESPACE_PREFIX scientific
#define flgShowBase                 STL_IOS_NAMESPACE_PREFIX showbase
#define flgShowPoint                STL_IOS_NAMESPACE_PREFIX showpoint
#define flgShowPos                  STL_IOS_NAMESPACE_PREFIX showpos
#define flgSkipWs                   STL_IOS_NAMESPACE_PREFIX skipws
#define flgUnitBuf                  STL_IOS_NAMESPACE_PREFIX unitbuf
#define flgUppercase                STL_IOS_NAMESPACE_PREFIX uppercase

#endif // _STDHELPER_H
