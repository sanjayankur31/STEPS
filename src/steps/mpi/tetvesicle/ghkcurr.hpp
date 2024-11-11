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

#pragma once

// Standard library & STL headers.
#include <string>
#include <vector>

// STEPS headers.
#include "math/constants.hpp"
#include "mpi/tetvesicle/kproc.hpp"
#include "mpi/tetvesicle/tri_rdef.hpp"
#include "solver/ghkcurrdef.hpp"

namespace steps::mpi::tetvesicle {

// Forward declarations.
class TetVesicleRDEF;

////////////////////////////////////////////////////////////////////////////////

class GHKcurr: public KProc {
  public:
    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    GHKcurr(solver::GHKcurrdef* ghkdef, TriRDEF* tri);
    GHKcurr(const GHKcurr&) = delete;
    ~GHKcurr();

    ////////////////////////////////////////////////////////////////////////
    // CHECKPOINTING
    ////////////////////////////////////////////////////////////////////////
    /// checkpoint data
    void checkpoint(std::fstream& cp_file) override;

    /// restore data
    void restore(std::fstream& cp_file) override;

    ////////////////////////////////////////////////////////////////////////
    // VIRTUAL INTERFACE METHODS
    ////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

    void setupDeps() override;

    void reset() override;

    double rate(TetVesicleRDEF* solver = nullptr) override;

    void apply(const rng::RNGptr& rng,
               double dt,
               double simtime,
               double period,
               TetVesicleRDEF* solver = nullptr) override;

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

    ////////////////////////////////////////////////////////////////////////

    inline bool efflux() const noexcept {
        return pEffFlux;
    }

    void setEffFlux(bool efx) noexcept {
        pEffFlux = efx;
    }

    //////////////// ADDED FOR MPI STEPS ////////////////////

    std::vector<KProc*> const& getLocalUpdVec(int direction = -1) const override;
    std::vector<solver::kproc_global_id> const& getRemoteUpdVec(int direction = -1) const override;

    void resetOccupancies() override;

    bool getInHost() const noexcept override {
        return pTri->getInHost();
    }

    int getHost() const noexcept override {
        return pTri->getHost();
    }

    ////////////////////////////////////////////////////////////////////////

  private:
    ////////////////////////////////////////////////////////////////////////

    solver::GHKcurrdef* pGHKcurrdef;
    TriRDEF* pTri;

    std::vector<KProc*> localUpdVec;
    std::vector<solver::kproc_global_id> remoteUpdVec;

    // Flag if flux is outward, positive flux (true) or inward, negative flux
    // (false)
    bool pEffFlux;

    ////////////////////////////////////////////////////////////////////////////////
};

}  // namespace steps::mpi::tetvesicle