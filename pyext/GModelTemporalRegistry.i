/***************************************************************************
 *  GModelTemporalRegistry.i  -  Temporal model registry class python I/F  *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2011 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/**
 * @file GModelTemporalRegistry.i
 * @brief GModelTemporalRegistry class python interface.
 * @author J. Knodlseder
 */
%{
/* Put headers and other declarations here that are needed for compilation */
#include "GModelTemporalRegistry.hpp"
#include "GTools.hpp"
%}


/***********************************************************************//**
 * @class GModelTemporalRegistry
 *
 * @brief Interface definition for the temporal model registry class.
 ***************************************************************************/
class GModelTemporalRegistry {
public:
    // Constructors and destructors
    GModelTemporalRegistry(void);
    GModelTemporalRegistry(const GModelTemporal* model);
    GModelTemporalRegistry(const GModelTemporalRegistry& registry);
    virtual ~GModelTemporalRegistry(void);

    // Methods
    int             size(void) const { return m_number; }
    GModelTemporal* alloc(const std::string& type) const;
    std::string     name(const int& index) const;
};


/***********************************************************************//**
 * @brief GModelTemporalRegistry class extension
 ***************************************************************************/
%extend GModelTemporalRegistry {
    char *__str__() {
        return tochar(self->print());
    }
};