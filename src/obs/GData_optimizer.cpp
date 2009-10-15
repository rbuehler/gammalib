/***************************************************************************
 *          GData_optimizer.cpp  -  Optimizer class of data class          *
 * ----------------------------------------------------------------------- *
 *  copyright (C) 2009 by Jurgen Knodlseder                                *
 * ----------------------------------------------------------------------- *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 * ----------------------------------------------------------------------- *
 ***************************************************************************/
/**
 * @file GData_optimizer.cpp
 * @brief GData::optimizer class implementation.
 * @author J. Knodlseder
 */

/* __ Includes ___________________________________________________________ */
#include "GData.hpp"

/* __ Method name definitions ____________________________________________ */

/* __ Macros _____________________________________________________________ */

/* __ Coding definitions _________________________________________________ */

/* __ Debug definitions __________________________________________________ */
#define G_EVAL_TIMING 1

/* __ Prototypes _________________________________________________________ */


/*==========================================================================
 =                                                                         =
 =                GData::optimizer constructors/destructors                =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Constructor
***************************************************************************/
GData::optimizer::optimizer(void) : GOptimizerFunction()
{
    // Initialise iterator
    init_members();
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Constructor based on specific GData object
 ***************************************************************************/
GData::optimizer::optimizer(GData *data) : GOptimizerFunction()
{
    // Initialise iterator
    init_members();

    // Set data object
    m_data = data;
    
    // Return
    return;
}



/***********************************************************************//**
 * @brief Copy constructor
 *
 * @param data GData instance which should be used for construction
 ***************************************************************************/
GData::optimizer::optimizer(const optimizer& fct) : GOptimizerFunction(fct)
{
    // Initialise class members for clean destruction
    init_members();

    // Copy members
    copy_members(fct);

    // Return
    return;
}


/***********************************************************************//**
 * @brief Destructor
 ***************************************************************************/
GData::optimizer::~optimizer()
{
    // Free members
    free_members();

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                       GData::optimizer operators                        =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Assignment operator
 *
 * @param[in] data GData instance to be assigned
 ***************************************************************************/
GData::optimizer& GData::optimizer::operator= (const optimizer& fct)
{
    // Execute only if object is not identical
    if (this != &fct) {

        // Copy base class members
        this->GOptimizerFunction::operator=(fct);

        // Free members
        free_members();

        // Initialise private members for clean destruction
        init_members();

        // Copy members
        copy_members(fct);

    } // endif: object was not identical

    // Return this object
    return *this;
}


/*==========================================================================
 =                                                                         =
 =                      GData::optimizer public methods                    =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Evaluate function
 ***************************************************************************/
void GData::optimizer::eval(const GOptimizerPars& pars) 
{
    // Timing measurement
    #if G_EVAL_TIMING
    clock_t t_start = clock();
    #endif
    
    // Allocate pointers for temporary memory
    int*    inx    = NULL;
    double* values = NULL;
    
    // Single loop for common exit point
    do {
        // Get number of parameters
        int npars = pars.npars();
        int nfree = pars.nfree();
        
        // Fall through if we have no free parameters
        if (npars < 1)
            continue;
        
        // Free old memory
        if (m_gradient != NULL) delete m_gradient;
        if (m_covar    != NULL) delete m_covar;
        
        // Initialise value, gradient vector and curvature matrix
        m_value    = 0.0;
        m_gradient = new GVector(npars);
        m_covar    = new GSparseMatrix(npars,npars);
        
        // Allocate some working arrays
        m_covar->stack_init(npars,10000);
        inx    = new int[npars];
        values = new double[npars];
        
        // Iterate over all data bins
        GData::iterator end = m_data->end();
        for (GData::iterator bin = m_data->begin(); bin != end; ++bin) {
        
            // Get number of counts in bin
            double data = bin->counts();
            
            // DUMMY: Get model and derivative
            double  model = 1.0;
            GVector grad(npars);
            grad(0) = 0.1;
            grad(1) = 0.2;
            
            // Skip bin if model is empty
            if (model <= 0.0)
                continue;
            
            // Create index array of non-zero derivatives
            int ndev = 0;
            for (int i = 0; i < npars; ++i) {
                if (grad(i) != 0.0) {
                    inx[ndev] = i;
                    ndev++;
                }
            }
            
            // Update Poissonian statistics
            m_value -= data * log(model) - model;
            
            // Skip bin now if there are no non-zero derivatives
            if (ndev < 1)
                continue;
            
            // Update gradient vector and curvature matrix. To avoid unneccessary
            // computation we distinguish the case where data>0 and data=0. The
            // second case requires much less computation since it does not
            // contribute to the covariance matrix ...
            if (data > 0.0) {
            
                // Pre computation
                double fb = data / model;
                double fc = (1.0 - fb);
                double fa = fb / model;
                
                // Loop over columns
                for (int jdev = 0; jdev < ndev; ++jdev) {
                
                    // Initialise computation
                    register int jpar    = inx[jdev];
                    double       g       = grad(jpar);
                    double       fa_i    = fa * g;
                    
                    // Update gradient
                    (*m_gradient)(jpar) += fc * g;
                    
                    // Loop over rows
                    register int* ipar = inx;
                    for (register int idev = 0; idev < ndev; ++idev, ++ipar)
                        values[idev] = fa_i * grad(*ipar);
                    
                    // Add column to matrix
                    m_covar->add_col(values, inx, ndev, jpar);
                }
            }
            
            // ... handle now data=0
            else {
                register int* ipar = inx;
                for (register int idev = 0; idev < ndev; ++idev, ++ipar)
                    (*m_gradient)(*ipar) += grad(*ipar);
            }
        
        } // endfor: iterated over all data bins

        // Release stack
        m_covar->stack_destroy();

    } while(0); // endwhile: main loop

    // Free temporary memory
    if (values != NULL) delete [] values;
    if (inx    != NULL) delete [] inx;

    // Timing measurement
    #if G_EVAL_TIMING
    double t_elapse = (double)(clock() - t_start) / (double)CLOCKS_PER_SEC;
    std::cout << "GData::optimizer::eval: CPU usage = "
              << t_elapse << " sec" << std::endl;
    #endif
    
    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                     GData::optimizer private methods                    =
 =                                                                         =
 ==========================================================================*/

/***********************************************************************//**
 * @brief Initialise class members
 ***************************************************************************/
void GData::optimizer::init_members(void)
{
    // Initialise members
    m_value    = 0.0;
    m_gradient = NULL;
    m_covar    = NULL;
    m_data     = NULL;

    // Return
    return;
}


/***********************************************************************//**
 * @brief Copy class members
 *
 * @param[in] fct GData::optimizer members to be copied.
 ***************************************************************************/
void GData::optimizer::copy_members(const optimizer& fct)
{
    // Copy attributes
    m_value = fct.m_value;
    
    // Copy gradient if it exists
    if (fct.m_gradient != NULL)
        m_gradient = new GVector(*fct.m_gradient);

    // Copy covariance matrix if it exists
    if (fct.m_covar != NULL)
        m_covar = new GSparseMatrix(*fct.m_covar);
    
    // Return
    return;
}


/***********************************************************************//**
 * @brief Delete class members
 ***************************************************************************/
void GData::optimizer::free_members(void)
{
    // Free members
	if (m_gradient != NULL) delete m_gradient;
	if (m_covar    != NULL) delete m_covar;
    
    // Signal free pointers
    m_gradient = NULL;
    m_covar    = NULL;

    // Return
    return;
}


/*==========================================================================
 =                                                                         =
 =                         GData::optimizer friends                        =
 =                                                                         =
 ==========================================================================*/

/*==========================================================================
 =                                                                         =
 =                  Other functions used by GData::optimizer               =
 =                                                                         =
 ==========================================================================*/
