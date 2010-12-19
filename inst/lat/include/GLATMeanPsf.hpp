/***************************************************************************
 *                  GLATMeanPsf.hpp  -  Fermi LAT mean PSF                 *
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
 * @file GLATMeanPsf.hpp
 * @brief GLATMeanPsf class definition.
 * @author J. Knodlseder
 */

#ifndef GLATMEANPSF_HPP
#define GLATMEANPSF_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include <vector>
#include <iostream>
#include "GLog.hpp"
#include "GSkyDir.hpp"
#include "GNodeArray.hpp"

/* __ Forward declarations _______________________________________________ */
class GLATObservation;


/***********************************************************************//**
 * @class GLATMeanPsf
 *
 * @brief Interface for the Fermi LAT position-dependent mean PSF.
 *
 * The position-dependent mean PSF is the point spread function that has
 * been averaged over the zenith and azimuth angles of an observation. The
 * averaging is done using the livetime cube which holds the lifetime as
 * function and zenith and azimuth angles for an observation.
 ***************************************************************************/
class GLATMeanPsf {

    // I/O friends
    friend std::ostream& operator<< (std::ostream& os, const GLATMeanPsf& psf);
    friend GLog&         operator<< (GLog& log, const GLATMeanPsf& psf);

public:
    // Constructors and destructors
    GLATMeanPsf(void);
    GLATMeanPsf(const GSkyDir& dir, const GLATObservation& obs);
    GLATMeanPsf(const GLATMeanPsf& cube);
    virtual ~GLATMeanPsf(void);

    // Operators
    GLATMeanPsf& operator= (const GLATMeanPsf& cube);

    // Methods
    void         clear(void);
    GLATMeanPsf* clone(void) const;
    int          size(void) const;
    void         set(const GSkyDir& dir, const GLATObservation& obs);
    int          noffsets(void) const { return m_offset.size(); }
    int          nenergies(void) const { return m_energy.size(); }
    GSkyDir      dir(void) const { return m_dir; }
    std::string  name(void) const { return m_name; }
    void         name(const std::string& name) { m_name=name; }
    double       thetamax(void) const { return m_theta_max; }
    void         thetamax(const double& value) { m_theta_max=value; }
    double       psf(const double& offset, const double& logE);
    double       exposure(const double& logE);
    std::string  print(void) const;

private:
    // Methods
    void init_members(void);
    void copy_members(const GLATMeanPsf& psf);
    void free_members(void);
    void set_offsets(void);
    
    // Protected members
    std::string          m_name;         //!< Source name for mean PSF
    GSkyDir              m_dir;          //!< Source direction for mean PSF
    std::vector<double>  m_psf;          //!< Mean PSF values
    std::vector<double>  m_exposure;     //!< Mean exposure
    GNodeArray           m_offset;       //!< Offsets of mean PSF
    GNodeArray           m_energy;       //!< log10(energy) of mean PSF
    double               m_theta_max;    //!< Maximum inclination angle (default 70 deg)

    // Bi-linear interpolation data
    double               m_last_energy;  //!< Last requested logE value
    double               m_last_offset;  //!< Last requested offset value
    int                  m_inx1;         //!< Index 1
    int                  m_inx2;         //!< Index 2
    int                  m_inx3;         //!< Index 3
    int                  m_inx4;         //!< Index 4
    double               m_wgt1;         //!< Weighting factor 1
    double               m_wgt2;         //!< Weighting factor 2
    double               m_wgt3;         //!< Weighting factor 3
    double               m_wgt4;         //!< Weighting factor 4
};

#endif /* GLATMEANPSF_HPP */