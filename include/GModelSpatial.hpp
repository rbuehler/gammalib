/***************************************************************************
 *         GModelSpatial.hpp  -  Spatial model abstract base class         *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009-2011 by Jurgen Knodlseder                           *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GModelSpatial.hpp
 * @brief Abstract spatial model base class interface definition
 * @author J. Knodlseder
 */

#ifndef GMODELSPATIAL_HPP
#define GMODELSPATIAL_HPP

/* __ Includes ___________________________________________________________ */
#include <iostream>
#include <string>
#include "GLog.hpp"
#include "GModelPar.hpp"
#include "GSkyDir.hpp"
#include "GXmlElement.hpp"
#include "GRan.hpp"


/***********************************************************************//**
 * @class GModelSpatial
 *
 * @brief Abstract spatial model base class
 *
 * This class implements the spatial component of the factorized gamma-ray
 * source model. Typical examples of spatial components are a point source
 * (implemented by the derived class GModelSpatialPtsrc) or a Gaussian
 * source (implemented by the derived class GModelSpatialGauss).
 ***************************************************************************/
class GModelSpatial {

    // I/O friends
    friend std::ostream& operator<<(std::ostream& os, const GModelSpatial& model);
    friend GLog&         operator<<(GLog& log,        const GModelSpatial& model);

public:
    // Constructors and destructors
    GModelSpatial(void);
    GModelSpatial(const GModelSpatial& model);
    virtual ~GModelSpatial(void);

    // Operators
    virtual GModelSpatial&   operator= (const GModelSpatial& model);
    virtual GModelPar&       operator[](const int& index);
    virtual const GModelPar& operator[](const int& index) const;
    virtual GModelPar&       operator[](const std::string& name);
    virtual const GModelPar& operator[](const std::string& name) const;

    // Pure virtual methods
    virtual void           clear(void) = 0;
    virtual GModelSpatial* clone(void) const = 0;
    virtual std::string    type(void) const = 0;
    virtual double         eval(const GSkyDir& srcDir) const = 0;
    virtual double         eval_gradients(const GSkyDir& srcDir) const = 0;
    virtual GSkyDir        mc(GRan& ran) const = 0;
    virtual void           read(const GXmlElement& xml) = 0;
    virtual void           write(GXmlElement& xml) const = 0;
    virtual std::string    print(void) const = 0;

    // Methods
    int size(void) const { return m_pars.size(); }

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GModelSpatial& model);
    void free_members(void);

    // Proteced members
    std::vector<GModelPar*> m_pars;  //!< Parameter pointers
};

#endif /* GMODELSPATIAL_HPP */
