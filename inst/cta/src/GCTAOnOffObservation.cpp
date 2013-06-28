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
 * @file GCTAOnOffObservation.cpp
 * @brief Container of CTA OnOff observation
 * @author Chia-Chun Lu & Christoph Deil
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GCTAOnOffObservation.hpp"
#include "GTools.hpp"

/* __ Method name definitions ____________________________________________ */

#define G_WRITE                        "GCTAOnOffObservation::write(GXmlElement&)"
#define G_READ                         "GCTAOnOffObservation::read(GXmlElement&)"
#define G_FILL                            "GCTAOnOffObservation::fill(GCTAObservation&)"

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
GCTAOnOffObservation::GCTAOnOffObservation(void)
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
GCTAOnOffObservation::GCTAOnOffObservation(const GCTAOnOffObservation& c)
{ 
    // Initialise private
    init_members();

    // Copy members
    copy_members(c);

    // Return
    return;
}

GCTAOnOffObservation::GCTAOnOffObservation(const GEbounds& reco_ebounds, const GSkyRegions& on, const GSkyRegions& off)
{
    // Initialise private
    init_members();

    // set members
    m_on_spec = GPha(reco_ebounds);
    m_off_spec = GPha(reco_ebounds);
    m_on_regions = on;
    m_off_regions = off;
    m_arf = GArf(reco_ebounds);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GCTAOnOffObservation::~GCTAOnOffObservation(void)
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
GCTAOnOffObservation& GCTAOnOffObservation::operator= (const GCTAOnOffObservation& c)
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
void GCTAOnOffObservation::clear(void)
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
GCTAOnOffObservation* GCTAOnOffObservation::clone(void) const
{
    return new GCTAOnOffObservation(*this);
}


/***********************************************************************//**
 * @brief Print class information
 ***************************************************************************/
std::string GCTAOnOffObservation::print(const GChatter& chatter) const
{
    // Initialise result string
    std::string result;

    if (chatter != SILENT) {
      // Append header
      result.append("=== GCTAOnOffObservation ===");
      result.append("\n"+gammalib::parformat("Name")+m_name);
    }
    // Return result
    return result;
}

/***********************************************************************//**
 * @brief read observation from an xml element
 *
 * @param[in] xml GXmlElement.
 ***************************************************************************/
void GCTAOnOffObservation::read(const GXmlElement& xml)
{
	// clean object
	clear();

	// Extract instrument name
	m_instrument = xml.attribute("instrument");

	// Determine number of parameter nodes in XML element
	int npars = xml.elements("parameter");

	// Verify that XML element has exactly 6 parameters
	if (xml.elements() != 6 || npars != 6) {
		throw GException::xml_invalid_parnum(G_READ, xml,
			  "CTA observation requires exactly 6 parameters.");
	}

	// Extract parameters
	int npar[] = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < npars; ++i) {

		// Get parameter element
		const GXmlElement* par = xml.element("parameter", i);

		// Handle Pha_on
		if (par->attribute("name") == "Pha_on") {

			// Read pha_on file name
			std::string filename = par->attribute("file");

			// Load pha_on
			m_on_spec.load(filename);

			// Increment parameter counter
			npar[0]++;
		}

		// Handle Pha_off
		else if (par->attribute("name") == "Pha_off") {

			// Read countsmap file name
			std::string filename = par->attribute("file");

			// Load pha_off
			m_off_spec.load(filename);

			// Increment parameter counter
			npar[1]++;
		}

		// Handle on regions
		else if(par->attribute("name") == "Regions_on") {

			// Get filename
			std::string filename = par->attribute("file");

			// load on regions
			m_on_regions.load(filename);

			// Increase number of parameters
			npar[2]++;
		}

		// Handle off regions
		else if(par->attribute("name") == "Regions_off") {

			// Get filename
			std::string filename = par->attribute("file");

			// load off regions
			m_on_regions.load(filename);

			// Increase number of parameters
			npar[3]++;
		}

		// Handle Arf
		else if(par->attribute("name") == "Arf") {

			// Get filename
			std::string filename = par->attribute("file");

			// load arf
			m_arf.load(filename);

			// Increase number of parameters
			npar[4]++;
		}

		// Handle Rmf
		else if(par->attribute("name") == "Rmf") {

			// Get filename
			std::string filename = par->attribute("file");

			// load Rmf
			m_rmf.load(filename);

			// Increase number of parameters
			npar[5]++;
		}

	} // endfor: looped over all parameters

	// Verify that all parameters were found
	if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1 || npar[4] != 1 || npar[5] != 1) {
		throw GException::xml_invalid_parnames(G_READ, xml,
			  "Require \"Pha_on\" or \"Pha_off\" and \"Regions_on\""
			  ", \"Regions_off\",\"Rmf\" and \"Arf\" parameters.");
	}

	// Return
	return;
}

/***********************************************************************//**
 * @brief write observation to an xml element
 *
 * @param[in] xml GXmlElement.
 ***************************************************************************/
void GCTAOnOffObservation::write(GXmlElement& xml) const
{
	// If XML element has 0 nodes then append 6 parameter nodes
	if (xml.elements() == 0) {
		xml.append(GXmlElement("parameter name=\"Pha_on\""));
		xml.append(GXmlElement("parameter name=\"Pha_off\""));
		xml.append(GXmlElement("parameter name=\"Regions_on\""));
		xml.append(GXmlElement("parameter name=\"Regions_off\""));
		xml.append(GXmlElement("parameter name=\"Arf\""));
		xml.append(GXmlElement("parameter name=\"Rmf\""));
	}

	// Verify that XML element has exactly 4 parameters
	if (xml.elements() != 6 || xml.elements("parameter") != 6) {
		throw GException::xml_invalid_parnum(G_WRITE, xml,
			  "CTAOnOffObservation requires exactly 6 parameters.");
	}

	// Set or update parameter attributes
	int npar[] = {0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 6; ++i) {

		// Get parameter element
		GXmlElement* par = xml.element("parameter", i);

		// Handle on counts
		if (par->attribute("name") == "Pha_on") {
			par->attribute("file", m_on_spec.filename());
			npar[0]++;
		}

		// Handle off counts
		else if (par->attribute("name") == "Pha_off") {
			par->attribute("file", m_off_spec.filename());
			npar[0]++;
		}

		// Handle on regions
		else if (par->attribute("name") == "Regions_on") {
			par->attribute("file", m_on_regions.filename());
			npar[0]++;
		}

		// Handle off regions
		else if (par->attribute("name") == "Regions_off") {
			par->attribute("file", m_off_regions.filename());
			npar[0]++;
		}

		// Handle effective area
		else if (par->attribute("name") == "Arf") {
			par->attribute("file", m_arf.filename());
			npar[0]++;
		}

		// Handle energy resolution
		else if (par->attribute("name") == "Rmf") {
			par->attribute("file", m_rmf.filename());
			npar[0]++;
		}
	}
	// Verify that all required parameters are present
	if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1 || npar[4] != 1 || npar[5] !=1) {
		throw GException::xml_invalid_parnames(G_WRITE, xml,
			  "Require \"Pha_on\" or \"Pha_off\" and \"Regions_on\", \"Regions_off\""
			  " \"Arf\", \"Rmf\" parameters.");
	}

	// Return
	return;
}

/***********************************************************************//**
 * @brief fill events in the on and off spectra
 *
 * @param[in] obs GCTAObservation.
 ***************************************************************************/
void GCTAOnOffObservation::fill(const GCTAObservation& obs)
{
	GCTAEventList* events =  (GCTAEventList*)obs.events();
	if (events==NULL) {
		throw GException::invalid_argument(G_FILL, "GCTAObservation must provide an event list");
	}

	for( int i = 0; i < events->size(); i++) {

		GCTAEventAtom* atom = (*events)[i];
		GCTAInstDir instdir = atom->dir();

		if (m_on_regions.contains(instdir.dir()) ) {
			m_on_spec.fill(atom->energy());
		}
		else if (m_off_regions.contains(instdir.dir()) ) {
			m_off_spec.fill(atom->energy());
		}
	}

	// Return
	return;
}
/***********************************************************************//**
 * @brief compute response of an on/off observation
 *
 * @param[in] obs GCTAObservation.
 ***************************************************************************/
void GCTAOnOffObservation::compute_response(const GCTAObservation& obs, const GEbounds& true_ebounds)
{

	// compute responses
	compute_arf(obs);
	compute_rmf(obs,true_ebounds);

	// Return
	return;
}

/***********************************************************************//**
 * @brief compute arf of an on/off observation
 *
 * @param[in] obs GCTAObservation.
 ***************************************************************************/
void GCTAOnOffObservation::compute_arf(const GCTAObservation& obs)
{
	// Getting response from observation
	GCTAResponse* response = obs.response();
	GEbounds bounds = m_arf.ebounds();

	// loop over reconstructed energies
	for (int i=0;i<bounds.size();i++) {
		GEnergy logemean = bounds.elogmean(i);

		// Setting specresp value
		m_arf[i] = response->aeff(0,0,0,0,logemean.log10TeV());
	}

	// Return
	return;
}

/***********************************************************************//**
 * @brief compute rmf of an on/off observation
 *
 * @param[in] obs GCTAObservation.
 ***************************************************************************/
void GCTAOnOffObservation::compute_rmf(const GCTAObservation& obs, const GEbounds& true_ebounds)
{
	// Getting response from observation
	GCTAResponse* response = obs.response();

	// loop over etrue and ereco
	GEbounds measured_bounds = m_rmf.emeasured();
    for ( int i = 0; i < measured_bounds.size(); i++) {
    	GEnergy ereco = measured_bounds.elogmean(i);
    	for (int j = 0; j < true_ebounds.size(); j++) {
    	    GEnergy etrue = true_ebounds.elogmean(i);
    	    // set rmf value
    	    m_rmf(i,j) = response->edisp(ereco.log10TeV(),0,0,0,0,etrue.log10TeV());
    	}
    }

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
void GCTAOnOffObservation::init_members(void)
{
    // Initialise members
    m_name.clear();
    m_id.clear();
    m_instrument = "CTA";
    m_on_regions.clear();
    m_off_regions.clear();
    m_on_spec.clear();
    m_off_spec.clear();
    m_arf.clear();
    m_rmf.clear();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] c Object.
 ***************************************************************************/
void GCTAOnOffObservation::copy_members(const GCTAOnOffObservation& obs)
{
    // Copy attributes
    m_name = obs.m_name;
    m_id = obs.m_id;
    m_instrument = obs.m_instrument;
    m_on_regions = obs.m_on_regions;
    m_off_regions = obs.m_off_regions;
    m_on_spec = obs.m_on_spec;
    m_off_spec = obs.m_off_spec;
    m_arf = obs.m_arf;
    m_rmf = obs.m_rmf;

    // Return
    return;
}



/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GCTAOnOffObservation::free_members(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/
