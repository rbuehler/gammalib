/***************************************************************************
 *                       GClass.hpp - [brief descriptor]                   *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2010-20xx by [author]                                    *
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
 * @file GCTAOnOffObservations.hpp
 * @brief Container of CTA OnOff observation
 * @author Chia-Chun Lu & Christoph Deil
 */

#ifndef GCTAOnOffObservations_HPP
#define GCTAOnOffObservations_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GBase.hpp"


/***********************************************************************//**
 * @class GCTAOnOffObservations
 *
 * @brief Container of CTA OnOff observation
 ***************************************************************************/
class GCTAOnOffObservations : public GBase {

public:
    // Constructors and destructors
    GCTAOnOffObservations(void);
    GCTAOnOffObservations(const GCTAOnOffObservations& c);
    virtual ~GCTAOnOffObservations(void);
 
    // Operators
    GCTAOnOffObservations& operator= (const GCTAOnOffObservations& c);

    // Methods
    void        clear(void);
    GCTAOnOffObservations*     clone(void) const;
    std::string print(const GChatter& chatter) const;
  
protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GCTAOnOffObservations& c);
    void free_members(void);

    // Protected data members
    std::string     m_name;          //!< Name
};

#endif /* GCTAOnOffObservations_HPP */
