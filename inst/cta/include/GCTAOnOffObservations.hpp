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

#ifndef GCTAONOFFOBSERVATIONS_HPP
#define GCTAONOFFOBSERVATIONS_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include <vector>
#include "GContainer.hpp"
#include "GObservations.hpp"
#include "GEbounds.hpp"
#include "GCTAOnOffObservation.hpp"

/***********************************************************************//**
 * @class GCTAOnOffObservations
 *
 * @brief Container of CTA OnOff observation
 ***************************************************************************/
class GCTAOnOffObservations : public GContainer {

public:
    // Constructors and destructors
    GCTAOnOffObservations(void);
    GCTAOnOffObservations(const GCTAOnOffObservations& c);
    virtual ~GCTAOnOffObservations(void);
 
    // Operators
    GCTAOnOffObservations& operator= (const GCTAOnOffObservations& c);
    GCTAOnOffObservation*       operator[](const int& index);
    const GCTAOnOffObservation* operator[](const int& index) const;

    // Methods
    void        clear(void);
    GCTAOnOffObservations*     clone(void) const;
    GCTAOnOffObservation*       at(const int& index);
    const GCTAOnOffObservation* at(const int& index) const;
    std::string         print(const GChatter& chatter) const;
    int                 size(void) const;
    bool                isempty(void) const;
    void                remove(const int& index);
    void                reserve(const int& num);

    GCTAOnOffObservation* append(const GCTAOnOffObservation& obs);

    //void load(const std::string& filename);
    void save(const std::string& filename) const;
    //void read(const GXml& xml);
    void write(GXml& xml) const;
  
protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GCTAOnOffObservations& c);
    void free_members(void);
    int  get_index(const std::string& instrument,
                       const std::string& id) const;

    // Protected data members
    std::string     m_name;          //!< Name
    std::vector<GCTAOnOffObservation*> m_obs;

};

#endif /* GCTAONOFFOBSERVATIONS_HPP */
