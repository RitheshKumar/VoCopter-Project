/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_75497707_INCLUDED
#define BINARYDATA_H_75497707_INCLUDED

namespace BinaryData
{
    extern const char*   copterFoto_png;
    const int            copterFoto_pngSize = 9907;

    extern const char*   copterFoto2_png;
    const int            copterFoto2_pngSize = 5426;

    extern const char*   copterLogo_png;
    const int            copterLogo_pngSize = 60578;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
