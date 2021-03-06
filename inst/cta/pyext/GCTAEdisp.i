/***************************************************************************
 *                 GCTAEdisp.i - Energy dispersion base class              *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2012-2013 by Juergen Knoedlseder                         *
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
 * @file GCTAEdisp.i
 * @brief Energy dispersion base class definition
 * @author Juergen Knoedlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GCTAEdisp.hpp"
#include "GTools.hpp"
%}


/***********************************************************************//**
 * @class GCTAEdisp
 *
 * @brief Abstract base class for the CTA energy dispersion
 ***************************************************************************/
class GCTAEdisp : public GBase {

public:
    // Constructors and destructors
    GCTAEdisp(void);
    GCTAEdisp(const GCTAEdisp& edisp);
    virtual ~GCTAEdisp(void);

    // Pure virtual operators
    /*
    virtual double operator()(const double& logE, 
                              const double& theta = 0.0, 
                              const double& phi = 0.0,
                              const double& zenith = 0.0,
                              const double& azimuth = 0.0,
                              const bool&   etrue = true) const = 0;
    */

    // Pure virtual methods
    virtual void        clear(void) = 0;
    virtual GCTAEdisp*  clone(void) const = 0;
    virtual void        load(const std::string& filename) = 0;
    virtual std::string filename(void) const = 0;
};


/***********************************************************************//**
 * @brief GCTAEdisp class extension
 ***************************************************************************/
%extend GCTAEdisp {
};
