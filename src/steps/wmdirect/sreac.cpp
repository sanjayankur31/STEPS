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
// #include <vector>

// STEPS headers.
#include "steps/common.h"
#include "steps/error.hpp"
#include "steps/math/constants.hpp"
#include "steps/wmdirect/comp.hpp"
#include "steps/wmdirect/patch.hpp"
#include "steps/wmdirect/sreac.hpp"
#include "steps/wmdirect/wmdirect.hpp"
// logging
#include "easylogging++.h"
////////////////////////////////////////////////////////////////////////////////

namespace swmd = steps::wmdirect;
namespace ssolver = steps::solver;
namespace smath = steps::math;

////////////////////////////////////////////////////////////////////////////////

static inline double comp_ccst_vol(double kcst, double vol, uint order)
{
    double vscale = 1.0e3 * vol * smath::AVOGADRO;
    int o1 = static_cast<int>(order) - 1;
    // I.H 5/1/2011 Removed this strange special behaviour for zero-order
    // if (o1 < 0) o1 = 0;
    return kcst * pow(vscale, static_cast<double>(-o1));
}

////////////////////////////////////////////////////////////////////////////////

static inline double comp_ccst_area(double kcst, double area, uint order)
{
    double ascale = area * smath::AVOGADRO;
    int o1 = static_cast<int>(order) - 1;
    // I.H 5/1/2011 Removed this strange special behaviour for zero-order
    // if (o1 < 0) o1 = 0;
    return kcst * pow(ascale, static_cast<double>(-o1));
}

////////////////////////////////////////////////////////////////////////////////

swmd::SReac::SReac(ssolver::SReacdef * srdef, swmd::Patch * patch)
: 
 pSReacdef(srdef)
, pPatch(patch)
, pUpdVec()
, pCcst()
{
    AssertLog(pSReacdef != 0);
    AssertLog(pPatch != 0);

    uint lsridx = pPatch->def()->sreacG2L(defsr()->gidx());
    double kcst = pPatch->def()->kcst(lsridx);

    if (defsr()->surf_surf() == false)
    {
        double vol;
        if (defsr()->inside() == true)
        {
            AssertLog(pPatch->iComp() != 0);
            vol = pPatch->iComp()->def()->vol();
        }
        else
        {
            AssertLog(pPatch->oComp() != 0);
            vol = pPatch->oComp()->def()->vol();
        }

        pCcst = comp_ccst_vol(kcst, vol, defsr()->order());
    }
    else
    {
        double area;
        area = pPatch->def()->area();
        pCcst = comp_ccst_area(kcst, area, defsr()->order());
    }

    AssertLog(pCcst >= 0);
}

////////////////////////////////////////////////////////////////////////////////

swmd::SReac::~SReac()
= default;

////////////////////////////////////////////////////////////////////////////////

void swmd::SReac::checkpoint(std::fstream & cp_file)
{
    cp_file.write((char*)&pCcst, sizeof(double));
}

////////////////////////////////////////////////////////////////////////////////

void swmd::SReac::restore(std::fstream & cp_file)
{
    cp_file.read((char*)&pCcst, sizeof(double));
}

////////////////////////////////////////////////////////////////////////////////

bool swmd::SReac::active() const
{
    uint lsridx = pPatch->def()->sreacG2L(defsr()->gidx());
    return pPatch->def()->active(lsridx);
}

////////////////////////////////////////////////////////////////////////////////

void swmd::SReac::setupDeps()
{
    Comp * icomp = pPatch->iComp();
    Comp * ocomp = pPatch->oComp();

    ssolver::gidxTVecCI s_beg = defsr()->beginUpdColl_S();
    ssolver::gidxTVecCI s_end = defsr()->endUpdColl_S();
    ssolver::gidxTVecCI i_beg = defsr()->beginUpdColl_I();
    ssolver::gidxTVecCI i_end = defsr()->endUpdColl_I();
    ssolver::gidxTVecCI o_beg = defsr()->beginUpdColl_O();
    ssolver::gidxTVecCI o_end = defsr()->endUpdColl_O();

    SchedIDXSet updset;

    KProcPVecCI kprocend = pPatch->kprocEnd();
    for (KProcPVecCI k = pPatch->kprocBegin(); k != kprocend; ++k)
    {
        for (ssolver::gidxTVecCI spec = s_beg; spec != s_end; ++spec)
        {
            if ((*k)->depSpecPatch(*spec, pPatch) == true)
                updset.insert((*k)->schedIDX());
        }
    }

    if (icomp != nullptr)
    {
        kprocend = icomp->kprocEnd();
        for (KProcPVecCI k = icomp->kprocBegin(); k != kprocend; ++k)
        {
            for (ssolver::gidxTVecCI spec = i_beg; spec != i_end; ++spec)
            {
                if ((*k)->depSpecComp(*spec, icomp) == true)
                    updset.insert((*k)->schedIDX());
            }
        }

        PatchPVecCI ip_bgn = icomp->beginIPatches();
        PatchPVecCI ip_end = icomp->endIPatches();
        for (PatchPVecCI ip = ip_bgn; ip != ip_end; ++ip)
        {
            kprocend = (*ip)->kprocEnd();
            for (KProcPVecCI k = (*ip)->kprocBegin(); k != kprocend; ++k)
            {
                for (ssolver::gidxTVecCI spec = i_beg; spec != i_end; ++spec)
                {
                    if ((*k)->depSpecComp(*spec, icomp) == true)
                        updset.insert((*k)->schedIDX());
                }
            }
        }

        PatchPVecCI op_bgn = icomp->beginOPatches();
        PatchPVecCI op_end = icomp->endOPatches();
        for (PatchPVecCI op = op_bgn; op != op_end; ++op)
        {
            kprocend = (*op)->kprocEnd();
            for (KProcPVecCI k = (*op)->kprocBegin(); k != kprocend; ++k)
            {
                for (ssolver::gidxTVecCI spec = i_beg; spec != i_end; ++spec)
                {
                    if ((*k)->depSpecComp(*spec, icomp) == true)
                        updset.insert((*k)->schedIDX());
                }
            }
        }
    }

    if (ocomp != nullptr)
    {
        kprocend = ocomp->kprocEnd();
        for (KProcPVecCI k = ocomp->kprocBegin(); k != kprocend; ++k)
        {
            for (ssolver::gidxTVecCI spec = o_beg; spec != o_end; ++spec)
            {
                if ((*k)->depSpecComp(*spec, ocomp) == true)
                    updset.insert((*k)->schedIDX());
            }
        }

        PatchPVecCI ip_bgn = ocomp->beginIPatches();
        PatchPVecCI ip_end = ocomp->endIPatches();
        for (PatchPVecCI ip = ip_bgn; ip != ip_end; ++ip)
        {
            kprocend = (*ip)->kprocEnd();
            for (KProcPVecCI k = (*ip)->kprocBegin(); k != kprocend; ++k)
            {
                for (ssolver::gidxTVecCI spec = o_beg; spec != o_end; ++spec)
                {
                    if ((*k)->depSpecComp(*spec, ocomp) == true)
                        updset.insert((*k)->schedIDX());
                }
            }
        }

        PatchPVecCI op_bgn = ocomp->beginOPatches();
        PatchPVecCI op_end = ocomp->endOPatches();
        for (PatchPVecCI op = op_bgn; op != op_end; ++op)
        {
            kprocend = (*op)->kprocEnd();
            for (KProcPVecCI k = (*op)->kprocBegin(); k != kprocend; ++k)
            {
                for (ssolver::gidxTVecCI spec = o_beg; spec != o_end; ++spec)
                {
                    if ((*k)->depSpecComp(*spec, ocomp) == true)
                        updset.insert((*k)->schedIDX());
                }
            }
        }
    }

    swmd::schedIDXSet_To_Vec(updset, pUpdVec);
}

////////////////////////////////////////////////////////////////////////////////

bool swmd::SReac::depSpecComp(uint gidx, swmd::Comp * comp)
{
    if (comp == pPatch->iComp())
    {
        return (defsr()->dep_I(gidx) != ssolver::DEP_NONE);
    }
    else if (comp == pPatch->oComp())
    {
        return (defsr()->dep_O(gidx) != ssolver::DEP_NONE);
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool swmd::SReac::depSpecPatch(uint gidx, swmd::Patch * patch)
{
    if (patch != pPatch) { return false;
}
    return (defsr()->dep_S(gidx) != ssolver::DEP_NONE);
}

////////////////////////////////////////////////////////////////////////////////

void swmd::SReac::reset()
{
    resetExtent();
    uint lsridx = pPatch->def()->sreacG2L(defsr()->gidx());
    pPatch->def()->setActive(lsridx, true);
    resetCcst();
}

////////////////////////////////////////////////////////////////////////////////

void swmd::SReac::resetCcst()
{
    uint lsridx = pPatch->def()->sreacG2L(defsr()->gidx());
    double kcst = pPatch->def()->kcst(lsridx);

    if (defsr()->surf_surf() == false)
    {
        double vol;
        if (defsr()->inside() == true)
        {
            AssertLog(pPatch->iComp() != 0);
            vol = pPatch->iComp()->def()->vol();
        }
        else
        {
            AssertLog(pPatch->oComp() != 0);
            vol = pPatch->oComp()->def()->vol();
        }

        pCcst = comp_ccst_vol(kcst, vol, defsr()->order());
    }
    else
    {
        double area;
        area = pPatch->def()->area();
        pCcst = comp_ccst_area(kcst, area, defsr()->order());
    }

    AssertLog(pCcst >= 0);
}

////////////////////////////////////////////////////////////////////////////////

double swmd::SReac::rate() const
{
    if (inactive()) { return 0.0;
}

    // First we compute the combinatorial part.
    //   1/ for the surface part of the stoichiometry
    //   2/ for the inner or outer volume part of the stoichiometry, pool
    //      depending on whether the sreac is inner() or outer()
    // Then we multiply with mesoscopic constant.

    ssolver::Patchdef * pdef = pPatch->def();
    uint lidx = pdef->sreacG2L(defsr()->gidx());

    double h_mu = 1.0;

    uint * lhs_s_vec = pdef->sreac_lhs_S_bgn(lidx);
    double * cnt_s_vec = pdef->pools();
    uint nspecs_s = pdef->countSpecs();
    for (uint s = 0; s < nspecs_s; ++s)
    {
        uint lhs = lhs_s_vec[s];
        if (lhs == 0) { continue;
}
        auto cnt = static_cast<uint>(cnt_s_vec[s]);
        if (lhs > cnt)
        {
            return 0.0;
        }
        switch (lhs)
        {
            case 4:
            {
                h_mu *= static_cast<double>(cnt - 3);
            }
            case 3:
            {
                h_mu *= static_cast<double>(cnt - 2);
            }
            case 2:
            {
                h_mu *= static_cast<double>(cnt - 1);
            }
            case 1:
            {
                h_mu *= static_cast<double>(cnt);
                break;
            }
            default:
            {
                AssertLog(0);
                return 0.0;
            }
        }
    }

    if (defsr()->inside())
    {
        uint * lhs_i_vec = pdef->sreac_lhs_I_bgn(lidx);
        double * cnt_i_vec = pPatch->iComp()->def()->pools();
        uint nspecs_i = pdef->countSpecs_I();
        for (uint s = 0; s < nspecs_i; ++s)
        {
            uint lhs = lhs_i_vec[s];
            if (lhs == 0) { continue;
}
            uint cnt = static_cast<double>(cnt_i_vec[s]);
            if (lhs > cnt)
            {
                return 0.0;
            }
            switch (lhs)
            {
                case 4:
                {
                    h_mu *= static_cast<double>(cnt - 3);
                }
                case 3:
                {
                    h_mu *= static_cast<double>(cnt - 2);
                }
                case 2:
                {
                    h_mu *= static_cast<double>(cnt - 1);
                }
                case 1:
                {
                    h_mu *= static_cast<double>(cnt);
                    break;
                }
                default:
                {
                    AssertLog(0);
                    return 0.0;
                }
            }
        }
    }
    else if (defsr()->outside())
    {
        uint * lhs_o_vec = pdef->sreac_lhs_O_bgn(lidx);
        double * cnt_o_vec = pPatch->oComp()->def()->pools();
        uint nspecs_o = pdef->countSpecs_O();
        for (uint s = 0; s < nspecs_o; ++s)
        {
            uint lhs = lhs_o_vec[s];
            if (lhs == 0) { continue;
}
            uint cnt = static_cast<double>(cnt_o_vec[s]);
            if (lhs > cnt)
            {
                return 0.0;
            }
            switch (lhs)
            {
                case 4:
                {
                    h_mu *= static_cast<double>(cnt - 3);
                }
                case 3:
                {
                    h_mu *= static_cast<double>(cnt - 2);
                }
                case 2:
                {
                    h_mu *= static_cast<double>(cnt - 1);
                }
                case 1:
                {
                    h_mu *= static_cast<double>(cnt);
                    break;
                }
                default:
                {
                    AssertLog(0);
                    return 0.0;
                }
            }
        }
    }

    return h_mu * pCcst;
}

////////////////////////////////////////////////////////////////////////////////

std::vector<uint> const & swmd::SReac::apply()
{
    ssolver::Patchdef * pdef = pPatch->def();
    uint lidx = pdef->sreacG2L(defsr()->gidx());

    // Update patch pools.
    int * upd_s_vec = pdef->sreac_upd_S_bgn(lidx);
    double * cnt_s_vec = pdef->pools();
    uint nspecs_s = pdef->countSpecs();

    for (uint s = 0; s < nspecs_s; ++s)
    {
        if (pdef->clamped(s) == true) continue;
        int upd = upd_s_vec[s];
        if (upd == 0) continue;
        int nc = static_cast<int>(cnt_s_vec[s]) + upd;
        AssertLog(nc >= 0);
        pdef->setCount(s, static_cast<double>(nc));
    }

    // Update inner comp pools.
    Comp * icomp = pPatch->iComp();
    if (icomp != 0)
    {
        int * upd_i_vec = pdef->sreac_upd_I_bgn(lidx);
        double * cnt_i_vec = icomp->def()->pools();
        uint nspecs_i = pdef->countSpecs_I();
        for (uint s = 0; s < nspecs_i; ++s)
        {
            if (icomp->def()->clamped(s) == true) continue;
            int upd = upd_i_vec[s];
            if (upd == 0) continue;
            int nc = static_cast<int>(cnt_i_vec[s]) + upd;
            AssertLog(nc >= 0);
            icomp->def()->setCount(s, static_cast<double>(nc));
        }
    }

    // Update outer comp pools.
    Comp * ocomp = pPatch->oComp();
    if (ocomp != 0)
    {
        int * upd_o_vec = pdef->sreac_upd_O_bgn(lidx);
        double * cnt_o_vec = ocomp->def()->pools();
        uint nspecs_o = pdef->countSpecs_O();
        for (uint s = 0; s < nspecs_o; ++s)
        {
            if (ocomp->def()->clamped(s) == true) continue;
            int upd = upd_o_vec[s];
            if (upd == 0) continue;
            int nc = static_cast<int>(cnt_o_vec[s]) + upd;
            AssertLog(nc >= 0);
            ocomp->def()->setCount(s, static_cast<double>(nc));
        }
    }

    rExtent++;
    return pUpdVec;
}

////////////////////////////////////////////////////////////////////////////////

// END

