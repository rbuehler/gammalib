/***************************************************************************
 *          GEventCube.hpp  -  Abstract event bin container class          *
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
 * @file GEventCube.hpp
 * @brief Abstract event bin container class interface definition
 * @author J. Knodlseder
 */

#ifndef GEVENTCUBE_HPP
#define GEVENTCUBE_HPP

/* __ Includes ___________________________________________________________ */
#include <string>
#include "GEvents.hpp"
#include "GEventBin.hpp"


/***********************************************************************//**
 * @class GEventCube
 *
 * @brief Abstract event bin container class
 *
 * This class is an abstract container class for event bins.
 ***************************************************************************/
class GEventCube : public GEvents {

public:
    // Constructors and destructors
    GEventCube(void);
    GEventCube(const GEventCube& cube);
    virtual ~GEventCube(void);

    // Operators
    virtual GEventCube&      operator=(const GEventCube& cube);
    virtual GEventBin*       operator[](const int& index) = 0;
    virtual const GEventBin* operator[](const int& index) const = 0;

    // Pure virtual methods
    virtual void        clear(void) = 0;
    virtual GEventCube* clone(void) const = 0;
    virtual int         size(void) const = 0;
    virtual int         dim(void) const = 0;
    virtual int         naxis(int axis) const = 0;
    virtual void        load(const std::string& filename) = 0;
    virtual void        save(const std::string& filename, bool clobber = false) const = 0;
    virtual void        read(const GFits& file) = 0;
    virtual void        write(GFits& file) const = 0;
    virtual int         number(void) const = 0;
    virtual std::string print(void) const = 0;

protected:
    // Protected methods
    void init_members(void);
    void copy_members(const GEventCube& cube);
    void free_members(void);
};

#endif /* GEVENTCUBE_HPP */
