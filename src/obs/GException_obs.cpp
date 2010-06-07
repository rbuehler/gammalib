/***************************************************************************
 *          GException_obs.cpp  -  observations exception handlers         *
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
 * @file GException_obs.cpp
 * @brief Observation exception handler interface implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#include "GException.hpp"
#include "GTools.hpp"


/***********************************************************************//**
 * @brief Mismatch between gradient vector and number of model parameters
 *
 * @param[in] origin Method that throws the error.
 * @param[in] nsize Gradient vector size.
 * @param[in] npars Number of parameters in model.
 ***************************************************************************/
GException::gradient_par_mismatch::gradient_par_mismatch(std::string origin,
                                                         int         nsize,
                                                         int         npars)
{
    m_origin  = origin;
    m_message = "Gradient vector size "+str(nsize)+
                " mismatches number "+str(npars)+" of model parameters.";
}


/***********************************************************************//**
 * @brief Calibration database directory not found.
 *
 * @param[in] origin Name of method that has thrown the exception.
 * @param[in] caldb Name of calibration database.
 * @param[in] message Optional error message.
 ***************************************************************************/
GException::caldb_not_found::caldb_not_found(std::string origin,
                                             std::string caldb,
                                             std::string message)
{
    m_origin  = origin;
    m_message = "Calibration database '"+caldb+"' not found. "+message;
    return;
}


/***********************************************************************//**
 * @brief Response error: invalid response type specified
 *
 * @param[in] origin Method that throws the error.
 * @param[in] type Specified response type.
 ***************************************************************************/
GException::rsp_invalid_type::rsp_invalid_type(std::string origin,
                                               std::string type)
{
    m_origin  = origin;
    m_message = "Invalid response type '"+type+"' specified.";
}


/***********************************************************************//**
 * @brief Good Time Intervals are not valid.
 *
 * @param[in] origin Method that throws the error.
 * @param[in] gti Pointer to invalid Good Time Intervals.
 * @param[in] message Optional error message.
 *
 * @todo Implement GTI dumping.
 ***************************************************************************/
GException::gti_invalid::gti_invalid(std::string origin, const GGti* gti,
                                     std::string message)
{
    m_origin  = origin;
    m_message = "Invalid Good Time Intervals specified. "+message;
}
