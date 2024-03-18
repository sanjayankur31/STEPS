/*
 #################################################################################
#
#    STEPS - STochastic Engine for Pathway Simulation
#    Copyright (C) 2007-2023 Okinawa Institute of Science and Technology, Japan.
#    Copyright (C) 2003-2006 University of Antwerp, Belgium.
#    
#    See the file AUTHORS for details.
#    This file is part of STEPS.
#    
#    STEPS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License version 3,
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

// STEPS headers.
#include "kproc.hpp"

#include "util/error.hpp"

#include "util/checkpointing.hpp"

namespace steps::tetexact {

KProc::KProc() = default;

////////////////////////////////////////////////////////////////////////////////

KProc::~KProc() = default;

////////////////////////////////////////////////////////////////////////////////

void KProc::checkpoint(std::fstream& cp_file) {
    util::checkpoint(cp_file, rExtent);
    util::checkpoint(cp_file, pFlags);
    util::checkpoint(cp_file, crData);
}

////////////////////////////////////////////////////////////////////////////////

void KProc::restore(std::fstream& cp_file) {
    util::restore(cp_file, rExtent);
    util::restore(cp_file, pFlags);
    util::restore(cp_file, crData);
}

////////////////////////////////////////////////////////////////////////////////

void KProc::setActive(bool active) {
    if (active == true) {
        pFlags &= ~INACTIVATED;
    } else {
        pFlags |= INACTIVATED;
    }
}

////////////////////////////////////////////////////////////////////////////////

unsigned long long KProc::getExtent() const {
    return rExtent;
}

////////////////////////////////////////////////////////////////////////////////

void KProc::resetExtent() {
    rExtent = 0;
}
////////////////////////////////////////////////////////////////////////////////

void KProc::resetCcst() const {
    // This should never get called on base object
    AssertLog(false);
}

////////////////////////////////////////////////////////////////////////////////

double KProc::c() const {
    // Should never get called on base object
    AssertLog(false);
}

////////////////////////////////////////////////////////////////////////////////

double KProc::h() {
    // Should never get called on base object
    AssertLog(false);
}

}  // namespace steps::tetexact
