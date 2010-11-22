/***************************************************************************
 *   GFitsTableCFloatCol.i  - FITS table single precision complex column   *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GFitsTableCFloatCol.i
 * @brief GFitsTableCFloatCol class SWIG file.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GFitsTableCFloatCol.hpp"
%}


/***********************************************************************//**
 * @class GFitsTableCFloatCol
 *
 * @brief SWIG interface for FITS table floating point column
 ***************************************************************************/
class GFitsTableCFloatCol : public GFitsTableCol {
public:
    // Constructors and destructors
    GFitsTableCFloatCol(void);
    GFitsTableCFloatCol(const std::string& name, const int& length,
                        const int& size = 1);
    GFitsTableCFloatCol(const GFitsTableCFloatCol& column);
    virtual ~GFitsTableCFloatCol(void);

    // Methods
    std::string    string(const int& row, const int& col = 0);
    double         real(const int& row, const int& col = 0);
    int            integer(const int& row, const int& col = 0);
    GFits::cfloat* data(void) { return m_data; }
    void           nulval(const GFits::cfloat* value);
    GFits::cfloat* nulval(void) { return m_nulval; }
};


/***********************************************************************//**
 * @brief GFitsTableCFloatCol class extension
 *
 * @todo Implement __getitem__ method. This probably means that a real
 * cfloat class is needed.
 ***************************************************************************/
%extend GFitsTableCFloatCol {
/*
    GFits::cfloat __getitem__(int GFitsTableColInx[]) {
        if (GFitsTableColInx[0] == 1)
            return (*self)(GFitsTableColInx[1]);
        else
            return (*self)(GFitsTableColInx[1], GFitsTableColInx[2]);
    }
*/
    void __setitem__(int GFitsTableColInx[], GFits::cfloat value) {
        if (GFitsTableColInx[0] == 1)
            (*self)(GFitsTableColInx[1]) = value;
        else
            (*self)(GFitsTableColInx[1], GFitsTableColInx[2]) = value;
    }
    GFitsTableCFloatCol copy() {
        return (*self);
    }
};
