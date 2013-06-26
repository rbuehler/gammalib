/***************************************************************************
 *                       GCTAOnOffObservations.cpp - [brief descriptor]                   *
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
 * @file GCTAOnOffObservations.cpp
 * @brief Container of CTA OnOff observation
 * @author Chia-Chun Lu & Christoph Deil
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GCTAOnOffObservations.hpp"
#include "GTools.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                         Constructors/destructors                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GCTAOnOffObservations::GCTAOnOffObservations(void)
{
    // Initialise private members
    init_members();
  
    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] c Object.
 ***************************************************************************/
GCTAOnOffObservations::GCTAOnOffObservations(const GCTAOnOffObservations& c)
{ 
    // Initialise private
    init_members();

    // Copy members
    copy_members(c);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GCTAOnOffObservations::~GCTAOnOffObservations(void)
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                Operators                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] c Object.
 ***************************************************************************/
GCTAOnOffObservations& GCTAOnOffObservations::operator= (const GCTAOnOffObservations& c)
{ 
    // Execute only if object is not identical
    if (this != &c) {

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(c);

    } // endif: object was not identical
  
    // Return
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                             Public methods                              =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
 *
 * This method properly resets the object to an initial state.
 ***************************************************************************/
void GCTAOnOffObservations::clear(void)
{
    // Free class members
    free_members();

    // Initialise members
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
 **************************************************************************/
GCTAOnOffObservations* GCTAOnOffObservations::clone(void) const
{
    return new GCTAOnOffObservations(*this);
}


/***********************************************************************//**
 * @brief Print class information
 ***************************************************************************/
std::string GCTAOnOffObservations::print(const GChatter& chatter) const
{
    // Initialise result string
    std::string result;

    if (chatter != SILENT) {
      // Append header
      result.append("=== GCTAOnOffObservations ===");
      result.append("\n"+gammalib::parformat("Name")+m_name);
    }
    // Return result
    return result;
}


/*==========================================================================
 =                                                                         =
 =                             Private methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GCTAOnOffObservations::init_members(void)
{
    // Initialise members
    m_name.clear();
  
    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] c Object.
 ***************************************************************************/
void GCTAOnOffObservations::copy_members(const GCTAOnOffObservations& c)
{
    // Copy attributes
    m_name = c.m_name;
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GCTAOnOffObservations::free_members(void)
{
    // Free memory
    //if (m_par = NULL) delete [] m_par;

    // Signal free pointers
    //m_par      = NULL;
  
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/
