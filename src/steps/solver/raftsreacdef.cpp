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

#include "solver/raftsreacdef.hpp"

#include "solver/statedef.hpp"
#include "util/checkpointing.hpp"
#include "util/error.hpp"

namespace steps::solver {

RaftSReacdef::RaftSReacdef(Statedef& sd, raftsreac_global_id idx, model::RaftSReac& sr)
    : pIdx(idx)
    , pName(sr.getID())
    , pOrder(sr.getOrder())
    , pKcst(sr.getKcst())
    , pCountSpecs(sd.countSpecs())
    , pImmobility(sr.getImmobilization())
    , pOrient(sr.getInner() ? RaftSReacdef::INSIDE : RaftSReacdef::OUTSIDE)
    , pOlhs(sr.getOLHS())
    , pSlhs(sr.getSLHS())
    , pRslhs(sr.getRsLHS())
    , pIlhs(sr.getILHS())
    , pOrhs(sr.getORHS())
    , pSrhs(sr.getSRHS())
    , pRsrhs(sr.getRsRHS())
    , pIrhs(sr.getIRHS())
    , pRsdep(sr.getRsDeps())
    , pAntiRsdep(sr.getAntiRsDeps()) {
    if (sr.getOrder() == 0) {
        std::ostringstream os;
        os << "\nModel contains zero-order vesicle surface reaction, which are not "
              "permitted. ";
        os << " Zero-order volume reaction may be used instead.\n";
        ArgErrLog(os.str());
    }

    pSpec_S_DEP.container().resize(pCountSpecs, DEP_NONE);
    pSpec_S_LHS.container().resize(pCountSpecs);
    pSpec_S_RHS.container().resize(pCountSpecs);
    pSpec_S_UPD.container().resize(pCountSpecs);

    pSpec_Rs_DEP.container().resize(pCountSpecs, DEP_NONE);
    pSpec_Rs_LHS.container().resize(pCountSpecs);
    pSpec_Rs_RHS.container().resize(pCountSpecs);
    pSpec_Rs_UPD.container().resize(pCountSpecs);

    if (pOrient == RaftSReacdef::INSIDE) {
        pSpec_I_DEP.container().resize(pCountSpecs, DEP_NONE);
        pSpec_I_LHS.container().resize(pCountSpecs);
    }

    else {
        pSpec_O_DEP.container().resize(pCountSpecs, DEP_NONE);
        pSpec_O_LHS.container().resize(pCountSpecs);
    }

    pSpec_O_RHS.container().resize(pCountSpecs);
    pSpec_O_UPD.container().resize(pCountSpecs);

    pSpec_I_RHS.container().resize(pCountSpecs);
    pSpec_I_UPD.container().resize(pCountSpecs);

    pSpec_RsDEP.container().resize(pCountSpecs);
    pSpec_AntiRsDEP.container().resize(pCountSpecs);
}

////////////////////////////////////////////////////////////////////////////////

void RaftSReacdef::checkpoint(std::fstream& /*cp_file*/) const {
    // reserve
}

////////////////////////////////////////////////////////////////////////////////

void RaftSReacdef::restore(std::fstream& /*cp_file*/) {
    // reserve
}

////////////////////////////////////////////////////////////////////////////////

void RaftSReacdef::setup(const Statedef& sd) {
    AssertLog(pSetupdone == false);

    for (auto const& ol: pOlhs) {
        pSurface_surface = false;
        AssertLog(outside());
        spec_global_id sidx = sd.getSpecIdx(*ol);
        pSpec_O_LHS[sidx] += 1;
    }

    for (auto const& sl: pSlhs) {
        spec_global_id sidx = sd.getSpecIdx(*sl);
        pSpec_S_LHS[sidx] += 1;
    }

    for (auto const& rsl: pRslhs) {
        spec_global_id sidx = sd.getSpecIdx(*rsl);
        pSpec_Rs_LHS[sidx] += 1;
    }

    for (auto const& il: pIlhs) {
        pSurface_surface = false;
        AssertLog(inside());
        spec_global_id sidx = sd.getSpecIdx(*il);
        pSpec_I_LHS[sidx] += 1;
    }

    for (auto const& sr: pSrhs) {
        spec_global_id sidx = sd.getSpecIdx(*sr);
        pSpec_S_RHS[sidx] += 1;
    }

    for (auto const& orh: pOrhs) {
        spec_global_id sidx = sd.getSpecIdx(*orh);
        pSpec_O_RHS[sidx] += 1;
    }

    for (auto const& rsrh: pRsrhs) {
        spec_global_id sidx = sd.getSpecIdx(*rsrh);
        pSpec_Rs_RHS[sidx] += 1;
    }

    for (auto const& irh: pIrhs) {
        spec_global_id sidx = sd.getSpecIdx(*irh);
        pSpec_I_RHS[sidx] += 1;
    }

    for (auto const& rsdep: pRsdep) {
        spec_global_id sidx = sd.getSpecIdx(*rsdep);
        pSpec_RsDEP[sidx] += 1;
    }

    for (auto const& anti_rsdep: pAntiRsdep) {
        spec_global_id sidx = sd.getSpecIdx(*anti_rsdep);
        pSpec_AntiRsDEP[sidx] += 1;
    }

    // Now set up the update vector
    uint ngspecs = sd.countSpecs();

    // Deal with surface.
    for (auto s: spec_global_id::range(ngspecs)) {
        int lhs = static_cast<int>(pSpec_S_LHS[s]);
        int rhs = static_cast<int>(pSpec_S_RHS[s]);
        int aux = pSpec_S_UPD[s] = (rhs - lhs);
        if (lhs != 0) {
            pSpec_S_DEP[s] |= DEP_STOICH;
        }
        if (aux != 0) {
            pSpec_S_UPD_Coll.emplace_back(s);
        }
    }

    // Deal with outside.
    for (auto s: spec_global_id::range(ngspecs)) {
        int lhs = (outside() ? static_cast<int>(pSpec_O_LHS[s]) : 0);
        int rhs = static_cast<int>(pSpec_O_RHS[s]);
        int aux = pSpec_O_UPD[s] = (rhs - lhs);
        if (lhs != 0) {
            pSpec_O_DEP[s] |= DEP_STOICH;
        }
        if (aux != 0) {
            pSpec_O_UPD_Coll.emplace_back(s);
        }
    }

    // Deal with vesicle surface.
    for (auto s: spec_global_id::range(ngspecs)) {
        int lhs = static_cast<int>(pSpec_Rs_LHS[s]);
        int rhs = static_cast<int>(pSpec_Rs_RHS[s]);
        int aux = pSpec_Rs_UPD[s] = (rhs - lhs);
        if (lhs != 0) {
            pSpec_Rs_DEP[s] |= DEP_STOICH;
        }
        if (aux != 0) {
            pSpec_Rs_UPD_Coll.emplace_back(s);
        }
    }

    // Deal with inside.
    for (auto s: spec_global_id::range(ngspecs)) {
        int lhs = (inside() ? static_cast<int>(pSpec_I_LHS[s]) : 0);
        int rhs = static_cast<int>(pSpec_I_RHS[s]);
        int aux = pSpec_I_UPD[s] = (rhs - lhs);
        if (lhs != 0) {
            pSpec_I_DEP[s] |= DEP_STOICH;
        }
        if (aux != 0) {
            pSpec_I_UPD_Coll.emplace_back(s);
        }
    }

    pSetupdone = true;
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqOutside() const {
    AssertLog(pSetupdone == true);

    // This can be checked by seeing if DEP_O or RHS_O is non-zero
    // for any species.
    for (auto s: spec_global_id::range(num_specs())) {
        if (reqspec_O(s) == true) {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqInside() const {
    AssertLog(pSetupdone == true);

    // This can be checked by seeing if DEP_I or RHS_I is non-zero
    // for any species.
    for (auto s: spec_global_id::range(num_specs())) {
        if (reqspec_I(s) == true) {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::lhs_S(spec_global_id gidx) const {
    return pSpec_S_LHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::lhs_O(spec_global_id gidx) const {
    if (inside()) {
        return 0;
    }
    return pSpec_O_LHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::lhs_Rs(spec_global_id gidx) const {
    return pSpec_Rs_LHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::lhs_I(spec_global_id gidx) const {
    if (outside()) {
        return 0;
    }
    return pSpec_I_LHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::rsdep(spec_global_id gidx) const {
    return pSpec_RsDEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::anti_rsdep(spec_global_id gidx) const {
    return pSpec_AntiRsDEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::dep_S(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_S_DEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::dep_O(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (inside()) {
        return DEP_NONE;
    }
    return pSpec_O_DEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::dep_Rs(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_Rs_DEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::dep_I(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (outside()) {
        return DEP_NONE;
    }
    return pSpec_I_DEP.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::rhs_S(spec_global_id gidx) const {
    return pSpec_S_RHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::rhs_O(spec_global_id gidx) const {
    return pSpec_O_RHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::rhs_Rs(spec_global_id gidx) const {
    return pSpec_Rs_RHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

uint RaftSReacdef::rhs_I(spec_global_id gidx) const {
    return pSpec_I_RHS.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::upd_S(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_S_UPD.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::upd_O(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_O_UPD.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::upd_Rs(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_Rs_UPD.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

int RaftSReacdef::upd_I(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    return pSpec_I_UPD.at(gidx);
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqspec_S(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (pSpec_S_DEP.at(gidx) != DEP_NONE) {
        return true;
    }
    if (pSpec_S_RHS.at(gidx) != 0) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqspec_O(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (outside()) {
        if (pSpec_O_DEP.at(gidx) != DEP_NONE) {
            return true;
        }
    }
    if (pSpec_O_RHS.at(gidx) != 0) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqspec_Rs(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (pSpec_Rs_DEP.at(gidx) != DEP_NONE) {
        return true;
    }
    if (pSpec_Rs_RHS.at(gidx) != 0) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool RaftSReacdef::reqspec_I(spec_global_id gidx) const {
    AssertLog(pSetupdone == true);
    if (inside()) {
        if (pSpec_I_DEP.at(gidx) != DEP_NONE) {
            return true;
        }
    }
    if (pSpec_I_RHS.at(gidx) != 0) {
        return true;
    }
    return false;
}

}  // namespace steps::solver
