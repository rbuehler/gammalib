/***************************************************************************
 *               GCTAObservation.hpp  -  CTA Observation class             *
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
 * @file GCTAObservation.hpp
 * @brief GCTAObservation class interface definition.
 * @author J. Knodlseder
 */

#ifndef GCTAOBSERVATION_HPP
#define GCTAOBSERVATION_HPP

/* __ Includes ___________________________________________________________ */
#include "GObservation.hpp"
#include "GIntegrand.hpp"


/***********************************************************************//**
 * @class GCTAObservation
 *
 * @brief Interface class for CTA observations.
 ***************************************************************************/
class GCTAObservation : public GObservation {

    // I/O friends
    friend std::ostream& operator<< (std::ostream& os, const GCTAObservation& obs);

public:
    // Constructors and destructors
    GCTAObservation(void);
    GCTAObservation(const GCTAObservation& obs);
    virtual ~GCTAObservation(void);

    // Operators
    GCTAObservation& operator= (const GCTAObservation& obs);

    // Methods
    void   response(const std::string& irfname, std::string caldb = "");
    void   load_unbinned(const std::string& filename);
    void   load_binned(const std::string& filename);
    double npred(const GModels& pars, GVector* gradient) const;

protected:
    // Protected methods
    void             init_members(void);
    void             copy_members(const GCTAObservation& obs);
    void             free_members(void);
    GCTAObservation* clone(void) const;

    // Npred integration methods
    double npred_temp(const GModel& model) const;
    double npred_grad_temp(const GModel& model, int ipar) const;

    // Protected data area
};

#endif /* GCTAOBSERVATION_HPP */
