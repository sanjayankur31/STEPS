/*
 #################################################################################
#
#    STEPS - STochastic Engine for Pathway Simulation
#    Copyright (C) 2007-2018 Okinawa Institute of Science and Technology, Japan.
#    Copyright (C) 2003-2006 University of Antwerp, Belgium.
#    
#    See the file AUTHORS for details.
#    This file is part of STEPS.
#    
#    STEPS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License version 2,
#    as published by the Free Software Foundation.
#    
#    STEPS is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#    
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#################################################################################   

 */

/*
 *  Last Changed Rev:  $Rev$
 *  Last Changed Date: $Date$
 *  Last Changed By:   $Author$
 */

// STL headers.
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/model/model.hpp"
#include "steps/model/reac.hpp"
#include "steps/model/spec.hpp"
#include "steps/model/volsys.hpp"

// logging
#include "easylogging++.h"
////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace steps::model;

////////////////////////////////////////////////////////////////////////////////

Reac::Reac(string const & id, Volsys * volsys, vector<Spec *> const & lhs,
           vector<Spec *> const & rhs, double kcst)
: pID(id)
, pModel(nullptr)
, pVolsys(volsys)
, pLHS()
, pRHS()
, pOrder(0)
, pKcst(kcst)
{
    if (pVolsys == nullptr)
    {
        ostringstream os;
        os << "No volsys provided to Reac initializer function";
        ArgErrLog(os.str());
    }
    if (pKcst < 0.0)
    {
        ostringstream os;
        os << "Reaction constant can't be negative";
        ArgErrLog(os.str());
    }

    pModel = pVolsys->getModel();
    AssertLog(pModel != 0);

    setLHS(lhs);
    setRHS(rhs);

    pVolsys->_handleReacAdd(this);
}

////////////////////////////////////////////////////////////////////////////////

Reac::~Reac()
{
    if (pVolsys == nullptr) { return;
}
    _handleSelfDelete();
}

////////////////////////////////////////////////////////////////////////////////

void Reac::_handleSelfDelete()
{
    pVolsys->_handleReacDel(this);
    pKcst = 0.0;
    pOrder = 0;
    pRHS.clear();
    pLHS.clear();
    pVolsys = nullptr;
    pModel = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void Reac::setID(string const & id)
{
    AssertLog(pVolsys != 0);
    // The following might raise an exception, e.g. if the new ID is not
    // valid or not unique. If this happens, we don't catch but simply let
    // it pass by into the Python layer.
    pVolsys->_handleReacIDChange(pID, id);
    // This line will only be executed if the previous call didn't raise
    // an exception.
    pID = id;
}

////////////////////////////////////////////////////////////////////////////////

void Reac::setLHS(vector<Spec *> const & lhs)
{
    AssertLog(pVolsys != 0);
    pLHS.clear();

    SpecPVecCI l_end = lhs.end();
    for (SpecPVecCI l = lhs.begin(); l != l_end; ++l)
    {
        AssertLog((*l)->getModel() == pModel);
        pLHS.push_back(*l);
    }
    pOrder = pLHS.size();
}

////////////////////////////////////////////////////////////////////////////////

void Reac::setRHS(vector<Spec *> const & rhs)
{
    AssertLog(pVolsys != 0);
    pRHS.clear();

    SpecPVecCI r_end = rhs.end();
    for (SpecPVecCI r = rhs.begin(); r != r_end; ++r)
    {
        AssertLog((*r)->getModel() == pModel);
        pRHS.push_back(*r);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Reac::setKcst(double kcst)
{
    AssertLog(pVolsys != 0);
    if (kcst < 0.0)
    {
        ostringstream os;
        os << "Reaction constant can't be negative";
        ArgErrLog(os.str());
    }
    pKcst = kcst;
}

////////////////////////////////////////////////////////////////////////////////

vector<Spec *> Reac::getAllSpecs() const
{
    SpecPVec specs = SpecPVec();
    bool first_occ = true;

    SpecPVec lhs = getLHS();
    SpecPVecCI l_end = lhs.end();
    for (SpecPVecCI l = lhs.begin(); l != l_end; ++l)
    {
        first_occ = true;
        SpecPVecCI s_end = specs.end();
        for (SpecPVecCI s = specs.begin(); s != s_end; ++s)
        {
            if ((*s) == (*l))
            {
                first_occ = false;
                break;
            }
        }
        if (first_occ == true) specs.push_back((*l));
    }

    SpecPVec rhs = getRHS();
    SpecPVecCI r_end = rhs.end();
    for (SpecPVecCI r = rhs.begin(); r != r_end; ++r)
    {
        first_occ = true;
        SpecPVecCI s_end = specs.end();
        for (SpecPVecCI s = specs.begin(); s != s_end; ++s)
        {
            if ((*s) == (*r))
            {
                first_occ = false;
                break;
            }
        }
        if (first_occ == true) specs.push_back((*r));
    }

    return specs;
}

////////////////////////////////////////////////////////////////////////////////

// END