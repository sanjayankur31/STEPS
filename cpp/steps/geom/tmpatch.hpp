////////////////////////////////////////////////////////////////////////////////
// STEPS - STochastic Engine for Pathway Simulation
// Copyright (C) 2005-2008 Stefan Wils. All rights reserved.
//
// This file is part of STEPS.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA
//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef STEPS_TETMESH_TMPATCH_HPP
#define STEPS_TETMESH_TMPATCH_HPP 1

// Autotools definitions.
#ifdef HAVE_CONFIG_H
#include <steps/config.h>
#endif

// STEPS headers.
#include <steps/common.h>
#include <steps/geom/patch.hpp>
#include <steps/geom/tetmesh.hpp>
#include <steps/model/surfsys.hpp>
#include <steps/geom/tmcomp.hpp>
#include <steps/geom/comp.hpp>

// STL headers
#include <vector>

////////////////////////////////////////////////////////////////////////////////

START_NAMESPACE(steps)
START_NAMESPACE(tetmesh)

////////////////////////////////////////////////////////////////////////////////

// Forward & auxiliary declarations.
class Tetmesh;
class TmComp;

////////////////////////////////////////////////////////////////////////////////

/// Class TmPatch: derived from base wm::Patch class
///
/// - Provides annotation for a group of surface triangles of a tet mesh

class TmPatch : public steps::wm::Patch
{

public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    /// Constructor.
	/// Argument tets is a sequence of triangles (by index) as a vector
	/// of unsigned integers which is represented as a sequence of positive
	/// integer values) in Python
    TmPatch(std::string const & id, Tetmesh * container,
       	 std::vector<uint> const & tris, steps::tetmesh::TmComp* icomp,
       	 steps::tetmesh::TmComp* ocomp = 0, steps::model::Surfsys * surfsys = 0);
	TmPatch(std::string const & id, Tetmesh * container,
		 std::vector<uint> const & tris, steps::wm::Comp* icomp,
			steps::wm::Comp* ocomp = 0, steps::model::Surfsys * surfsys = 0);

    /// Destructor.
    ///
    ~TmPatch(void);

    ////////////////////////////////////////////////////////////////////////
    // PARENT CLASS METHODS
    ////////////////////////////////////////////////////////////////////////

	void setArea(double area);

    ////////////////////////////////////////////////////////////////////////
    // DATA ACCESS (EXPOSED TO PYTHON):
    ////////////////////////////////////////////////////////////////////////

    // return whether triangles (specified by index) are inside this patch
    std::vector<bool> isTriInside(std::vector<uint> tri) const;

    inline std::vector<uint> getAllTriIndices(void) const
    { return pTri_indices; }

    ////////////////////////////////////////////////////////////////////////
    // DATA ACCESS (EXPOSED TO C++)
    ////////////////////////////////////////////////////////////////////////

    inline std::vector<uint> const & _getAllTriIndices(void) const
    { return pTri_indices; }

	////////////////////////////////////////////////////////////////////////

private:

	////////////////////////////////////////////////////////////////////////

	Tetmesh                           * pTetmesh;
	std::vector<uint>                   pTri_indices;
	uint								pTrisN;

////////////////////////////////////////////////////////////////////////////////

};

END_NAMESPACE(tetmesh)
END_NAMESPACE(steps)

#endif
// STEPS_TETMESH_TMPATCH_HPP

// END