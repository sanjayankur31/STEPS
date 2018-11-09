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


// Standard library & STL headers.
#include <cassert>
#include <vector>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/tetexact/kproc.hpp"

#include "easylogging++.h"
////////////////////////////////////////////////////////////////////////////////

namespace stex = steps::tetexact;

////////////////////////////////////////////////////////////////////////////////

stex::KProc::KProc()
: rExtent(0)
, pFlags(0)
, pSchedIDX(0)
 
{
}

////////////////////////////////////////////////////////////////////////////////

stex::KProc::~KProc()
= default;

////////////////////////////////////////////////////////////////////////////////

void stex::KProc::setActive(bool active)
{
    if (active == true) { pFlags &= ~INACTIVATED;
    } else { pFlags |= INACTIVATED;
}
}

////////////////////////////////////////////////////////////////////////////////

uint stex::KProc::getExtent() const
{
    return rExtent;
}

////////////////////////////////////////////////////////////////////////////////

void stex::KProc::resetExtent()
{
    rExtent = 0;
}
////////////////////////////////////////////////////////////////////////////////

void stex::KProc::resetCcst() const
{
    // This should never get called on base object
    AssertLog(false);
}

////////////////////////////////////////////////////////////////////////////////

double stex::KProc::c() const
{
    // Should never get called on base object
    AssertLog(false);
}

////////////////////////////////////////////////////////////////////////////////

double stex::KProc::h()
{
    // Should never get called on base object
    AssertLog(false);
}

////////////////////////////////////////////////////////////////////////////////

// END