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


#ifndef STEPS_WMDIRECT_COMP_HPP
#define STEPS_WMDIRECT_COMP_HPP 1


// STL headers.
#include <cassert>
#include <vector>
#include <fstream>

// STEPS headers.
#include "steps/common.h"
#include "steps/wmdirect/kproc.hpp"
#include "steps/wmdirect/patch.hpp"
#include "steps/solver/compdef.hpp"
#include "steps/solver/types.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace steps{
namespace wmdirect{

////////////////////////////////////////////////////////////////////////////////

// Forward declarations.
class Comp;
class Wmdirect;

// Auxiliary declarations.
typedef Comp *                          CompP;
typedef std::vector<CompP>              CompPVec;
typedef CompPVec::iterator              CompPVecI;
typedef CompPVec::const_iterator        CompPVecCI;

////////////////////////////////////////////////////////////////////////////////

class Comp
{

public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    Comp(steps::solver::Compdef * compdef);
    ~Comp();

    ////////////////////////////////////////////////////////////////////////
    // CHECKPOINTING
    ////////////////////////////////////////////////////////////////////////
    /// checkpoint data
    void checkpoint(std::fstream & cp_file);

    /// restore data
    void restore(std::fstream & cp_file);

    ////////////////////////////////////////////////////////////////////////

    void setupKProcs(Wmdirect * wmd);
    void setupDeps();

    void reset();

    ////////////////////////////////////////////////////////////////////////
    // DATA ACCESS
    ////////////////////////////////////////////////////////////////////////

    inline steps::solver::Compdef * def() const
    { return pCompdef; }

    ////////////////////////////////////////////////////////////////////////

    inline std::vector<steps::wmdirect::KProc *>::const_iterator kprocBegin() const
    { return pKProcs.begin(); }
    inline std::vector<steps::wmdirect::KProc *>::const_iterator kprocEnd() const
    { return pKProcs.end(); }
    inline uint countKProcs() const
    { return pKProcs.size(); }

    steps::wmdirect::KProc * reac(uint lridx) const;

    ////////////////////////////////////////////////////////////////////////

    void addIPatch(Patch * p);

    inline uint countIPatches() const
    { return pIPatches.size(); }

    inline std::vector<steps::wmdirect::Patch *>::const_iterator beginIPatches() const
    { return pIPatches.begin(); }
    inline std::vector<steps::wmdirect::Patch *>::const_iterator  endIPatches() const
    { return pIPatches.end(); }

    void addOPatch(Patch * p);

    inline uint countOPatches() const
    { return pOPatches.size(); }

    inline std::vector<steps::wmdirect::Patch *>::const_iterator  beginOPatches() const
    { return pOPatches.begin(); }
    inline std::vector<steps::wmdirect::Patch *>::const_iterator  endOPatches() const
    { return pOPatches.end(); }

    ////////////////////////////////////////////////////////////////////////

private:

    ////////////////////////////////////////////////////////////////////////

    steps::solver::Compdef *              pCompdef;

    /// The kinetic processes.
    std::vector<steps::wmdirect::KProc *> pKProcs;

    std::vector<steps::wmdirect::Patch *> pIPatches;
    std::vector<steps::wmdirect::Patch *> pOPatches;

    ////////////////////////////////////////////////////////////////////////

};

////////////////////////////////////////////////////////////////////////////////

}
}

#endif
// STEPS_WMDIRECT_COMP_HPP

// END
