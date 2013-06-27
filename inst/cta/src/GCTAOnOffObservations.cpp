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
#include "GObservationRegistry.hpp"


/* __ Method name definitions ____________________________________________ */
#define G_AT                                "GCTAOnOffObservations::at(int&)"
#define G_APPEND       "GCTAOnOffObservations::append(GCTAOnOffObservation&)"
#define G_READ                           "GCTAOnOffObservations::read(GXml&)"

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


/***********************************************************************//**
 * @brief Append observation to container
 *
 * @param[in] obs Observation.
 * @return Pointer to deep copy of observation.
 *
 * @exception GException::invalid_value
 *            Observation with same instrument and identifier already
 *            exists in container.
 *
 * Appends a deep copy of an observation to the container.
 ***************************************************************************/
GCTAOnOffObservation* GCTAOnOffObservations::append(const GCTAOnOffObservation& obs)
{
    // Raise an exception if an observation with specified instrument and
    // identifier already exists
    int inx = get_index(obs.instrument(), obs.id());
    if (inx != -1) {
        std::string msg =
            "Attempt to append \""+obs.instrument()+"\" observation with"
            " identifier \""+obs.id()+"\" to observation container, but an"
            " observation with the same attributes exists already at"
            " index "+gammalib::str(inx)+" in the container.\n"
            "Every observation for a given instrument in the observation"
            " container needs a unique identifier.";
        throw GException::invalid_value(G_APPEND, msg);
    }

    // Clone observation
    GCTAOnOffObservation* ptr = obs.clone();

    // Append to list
    m_obs.push_back(ptr);

    // Return pointer
    return ptr;
}

/***********************************************************************//**
 * @brief Return pointer to observation
 *
 * @param[in] index Observation index [0,...,size()-1].
 * @return Observation.
 *
 * @exception GException::out_of_range
 *            Operation index is out of range.
 *
 * Returns a pointer to the observation with specified @p index.
 ***************************************************************************/
GCTAOnOffObservation* GCTAOnOffObservations::at(const int& index)
{
    // Raise exception if index is out of range
    if (index < 0 || index >= size()) {
        throw GException::out_of_range(G_AT, index, 0, size()-1);
    }

    // Return pointer
    return m_obs[index];
}


/***********************************************************************//**
 * @brief Return pointer to observation (const version)
 *
 * @param[in] index Observation index [0,...,size()-1].
 *
 * @exception GException::out_of_range
 *            Operation index is out of range.
 *
 * Returns a const pointer to the observation with specified @p index.
 ***************************************************************************/
const GCTAOnOffObservation* GCTAOnOffObservations::at(const int& index) const
{
    // Raise exception if index is out of range
    if (index < 0 || index >= size()) {
        throw GException::out_of_range(G_AT, index, 0, size()-1);
    }

    // Return pointer
    return m_obs[index];
}

/***********************************************************************//**
 * @brief Return pointer to observation
 *
 * @param[in] index Observation index [0,...,size()-1].
 * @return Observation.
 *
 * Returns a pointer to the observation with specified @p index.
 ***************************************************************************/
inline
GCTAOnOffObservation* GCTAOnOffObservations::operator[](const int& index)
{
    return m_obs[index];
}


/***********************************************************************//**
 * @brief Return pointer to observation (const version)
 *
 * @param[in] index Observation index [0,...,size()-1].
 *
 * Returns a const pointer to the observation with specified @p index.
 ***************************************************************************/
inline
const GCTAOnOffObservation* GCTAOnOffObservations::operator[](const int& index) const
{
    return m_obs[index];
}


/***********************************************************************//**
 * @brief Load observations from XML file
 *
 * @param[in] filename XML filename.
 *
 * Loads observation from a XML file into the container. Please refer to the
 * read() method for more information about the structure of the XML file.
 ***************************************************************************/
/*
void GCTAOnOffObservations::load(const std::string& filename)
{
    // Clear any existing observations
    clear();

    // Load XML document
    GXml xml(filename);

    // Read observations from XML document
    read(xml);

    // Return
    return;
}
*/

/***********************************************************************//**
 * @brief Save observations into XML file
 *
 * @param[in] filename XML filename.
 *
 * Saves observations into a XML file. Please refer to the read() method for
 * more information about the structure of the XML file.
 ***************************************************************************/
void GCTAOnOffObservations::save(const std::string& filename) const
{
    // Declare empty XML document
    GXml xml;

    // Write observations into XML file
    write(xml);

    // Save XML document
    xml.save(filename);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Read observations from XML document
 *
 * @param[in] xml XML document.
 *
 * @exception GException::invalid_instrument
 *            Invalid instrument encountered in XML file.
 *
 * Reads observations from the first observation list that is found in the
 * XML document. The decoding of the instrument specific observation
 * definition is done within the observation's GObservation::read() method.
 * The following file structure is expected:
 *
 *     <observation_list title="observation library">
 *       <observation name="..." id="..." instrument="...">
 *         ...
 *       </observation>
 *       <observation name="..." id="..." instrument="...">
 *         ...
 *       </observation>
 *       ...
 *     </observation_list>
 *
 * The @p name and @p id attributes allow for a unique identification of an
 * observation within the observation container. The @p instrument
 * attributes specifies the instrument to which the observation applies.
 * This attribute will be used to allocate the appropriate instrument
 * specific GObservation class variant by using the GObservationRegistry
 * class.
 *
 * The structure within the @p observation tag is defined by the instrument
 * specific GObservation class.
 *
 * @todo Observation names and IDs are not verified so far for uniqueness.
 *       This would be required to achieve an unambiguous update of parameters
 *       in an already existing XML file when using the write method.
 ***************************************************************************/
/*
void GCTAOnOffObservations::read(const GXml& xml)
{
    // Get pointer on observation library
    const GXmlElement* lib = xml.element("observation_list", 0);

    // Loop over all observations
    int n = lib->elements("observation");
    for (int i = 0; i < n; ++i) {

        // Get pointer on observation
        const GXmlElement* obs = lib->element("observation", i);

        // Get attributes
        std::string name       = obs->attribute("name");
        std::string id         = obs->attribute("id");
        std::string instrument = obs->attribute("instrument");

        // Allocate instrument specific observation
        GObservationRegistry registry;
        GObservation*        ptr = registry.alloc(instrument);

        // If observation is valid then read its definition from XML file
        if (ptr != NULL) {

            // Read definition
            ptr->read(*obs);

            // Set attributes
            ptr->name(name);
            ptr->id(id);

        } // endif: observation was valid

        // ... otherwise throw an exception
        else {
            throw GException::invalid_instrument(G_READ, instrument);
        }

        // Append observation to container
        append(*ptr);

        // Free observation (the append method made a deep copy)
        delete ptr;

    } // endfor: looped over all observations

    // Return
    return;
}
*/

/***********************************************************************//**
 * @brief Write observations into XML document
 *
 * @param[in] xml XML document.
 *
 * Write observations into the first observation library that is found in the
 * XML document. In case that no observation library exists, one is added to
 * the document. Please refer to the read() method for more information
 * about the structure of the XML document.
 ***************************************************************************/
void GCTAOnOffObservations::write(GXml& xml) const
{
    // If there is no observation library then append one
    if (xml.elements("observation_list") == 0) {
        xml.append(GXmlElement("observation_list title=\"observation list\""));
    }

    // Get pointer on observation library
    GXmlElement* lib = xml.element("observation_list", 0);

    // Write all observations into library
    for (int i = 0; i < size(); ++i) {

        // Initialise pointer on observation
        GXmlElement* obs = NULL;

        // Search corresponding observation
        int n = xml.elements("observation");
        for (int k = 0; k < n; ++k) {
            GXmlElement* element = xml.element("observation", k);
            if (element->attribute("name")       == m_obs[i]->name() &&
                element->attribute("id")         == m_obs[i]->id()   &&
                element->attribute("instrument") == m_obs[i]->instrument()) {
                obs = element;
                break;
            }
        }

        // If no observation with corresponding name, ID and instrument was
        // found then append one now
        if (obs == NULL) {
            obs = lib->append("observation");
            obs->attribute("name", m_obs[i]->name());
            obs->attribute("id", m_obs[i]->id());
            obs->attribute("instrument", m_obs[i]->instrument());
        }

        // Write now observation
        m_obs[i]->write(*obs);

    } // endfor: looped over all observaitons

    // Return
    return;
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

/***********************************************************************//**
 * @brief Return observation index by instrument and identifier
 *
 * @param[in] instrument Instrument.
 * @param[in] id Observation identifier.
 * @return Observation index (-1 of instrument and observation identifier
 *         has not been found)
 *
 * Returns observation index based on the specified @p instrument and
 * observation identifier @p id. If no observation with the specified
 * attributes has been found, the method returns -1.
 ***************************************************************************/
int GCTAOnOffObservations::get_index(const std::string& instrument,
                             const std::string& id) const
{
    // Initialise index
    int index = -1;

    // Search observation with specified instrument and id
    for (int i = 0; i < size(); ++i) {
        if ((m_obs[i]->instrument() == instrument) &&
            (m_obs[i]->id()         == id)) {
            index = i;
            break;
        }
    }

    // Return index
    return index;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/
