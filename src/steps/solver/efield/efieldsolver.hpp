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

/** \file Abstract interface for solver implementations
 * used by EField objects. */

#include "tetmesh.hpp"

namespace steps::solver::efield {

struct EFieldSolver {
    virtual ~EFieldSolver() = default;
    /** Initialize state with given mesh */
    virtual void initMesh(TetMesh* mesh) = 0;

    /** Checkpoint solver data to file stream */
    virtual void checkpoint(std::fstream& cp_file) = 0;

    /** Restore data from file stream */
    virtual void restore(std::fstream& cp_file) = 0;

    /** Set membrane conductance and reversal potential (for leak current) */
    virtual void setSurfaceConductance(double g_surface, double v_rev) = 0;

    /** Get membrane conductance and reversal potential (for leak current) */
    virtual std::pair<double, double> getSurfaceConductance() = 0;

    /** Set all vertex potentials to v */
    virtual void setPotential(double v) = 0;

    /** Retrieve potential at vertex i */
    virtual double getV(vertex_id_t i) const = 0;

    /** Set potential at vertex i */
    virtual void setV(vertex_id_t i, double v) = 0;

    /** Get voltage clamped status for vertex i */
    virtual bool getClamped(vertex_id_t i) const = 0;

    /** Set voltage clamped status for vertex i */
    virtual void setClamped(vertex_id_t i, bool clamped) = 0;

    /** Get current through triangle i */
    virtual double getTriI(triangle_local_id i) const = 0;

    /** Set current through triangle i to d (pA) */
    virtual void setTriI(triangle_local_id i, double d) = 0;

    /** Set additional current injection for triangle i to c (pA) */
    virtual void setTriIClamp(triangle_local_id i, double c) = 0;

    /** Get additional current injection for triangle i (pA) */
    virtual double getTriIClamp(triangle_local_id i) const = 0;

    /** Set additional current injection for area associated with vertex i to c
     * (pA) */
    virtual void setVertIClamp(vertex_id_t i, double c) = 0;

    /** Get additional current injection for area associated with vertex i (pA) */
    virtual double getVertIClamp(vertex_id_t i) const = 0;

    /** Solve for voltage with given dt */
    virtual void advance(double dt) = 0;
};

}  // namespace steps::solver::efield
