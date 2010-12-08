/***************************************************************************
 *        GModelSpectralPlaw2.cpp  -  Spectral power law model class       *
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
 * @file GModelSpectralPlaw2.cpp
 * @brief GModelSpectralPlaw2 class implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <math.h>
#include "GException.hpp"
#include "GTools.hpp"
#include "GModelSpectralPlaw2.hpp"

/* __ Method name definitions ____________________________________________ */
#define G_READ                      "GModelSpectralPlaw2::read(GXmlElement&)"
#define G_WRITE                    "GModelSpectralPlaw2::write(GXmlElement&)"

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                        Constructors/destructors                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GModelSpectralPlaw2::GModelSpectralPlaw2(void) : GModelSpectral()
{
    // Initialise private members for clean destruction
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Constructor
 *
 * @param[in] integral Integral flux.
 * @param[in] index Power law index.
 *
 * Construct a spectral power law from integral flux and spectral index.
 ***************************************************************************/
GModelSpectralPlaw2::GModelSpectralPlaw2(const double& integral,
                                         const double& index) :
                     GModelSpectral()
{
    // Initialise private members for clean destruction
    init_members();

    // Set parameters
    m_integral.value(integral);
    m_index.value(index);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Constructor
 *
 * @param[in] xml XML element.
 *
 * Construct a spectral power law from a XML element.
 ***************************************************************************/
GModelSpectralPlaw2::GModelSpectralPlaw2(const GXmlElement& xml) :
                     GModelSpectral()
{
    // Initialise private members for clean destruction
    init_members();

    // Read information from XML element
    read(xml);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] model Spectral power law model.
 ***************************************************************************/
GModelSpectralPlaw2::GModelSpectralPlaw2(const GModelSpectralPlaw2& model) :
                     GModelSpectral(model)
{
    // Initialise private members for clean destruction
    init_members();

    // Copy members
    copy_members(model);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GModelSpectralPlaw2::~GModelSpectralPlaw2(void)
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
 * @param[in] model Spectral power law model.
 ***************************************************************************/
GModelSpectralPlaw2& GModelSpectralPlaw2::operator= (const GModelSpectralPlaw2& model)
{
    // Execute only if object is not identical
    if (this != &model) {

        // Copy base class members
        this->GModelSpectral::operator=(model);

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(model);

    } // endif: object was not identical

    // Return
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                              Public methods                             =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Clear instance
***************************************************************************/
void GModelSpectralPlaw2::clear(void)
{
    // Free class members (base and derived classes, derived class first)
    free_members();
    this->GModelSpectral::free_members();

    // Initialise members
    this->GModelSpectral::init_members();
    init_members();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Clone instance
***************************************************************************/
GModelSpectralPlaw2* GModelSpectralPlaw2::clone(void) const
{
    return new GModelSpectralPlaw2(*this);
}


/***********************************************************************//**
 * @brief Evaluate function
 *
 * @param[in] srcEng True energy of photon.
 *
 * The power law function is defined as
 * \f[I(E)=integral (index+1)/(emax^{index+1}-emin^{index+1}) E^{index}\f]
 * for \f$index \ne -1\f$ and
 * \f[I(E)=integral / (\log(emax)-\log(emin)) E^{index}\f]
 * for \f$index \eq -1\f$, where
 * \f$integral\f$ is the integral flux between \f$emin\f$ and \f$emax\f$,
 * \f$index\f$ is the spectral index,
 * \f$emin\f$ is the lower energy limit, and
 * \f$emax\f$ is the upper energy limit.
 ***************************************************************************/
double GModelSpectralPlaw2::eval(const GEnergy& srcEng)
{
    // Compute function value
    double gamma = index() + 1.0;
    double norm  = (gamma != 0.0)
                 ? gamma / (pow(emax(), gamma) - pow(emin(), gamma))
                 : 1.0   / (log(emax())        - log(emin()));
    double power = pow(srcEng.MeV(), index());
    double value = integral() * norm * power;

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Evaluate function and gradients
 *
 * @param[in] srcEng True energy of photon.
 *
 * The power law function is defined as
 * \f[I(E)=integral (index+1)/(emax^{index+1}-emin^{index+1}) E^{index}\f]
 * for \f$index \ne -1\f$ and
 * \f[I(E)=integral / (\log(emax)-\log(emin)) E^{index}\f]
 * for \f$index \eq -1\f$, where
 * \f$integral=f_s f_v\f$ is the integral flux between \f$emin\f$ and \f$emax\f$,
 * \f$index=i_s i_v\f$ is the spectral index,
 * \f$emin=l_s l_v\f$ is the lower energy limit, and
 * \f$emax=u_s u_v\f$ is the upper energy limit.
 * Note that each parameter is factorised into a scaling factor and a value
 * and that the method is expected to return the gradient with respect to
 * the parameter value (i.e. \f$f_v\f$, \f$i_v\f$, \f$l_v\f$, and \f$u_v\f$
 * in this case).
 *
 * The partial derivatives of the parameter values are given by
 * \f[dI/df_v=I(E) / f_v\f]
 * \f[dI/di_v=I(E) \[1/(index+1) +
 *                  (\log(emax) emax^{index+1} - \log(emin) emin^{index+1})/
 *                  (emax^{index+1}-emin^{index+1}) + \log(E)\] i_s\f]
 * for \f$index \ne -1\f$ and
 * \f[dI/df_v=I(E) / f_v\f]
 * \f[dI/di_v=I(E) \log(E) i_s\f]
 * for \f$index \eq -1\f$.
 * The partial derivatives for the energy boundaries are fixed to 0 as it is
 * not expected the fit these parameters.
 ***************************************************************************/
double GModelSpectralPlaw2::eval_gradients(const GEnergy& srcEng)
{
    // Initialise
    double value      = 0.0;
    double g_integral = 0.0;
    double g_index    = 0.0;
    double gamma      = index() + 1.0;
    double lnE        = log(srcEng.MeV());
    double power      = pow(srcEng.MeV(), index());

    // Case A: index != -1
    if (gamma != 0.0) {

        // Precomputation
        double emax_g = pow(emax(), gamma);
        double emin_g = pow(emin(), gamma);
        double denom  = emax_g - emin_g;
        double norm   = gamma / denom;

        // Compute function value
        value = integral() * norm * power;

        // Compute partial derivatives of the parameter values
        if (m_integral.isfree())
            g_integral = value / m_integral.value();
        if (m_index.isfree())
            g_index = (1.0/gamma + 
                       (log(emax())*emax_g - log(emin())*emin_g)/denom +
                       lnE) * value * m_index.scale();

    }

    // Case B: index == -1
    else {
    
        // Precomputation
        double lnemax = log(emax());
        double lnemin = log(emin());
        double norm   = 1.0 / (lnemax - lnemin);

        // Compute function value
        value = integral() * norm * power;

        // Compute partial derivatives of the parameter values
        if (m_integral.isfree())
            g_integral = value / m_integral.value();
        if (m_index.isfree())
            g_index = value * lnE * m_index.scale();

    }

    // Set gradients
    m_integral.gradient(g_integral);
    m_index.gradient(g_index);
    m_emin.gradient(0.0);
    m_emax.gradient(0.0);

    // Return
    return value;
}


/***********************************************************************//**
 * @brief Read model from XML element
 *
 * @param[in] xml XML element.
 *
 * @exception GException::model_invalid_parnum
 *            Invalid number of model parameters found in XML element.
 * @exception GException::model_invalid_parnames
 *            Invalid model parameter names found in XML element.
 *
 * Read the spectral power law information from an XML element. The XML
 * element is required to have 4 parameters with names "Integral", "Index",
 * "LowerLimit", and "UpperLimit".
 ***************************************************************************/
void GModelSpectralPlaw2::read(const GXmlElement& xml)
{
    // Verify that XML element has exactly 4 parameters
    if (xml.elements() != 4 || xml.elements("parameter") != 4)
        throw GException::model_invalid_parnum(G_READ, xml,
              "Power law 2 spectral model requires exactly 4 parameters.");

    // Extract model parameters
    int npar[] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {

        // Get parameter element
        GXmlElement* par = (GXmlElement*)xml.element("parameter", i);

        // Handle prefactor
        if (par->attribute("name") == "Integral") {
            m_integral.read(*par);
            npar[0]++;
        }

        // Handle index
        else if (par->attribute("name") == "Index") {
            m_index.read(*par);
            npar[1]++;
        }

        // Handle lower limit
        else if (par->attribute("name") == "LowerLimit") {
            m_emin.read(*par);
            npar[2]++;
        }

        // Handle upper limit
        else if (par->attribute("name") == "UpperLimit") {
            m_emax.read(*par);
            npar[3]++;
        }

    } // endfor: looped over all parameters

    // Verify that all parameters were found
    if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1)
        throw GException::model_invalid_parnames(G_READ, xml,
              "Power law 2 spectral model requires \"Integral\", \"Index\","
              " \"LowerLimit\" and \"UpperLimit\" parameters.");

    // Return
    return;
}


/***********************************************************************//**
 * @brief Write model into XML element
 *
 * @param[in] xml XML element.
 *
 * @exception GException::model_invalid_spectral
 *            Existing XML element is not of type "PowerLaw2"
 * @exception GException::model_invalid_parnum
 *            Invalid number of model parameters or nodes found in XML element.
 * @exception GException::model_invalid_parnames
 *            Invalid model parameter names found in XML element.
 *
 * Write the spectral power law information into an XML element. The XML
 * element has to be of type "PowerLaw2" and will have 4 parameter leafs
 * named "Integral", "Index", "LowerLimit", and "UpperLimit".
 ***************************************************************************/
void GModelSpectralPlaw2::write(GXmlElement& xml) const
{
    // Set model type
    if (xml.attribute("type") == "")
        xml.attribute("type", "PowerLaw2");

    // Verify model type
    if (xml.attribute("type") != "PowerLaw2")
        throw GException::model_invalid_spectral(G_WRITE, xml.attribute("type"),
              "Spectral model is not of type \"PowerLaw2\".");

    // If XML element has 0 nodes then append 4 parameter nodes
    if (xml.elements() == 0) {
        xml.append(new GXmlElement("parameter name=\"Integral\""));
        xml.append(new GXmlElement("parameter name=\"Index\""));
        xml.append(new GXmlElement("parameter name=\"LowerLimit\""));
        xml.append(new GXmlElement("parameter name=\"UpperLimit\""));
    }

    // Verify that XML element has exactly 4 parameters
    if (xml.elements() != 4 || xml.elements("parameter") != 4)
        throw GException::model_invalid_parnum(G_WRITE, xml,
              "Power law 2 spectral model requires exactly 4 parameters.");

    // Set or update model parameter attributes
    int npar[] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {

        // Get parameter element
        GXmlElement* par = (GXmlElement*)xml.element("parameter", i);

        // Handle prefactor
        if (par->attribute("name") == "Integral") {
            npar[0]++;
            m_integral.write(*par);
        }

        // Handle index
        else if (par->attribute("name") == "Index") {
            npar[1]++;
            m_index.write(*par);
        }

        // Handle lower limit
        else if (par->attribute("name") == "LowerLimit") {
            m_emin.write(*par);
            npar[2]++;
        }

        // Handle lower limit
        else if (par->attribute("name") == "UpperLimit") {
            m_emax.write(*par);
            npar[3]++;
        }

    } // endfor: looped over all parameters

    // Check of all required parameters are present
    if (npar[0] != 1 || npar[1] != 1 || npar[2] != 1 || npar[3] != 1)
        throw GException::model_invalid_parnames(G_WRITE, xml,
              "Power law 2 spectral model requires \"Integral\", \"Index\","
              " \"LowerLimit\" and \"UpperLimit\" parameters.");

    // Return
    return;
}


/***********************************************************************//**
 * @brief Print powerlaw information
 ***************************************************************************/
std::string GModelSpectralPlaw2::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GModelSpectralPlaw2 ===\n");
    result.append(parformat("Number of parameters")+str(size()));
    for (int i = 0; i < size(); ++i) {
        result.append("\n"+parformat("Parameter "+str(i+1)));
        result.append(m_par[i]->print());
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
void GModelSpectralPlaw2::init_members(void)
{
    // Initialise parameters
    m_npars  = 4;
    m_par[0] = &m_integral;
    m_par[1] = &m_index;
    m_par[2] = &m_emin;
    m_par[3] = &m_emax;

    // Initialise integral flux
    m_integral = GModelPar();
    m_integral.name("Integral");
    m_integral.unit("ph/cm2/s");
    m_integral.value(1.0);
    m_integral.scale(1.0);
    m_integral.range(0.0, 10.0);
    m_integral.free();

    // Initialise powerlaw index
    m_index = GModelPar();
    m_index.name("Index");
    m_index.value(-2.0);
    m_index.scale(1.0);
    m_index.range(-5.0, -0.1);
    m_index.free();

    // Initialise lower limit
    m_emin = GModelPar();
    m_emin.name("LowerLimit");
    m_emin.unit("MeV");
    m_emin.value(100.0);
    m_emin.scale(1.0);
    m_emin.range(0.001, 1.0e15);
    m_emin.fix();

    // Initialise upper limit
    m_emax = GModelPar();
    m_emax.name("UpperLimit");
    m_emax.unit("MeV");
    m_emax.value(500000.0);
    m_emax.scale(1.0);
    m_emax.range(0.001, 1.0e15);
    m_emax.fix();

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] model Spectral power law model.
 ***************************************************************************/
void GModelSpectralPlaw2::copy_members(const GModelSpectralPlaw2& model)
{
    // Copy model parameters (no need to copy others since they are static)
    m_integral = model.m_integral;
    m_index    = model.m_index;
    m_emin     = model.m_emin;
    m_emax     = model.m_emax;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GModelSpectralPlaw2::free_members(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                 Friends                                 =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream.
 * @param[in] model Model.
 ***************************************************************************/
std::ostream& operator<< (std::ostream& os, const GModelSpectralPlaw2& model)
{
     // Write model in output stream
    os << model.print();

    // Return output stream
    return os;
}


/***********************************************************************//**
 * @brief Log operator
 *
 * @param[in] log Logger.
 * @param[in] model Model.
 ***************************************************************************/
GLog& operator<< (GLog& log, const GModelSpectralPlaw2& model)
{
    // Write model into logger
    log << model.print();

    // Return logger
    return log;
}