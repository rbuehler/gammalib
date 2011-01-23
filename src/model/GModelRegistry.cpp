/***************************************************************************
 *       GModelRegistry.cpp  -  Spatial model registry class        *
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
 * @file GModelRegistry.cpp
 * @brief GModelRegistry class interface definition
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "GModelRegistry.hpp"
#include "GTools.hpp"

/* __ Static members _____________________________________________________ */
int            GModelRegistry::m_number(0);
std::string*   GModelRegistry::m_names(0);
const GModel** GModelRegistry::m_models(0);

/* __ Method name definitions ____________________________________________ */
#define G_NAME                                   "GModelRegistry::name(int&)"

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */
#define G_DEBUG_REGISTRY 0


/*==========================================================================
 =                                                                         =
 =                        Constructors/destructors                         =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Void constructor
 ***************************************************************************/
GModelRegistry::GModelRegistry(void)
{
    // Initialise private members for clean destruction
    init_members();

    // Debug option: Show actual registry
    #if G_DEBUG_REGISTRY
    std::cout << "GModelRegistry(void): ";
    for (int i = 0; i < m_number; ++i)
        std::cout << "\"" << m_names[i] << "\" ";
    std::cout << std::endl;
    #endif

    // Return
    return;
}


/***********************************************************************//**
 * @brief Model constructor
 ***************************************************************************/
GModelRegistry::GModelRegistry(const GModel* model)
{
    // Initialise private members for clean destruction
    init_members();

    // Debug option: Notify new registry
    #if G_DEBUG_REGISTRY
    std::cout << "GModelRegistry(const GModel*): ";
    std::cout << "add \"" << model->type() << "\" to registry." << std::endl;
    #endif
    
    // Allocate new old registry
    std::string*   new_names  = new std::string[m_number+1];
    const GModel** new_models = new const GModel*[m_number+1];

    // Save old registry
    for (int i = 0; i < m_number; ++i) {
        new_names[i]  = m_names[i];
        new_models[i] = m_models[i];
    }

    // Add new model to registry
    new_names[m_number]  = model->type();
    new_models[m_number] = model;

    // Delete old registry
    if (m_names  != NULL) delete [] m_names;
    if (m_models != NULL) delete [] m_models;

    // Set pointers on new registry
    m_names  = new_names;
    m_models = new_models;

    // Increment number of models in registry
    m_number++;

    // Debug option: Show actual registry
    #if G_DEBUG_REGISTRY
    std::cout << "GModelRegistry(const GModel*): ";
    for (int i = 0; i < m_number; ++i)
        std::cout << "\"" << m_names[i] << "\" ";
    std::cout << std::endl;
    #endif

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param[in] registry Registry.
 ***************************************************************************/
GModelRegistry::GModelRegistry(const GModelRegistry& registry)
{
    // Initialise private members
    init_members();

    // Copy members
    copy_members(registry);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GModelRegistry::~GModelRegistry(void)
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
 * @param[in] registry Registry.
 ***************************************************************************/
GModelRegistry& GModelRegistry::operator= (const GModelRegistry& registry)
{
    // Execute only if object is not identical
    if (this != &registry) {

        // Free members
        free_members();

        // Initialise private members
        init_members();

        // Copy members
        copy_members(registry);

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
 * @brief Allocate model of given type
 *
 * @param[in] type Model type.
 *
 * Returns a pointer to a void model instance of the specified type. If the
 * type has not been found in the registry, a NULL pointer is returned.
 ***************************************************************************/
GModel* GModelRegistry::alloc(const std::string& type) const
{
    // Initialise model
    GModel* model = NULL;

    // Search for model in registry
    for (int i = 0; i < m_number; ++i) {
        if (m_names[i] == type) {
            model = m_models[i]->clone();
            break;
        }
    }    

    // Return model
    return model;
}


/***********************************************************************//**
 * @brief Returns model name
 *
 * @param[in] index Model index [0,...,size()-1].
 *
 * @exception GException::out_of_range
 *            Model index is out of range.
 ***************************************************************************/
std::string GModelRegistry::name(const int& index) const
{
    // Compile option: raise exception if index is out of range
    #if defined(G_RANGE_CHECK)
    if (index < 0 || index >= size())
        throw GException::out_of_range(G_NAME, index, 0, size()-1);
    #endif

    // Return name
    return (m_names[index]);
}


/***********************************************************************//**
 * @brief Print registry information
 ***************************************************************************/
std::string GModelRegistry::print(void) const
{
    // Initialise result string
    std::string result;

    // Append header
    result.append("=== GModelRegistry ===");
    result.append("\n"+parformat("Number of models")+str(m_number));

    // Append models
    for (int i = 0; i < m_number; ++i) {
        result.append("\n"+parformat(m_names[i]));
        result.append(m_models[i]->type());
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
void GModelRegistry::init_members(void)
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] registry Registry.
 ***************************************************************************/
void GModelRegistry::copy_members(const GModelRegistry& registry)
{
    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GModelRegistry::free_members(void)
{
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                                  Friends                                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Output operator
 *
 * @param[in] os Output stream.
 * @param[in] registry Model registry.
 ***************************************************************************/
std::ostream& operator<< (std::ostream& os, const GModelRegistry& registry)
{
     // Write registry in output stream
    os << registry.print();

    // Return output stream
    return os;
}


/***********************************************************************//**
 * @brief Log operator
 *
 * @param[in] log Logger.
 * @param[in] registry Model registry.
 ***************************************************************************/
GLog& operator<< (GLog& log, const GModelRegistry& registry)
{
    // Write registry into logger
    log << registry.print();

    // Return logger
    return log;
}