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
#include <sstream>
#include <string>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/geom/patch.hpp"

#include "steps/model/model.hpp"

// logging
#include "easylogging++.h"

////////////////////////////////////////////////////////////////////////////////

namespace swm = steps::wm;

////////////////////////////////////////////////////////////////////////////////

swm::Patch::Patch(std::string id, swm::Geom * container, swm::Comp* icomp,
        swm::Comp* ocomp, double area)
: pID(std::move(id))
, pContainer(container)
, pIComp()
, pOComp()
, pSurfsys()
, pArea(area)
{
    if (pContainer == nullptr)
    {
        std::ostringstream os;
        os << "No container provided to Patch initializer function.\n";
        ArgErrLog(os.str());
    }

    _setIComp(icomp);
    if (ocomp != nullptr) {
        _setOComp(ocomp);
    }

    if (pArea < 0.0)
    {
        std::ostringstream os;
        os << "Patch area can't be negative.\n";
        ArgErrLog(os.str());
    }
    pContainer->_handlePatchAdd(this);
}

////////////////////////////////////////////////////////////////////////////////

swm::Patch::~Patch()
{
    if (pContainer == nullptr) {
        return;
    }
    _handleSelfDelete();
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::setID(std::string const & id)
{
    AssertLog(pContainer != nullptr);
    if (id == pID) {
        return;
    }
    // The following might raise an exception, e.g. if the new ID is not
    // valid or not unique. If this happens, we don't catch but simply let
    // it pass by into the Python layer.
    pContainer->_handlePatchIDChange(pID, id);
    // This line will only be executed if the previous call didn't raise
    // an exception.
    pID = id;
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::setArea(double area)
{
    AssertLog(pContainer != nullptr);
    if (area < 0.0)
    {
        std::ostringstream os;
        os << "Patch area can't be negative.\n";
        ArgErrLog(os.str());
    }
    pArea = area;
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::addSurfsys(std::string const & id)
{
    // string identifier is only added to set if it is not already included
    pSurfsys.insert(id);
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::delSurfsys(std::string const & id)
{
    // string identifier is only removed from set if it is included
    pSurfsys.erase(id);
}

////////////////////////////////////////////////////////////////////////////////

std::vector<steps::model::Spec*> swm::Patch::getAllSpecs(steps::model::Model* model)
{
    std::set<steps::model::Spec*> pSpecs;
    for (const auto& id : pSurfsys) {
        steps::model::Surfsys* surfsys = model->getSurfsys(id);
        std::vector<steps::model::Spec*> specs = surfsys->getAllSpecs();
        pSpecs.insert(specs.begin(), specs.end());
    }

    std::vector<steps::model::Spec*> spec_vec(pSpecs.begin(), pSpecs.end());
    return spec_vec;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<steps::model::SReac*> swm::Patch::getAllSReacs(steps::model::Model* model)
{
    std::set<steps::model::SReac*> pSReacs;
    for (const auto& id : pSurfsys) {
        steps::model::Surfsys* surfsys = model->getSurfsys(id);
        std::vector<steps::model::SReac*> sreacs = surfsys->getAllSReacs();
        pSReacs.insert(sreacs.begin(), sreacs.end());
    }

    std::vector<steps::model::SReac*> sreac_vec(pSReacs.begin(), pSReacs.end());
    return sreac_vec;
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::_setIComp(swm::Comp* icomp)
{
    if (icomp->getContainer() != pContainer)
    {
        std::ostringstream os;
        os << "Compartment does not belong to same container as patch.\n";
        ArgErrLog(os.str());
    }
    std::set<swm::Patch *> ipatches  = icomp->getIPatches();
    if (ipatches.find(this) != ipatches.end())
    {
        std::ostringstream os;
        os << "Patch is already on inside of compartment.\n";
        ArgErrLog(os.str());
    }
    // remove the patch if it was already on the outside of some
    // other compartment
    if (pIComp != nullptr)
    {
        pIComp->_delOPatch(this);
    }

    pIComp = icomp;
    pIComp->_addOPatch(this);

}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::_setOComp(swm::Comp* ocomp)
{
    if (ocomp == nullptr) {
        return;
    }

    if (ocomp->getContainer() != pContainer)
    {
        std::ostringstream os;
           os << "Compartment does not belong to same container as patch.\n";
           ArgErrLog(os.str());
    }
    std::set<swm::Patch *> opatches  = ocomp->getOPatches();
    if (opatches.find(this) != opatches.end())
    {
          std::ostringstream os;
          os << "Patch is already on outside of compartment.\n";
           ArgErrLog(os.str());
    }
    // remove the patch if it was already on the inside of some
    // other compartment
    if (pOComp != nullptr)
    {
        pOComp->_delIPatch(this);
    }

    pOComp = ocomp;
    pOComp->_addIPatch(this);
}

////////////////////////////////////////////////////////////////////////////////

void swm::Patch::_handleSelfDelete()
{
    pContainer->_handlePatchDel(this);
    pArea = 0.0;
    pSurfsys.clear();
    pIComp = nullptr;
    pOComp = nullptr;
    pContainer = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

/// END
