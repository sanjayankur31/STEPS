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


// STL headers.
#include <cassert>
#include <string>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/geom/comp.hpp"
#include "steps/solver/diffboundarydef.hpp"
#include "steps/solver/statedef.hpp"
#include "steps/solver/types.hpp"

// logging
#include "easylogging++.h"
////////////////////////////////////////////////////////////////////////////////

namespace ssolver = steps::solver;
namespace stetmesh = steps::tetmesh;

////////////////////////////////////////////////////////////////////////////////

ssolver::DiffBoundarydef::DiffBoundarydef(Statedef * sd, uint idx, stetmesh::DiffBoundary * db)
: pStatedef(sd)
, pIdx(idx)
, pName()
, pTris()
, pCompA_temp(nullptr)
, pCompB_temp(nullptr)
, pCompA(0)
, pCompB(0)
, pSetupdone(false)
{
    AssertLog(pStatedef != 0);
    AssertLog(db != 0);

    pName = db->getID();
    pTris = db->_getAllTriIndices();
    std::vector<steps::wm::Comp *> comps = db->getComps();
    pCompA_temp = comps[0];
    pCompB_temp = comps[1];
    AssertLog(pCompA_temp != 0);
    AssertLog(pCompB_temp != 0);

}

////////////////////////////////////////////////////////////////////////////////

ssolver::DiffBoundarydef::~DiffBoundarydef()
= default;

////////////////////////////////////////////////////////////////////////////////

void ssolver::DiffBoundarydef::checkpoint(std::fstream & cp_file)
{
    // reserve
}

////////////////////////////////////////////////////////////////////////////////

void ssolver::DiffBoundarydef::restore(std::fstream & cp_file)
{
    // reserve
}

////////////////////////////////////////////////////////////////////////////////

void ssolver::DiffBoundarydef::setup()
{
    AssertLog(pSetupdone == false);

    pCompA = pStatedef->getCompIdx(pCompA_temp);
    pCompB = pStatedef->getCompIdx(pCompB_temp);
    AssertLog(pCompA >= 0);
    AssertLog(pCompB >= 0);
    pSetupdone = true;

}

////////////////////////////////////////////////////////////////////////////////

std::string const ssolver::DiffBoundarydef::name() const
{
    return pName;
}

////////////////////////////////////////////////////////////////////////////////

