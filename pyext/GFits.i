/***************************************************************************
 *                 GFits.i  - FITS file access class SWIG file             *
 * ----------------------------------------------------------------------- *
 *  copyright : (C) 2008-2010 by Jurgen Knodlseder                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GFits.i
 * @brief GFits class SWIG definition.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GFits.hpp"
%}

%include stl.i

/***********************************************************************//**
 * @class GFits
 *
 * @brief Implements FITS file SWIG interface
 *
 * GFits is the basic FITS file interface. All FITS file handlings operate
 * via members of GFits. A FITS file is composed of Header Data Units (HDU)
 * which are implemented by the GFitsHDU class.
 ***************************************************************************/
class GFits {
public:
    // Constructors and destructors
    GFits(void);
    GFits(const std::string& filename);
    GFits(const GFits& fits);
    virtual ~GFits(void);

    // Methods
    void        clear(void);
    int         size(void) const;
    void        open(const std::string& filename);
    void        close(void);
    void        save(void);
    void        saveto(const std::string& filename, bool clobber = false);
    void        append(GFitsHDU* hdu);
    GFitsHDU*   hdu(const std::string& extname) const;
    GFitsHDU*   hdu(int extno) const;
    GFitsImage* image(const std::string& extname) const;
    GFitsImage* image(int extno) const;
    GFitsTable* table(const std::string& extname) const;
    GFitsTable* table(int extno) const;
};


/***********************************************************************//**
 * @brief GFits class SWIG extension
 *
 * Note: Print fails on 28373 char long string. For that reason we just put
 * directly a std::cout here which also works (but only for printing) :-)
 ***************************************************************************/
%extend GFits {
    char *__str__() {
        std::string result = self->print();
        std::cout << result;
        std::string empty = "";
        return ((char*)empty.c_str());
        //return ((char*)result.c_str());
    }
    GFits copy() {
        return (*self);
    }
}
