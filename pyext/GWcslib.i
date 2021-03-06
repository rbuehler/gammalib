/***************************************************************************
 *           GWcslib.i  -  Virtual base class for wcslib based WCS         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011-2012 by Juergen Knoedlseder                         *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GWcslib.i
 * @brief Python interface for virtual base class for wcslib based WCS
 * @author Juergen Knoedlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GWcslib.hpp"
%}


/***********************************************************************//**
 * @class GWcslib
 *
 * @brief Virtual base class for wcslib based World Coordinate System
 ***************************************************************************/
class GWcslib : public GWcs {
public:
    // Constructors and destructors
    GWcslib(void);
    explicit GWcslib(const std::string& coords,
                     const double& crval1, const double& crval2,
                     const double& crpix1, const double& crpix2,
                     const double& cdelt1, const double& cdelt2);
    explicit GWcslib(const GFitsHDU* hdu);
    GWcslib(const GWcslib& wcs);
    virtual ~GWcslib(void);

    // Pure virtual methods (not implemented)
    virtual void        clear(void) = 0;
    virtual GWcslib*    clone(void) const = 0;
    virtual std::string code(void) const = 0;
    virtual std::string name(void) const = 0;
    
    // Implemented virtual methods
    virtual void        read(const GFitsHDU* hdu);
    virtual void        write(GFitsHDU* hdu) const;
    virtual double      omega(const int& pix) const;
    virtual double      omega(const GSkyPixel& pix) const;
    virtual GSkyDir     pix2dir(const int& pix) const;
    virtual int         dir2pix(const GSkyDir& dir) const;
    virtual GSkyDir     xy2dir(const GSkyPixel& pix) const;
    virtual GSkyPixel   dir2xy(const GSkyDir& dir) const;

    // Other methods
    void   set(const std::string& coords,
               const double& crval1, const double& crval2,
               const double& crpix1, const double& crpix2,
               const double& cdelt1, const double& cdelt2);
    double crval(const int& inx) const;
    double crpix(const int& inx) const;
    double cdelt(const int& inx) const;
};


/***********************************************************************//**
 * @brief GWcslib class extension
 ***************************************************************************/
