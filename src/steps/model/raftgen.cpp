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

#include "model/raftgen.hpp"

#include "model/spec.hpp"
#include "model/surfsys.hpp"
#include "util/error.hpp"

namespace steps::model {

////////////////////////////////////////////////////////////////////////////////

RaftGen::RaftGen(std::string const& id,
                 Surfsys& surfsys,
                 std::vector<Spec*> const& spec_signature,
                 Raft& raft,
                 double kcst)
    : pID(id)
    , pModel(surfsys.getModel())
    , pSurfsys(surfsys)
    , pRaft(raft)
    , pKcst(kcst) {
    if (spec_signature.size() == 0) {
        std::ostringstream os;
        os << "No species signature provided to RaftGen initializer function";
        ArgErrLog(os.str());
    }

    if (pKcst < 0.0) {
        std::ostringstream os;
        os << "RaftGen rate can't be negative";
        ArgErrLog(os.str());
    }

    for (auto const& sig: spec_signature) {
        AssertLog(&sig->getModel() == &pModel);
        pSpecSignature.push_back(sig);
    }

    pSurfsys._handleRaftGenAdd(*this);
}

////////////////////////////////////////////////////////////////////////////////

RaftGen::~RaftGen() {
    _handleSelfDelete();
}

////////////////////////////////////////////////////////////////////////////////

void RaftGen::_handleSelfDelete() {
    pSurfsys._handleRaftGenDel(*this);
}

////////////////////////////////////////////////////////////////////////////////

void RaftGen::setKcst(double kcst) {
    if (kcst < 0.0) {
        std::ostringstream os;
        os << "RaftGen rate can't be negative";
        ArgErrLog(os.str());
    }

    pKcst = kcst;
}

////////////////////////////////////////////////////////////////////////////////

void RaftGen::setID(std::string const& id) {
    // The following might raise an exception, e.g. if the new ID is not
    // valid or not unique. If this happens, we don't catch but simply let
    // it pass by into the Python layer.
    pSurfsys._handleRaftGenIDChange(pID, id);
    // This line will only be executed if the previous call didn't raise
    // an exception.
    pID = id;
}

////////////////////////////////////////////////////////////////////////////////

util::flat_set<Spec*> RaftGen::getAllSpecs() const {
    util::flat_set<Spec*> specs;
    const auto& signature = getSpecSignature();
    specs.insert(signature.begin(), signature.end());
    return specs;
}

}  // namespace steps::model
