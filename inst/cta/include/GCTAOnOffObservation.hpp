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
 * @file GCTAOnOffObservation.hpp
 * @brief Container of CTA OnOff observation
 * @author Chia-Chun Lu & Christoph Deil
 */

#ifndef GCTAONOFFOBSERVATION_HPP
#define GCTAONOFFOBSERVATION_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GBase.hpp"
#include "GPha.hpp"


/***********************************************************************//**
 * @class GCTAOnOffObservation
 *
 * @brief Container of CTA OnOff observation
 ***************************************************************************/
class GCTAOnOffObservation : public GBase {

public:
    // Constructors and destructors
    GCTAOnOffObservation(void);
    GCTAOnOffObservation(const GCTAOnOffObservation& c);
    virtual ~GCTAOnOffObservation(void);
 
    // Operators
    GCTAOnOffObservation& operator= (const GCTAOnOffObservation& c);

    // Methods
    void        clear(void);
    GCTAOnOffObservation*     clone(void) const;
    std::string print(const GChatter& chatter) const;

    // Getters / Setters
    void name(const std::string& name) { m_name = name; }
    virtual std::string name(void) const { return m_name; }
    void instrument(const std::string& instrument) { m_instrument = instrument; }
    virtual std::string instrument(void) const { return m_instrument; }
    void id(const std::string& id) { m_id = id; };
    const std::string& id(void) const { return m_id; }
    void spec_on(const GPha& spec_on) { m_spec_on = spec_on; };
    const GPha& spec_on(void) const { return m_spec_on; }
    void spec_off(const GPha& spec_off) { m_spec_off = spec_off; };
    const GPha& spec_off(void) const { return m_spec_off; }


protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GCTAOnOffObservation& c);
    void free_members(void);

    // Protected data members
    std::string     m_name;         //!< Name
    std::string   m_instrument;   //!< Instrument name
    std::string m_id;           //!< Observation identifier
    GPha m_spec_on;
    GPha m_spec_off;

};

#endif /* GCTAONOFFOBSERVATION_HPP */
