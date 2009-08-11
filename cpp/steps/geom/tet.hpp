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
// $Id$
////////////////////////////////////////////////////////////////////////////////

#ifndef STEPS_TETMESH_TET_HPP
#define STEPS_TETMESH_TET_HPP 1

// Autotools definitions.
#ifdef HAVE_CONFIG_H
#include <steps/config.h>
#endif

// STEPS headers.
#include <steps/common.h>
#include <steps/geom/tri.hpp>
#include <steps/geom/tetmesh.hpp>
#include <steps/geom/tmcomp.hpp>
#include <steps/rng/rng.hpp>


// STL headers
#include <vector>
#include <ostream>

////////////////////////////////////////////////////////////////////////////////

START_NAMESPACE(steps)
START_NAMESPACE(tetmesh)

////////////////////////////////////////////////////////////////////////////////

// Forward & auxiliary declarations.
//class TmComp;
class Vertex;
class TmPatch;
class Tet;
class Tetmesh;
class Tri;

////////////////////////////////////////////////////////////////////////////////

/// Class Tet is a helper class which provides a view on a tetrahedron
/// whose actual data is stored in the TetMesh object.
///
class Tet
{

public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    /// Constructor.
    ///
    Tet(Tetmesh * mesh, uint tidx);

    /// Destructor.
    ///
    ~Tet(void);

    ////////////////////////////////////////////////////////////////////////
    // TETRAHEDRON INFORMATION
    ////////////////////////////////////////////////////////////////////////

    /// Returns the index of this tetrahedron.
    ///
    uint getIdx(void) const
    { return pTidx; }

    /// Returns the volume of this tetrahedron.
    ///
    double getVol(void) const;

    /// Returns the barycenter of this tetrahedron.
    ///
    std::vector<double> getBarycenter(void) const;

    // Auxiliary method for internal c++ use
    double * _getBarycenter(void) const;

    /// Computes the quality of the tetrahedron.
    ///
    /// This method uses the aspect ratio (AR) metric for tetrahedron
    /// quality, given by dividing the length of the longest edge with
    /// the smallest altitude. The smaller this value, the more regular
    /// the tetrahedron.
    ///
    /// TODO: implement getQualityAR
    ///
    //double getQualityAR(void) const;

    /// Computes the quality of the tetrahedron.
    ///
    /// This method uses the radius-edge ratio (RER) metric for tetrahedron
    /// quality, given by dividing the radius of the tetrahedron's
    /// circumsphere with the length of the shortest edge.
    ///
    /// The smaller this value, the more regular the tetrahedron. The
    /// lowest possible value of this metric is given by computing the
    /// RER for a fully regular tetrahedron:
    ///
    ///    Q = sqrt(6)/4 ~ 0.612
    ///
    /// This is a slightly weaker metric than getQualityAR, because
    /// certain slivers (degenerate tetrahedrons) can still have a fairly
    /// small value.
    ///
    double getQualityRER(void) const;

    ////////////////////////////////////////////////////////////////////////

    /// Returns a pointer to the compartment to which this tetrahedron
    /// belongs. Can return 0, if the tetrahedron has not been added to
    /// any compartment.
    ///
    steps::tetmesh::TmComp * getComp(void) const;

    ////////////////////////////////////////////////////////////////////////
    // NEIGHBOURING TETRAHEDRON INFORMATION
    ////////////////////////////////////////////////////////////////////////

    /// Returns a Tet object encapsulating 1 of the 4 (possible)
    Tet getTet(uint i) const;

    inline Tet getTet0(void) const
    { return getTet(0); }
    inline Tet getTet1(void) const
    { return getTet(1); }
    inline Tet getTet2(void) const
    { return getTet(2); }
    inline Tet getTet3(void) const
    { return getTet(3); }

    ////////////////////////////////////////////////////////////////////////

    int getTetIdx(uint i) const;

    inline int getTet0Idx(void) const
    { return getTetIdx(0); }
    inline int getTet1Idx(void) const
    { return getTetIdx(1); }
    inline int getTet2Idx(void) const
    { return getTetIdx(2); }
    inline int getTet3Idx(void) const
    { return getTetIdx(3); }

    ////////////////////////////////////////////////////////////////////////

    double getTetDist(uint i) const;

    inline double getTet0Dist(void) const
    { return getTetDist(0); }
    inline double getTet1Dist(void) const
    { return getTetDist(1); }
    inline double getTet2Dist(void) const
    { return getTetDist(2); }
    inline double getTet3Dist(void) const
    { return getTetDist(3); }

    ////////////////////////////////////////////////////////////////////////
    // NEIGHBOURING TRIANGLE INFORMATION
    ////////////////////////////////////////////////////////////////////////

    Tri getTri(uint i) const;
    // NOTE: couldn't compile with inline functions
    Tri getTri0(void) const;
    Tri getTri1(void) const;
    Tri getTri2(void) const;
    Tri getTri3(void) const;

    ////////////////////////////////////////////////////////////////////////

    uint getTriIdx(uint i) const;

    inline uint getTri0Idx(void) const
    { return getTriIdx(0); }
    inline uint getTri1Idx(void) const
    { return getTriIdx(1); }
    inline uint getTri2Idx(void) const
    { return getTriIdx(2); }
    inline uint getTri3Idx(void) const
    { return getTriIdx(3); }

    double getTriDist(uint i) const;

    inline double getTri0Dist(void) const
    { return getTriDist(0); }
    inline double getTri1Dist(void) const
    { return getTriDist(1); }
    inline double getTri2Dist(void) const
    { return getTriDist(2); }
    inline double getTri3Dist(void) const
    { return getTriDist(3); }

    ////////////////////////////////////////////////////////////////////////

    double getTriArea(uint i) const;

    inline double getTri0Area(void) const
    { return getTriArea(0); }
    inline double getTri1Area(void) const
    { return getTriArea(1); }
    inline double getTri2Area(void) const
    { return getTriArea(2); }
    inline double getTri3Area(void) const
    { return getTriArea(3); }

    ////////////////////////////////////////////////////////////////////////
    // NEIGHBOURING VERTEX INFORMATION
    ////////////////////////////////////////////////////////////////////////

    uint getVertexIdx(uint i) const;

    inline uint getVertex0Idx(void) const
    { return getVertexIdx(0); }
    inline uint getVertex1Idx(void) const
    { return getVertexIdx(1); }
    inline uint getVertex2Idx(void) const
    { return getVertexIdx(2); }
    inline uint getVertex3Idx(void) const
    { return getVertexIdx(3); }

    std::vector<double> getVertex(uint i) const;

    // Auxiliary function for internal use
    double * _getVertex(uint i) const;

    inline uint getVertex0(void) const
    { return getVertexIdx(0); }
    inline uint getVertex1(void) const
    { return getVertexIdx(1); }
    inline uint getVertex2(void) const
    { return getVertexIdx(2); }
    inline uint getVertex3(void) const
    { return getVertexIdx(3); }


    ////////////////////////////////////////////////////////////////////////
    // OTHER FUNCTIONS
    ////////////////////////////////////////////////////////////////////////

    /// Returns true if the point is inside the tetrahedron.
    ///
    bool isInside(double * p) const;

    /// Generate a number of random points in this tetrahedron. The
    /// default number is 1. Returns a pointer to an array of size N * 3
    /// of doubles.
    ///
    std::vector<double> getRanPnt(steps::rng::RNG * r, uint n = 1) const;

    ////////////////////////////////////////////////////////////////////////

private:

    ////////////////////////////////////////////////////////////////////////

    /// Disable the default constructor.
    ///
    Tet(void);

    /// A pointer to the parent Tetmesh object
    Tetmesh                   * pTetmesh;

    /// The index of this tetrahedron
    uint                        pTidx;

    /// The four vertices of this tetrahedron, by index
    uint                        pVerts[4];

    // The Barycentre- currently calculated each time _getBarycentre is called
    double                    * pBaryc;

};

////////////////////////////////////////////////////////////////////////////////

END_NAMESPACE(tetmesh)
END_NAMESPACE(steps)

#endif
// STEPS_TETMESH_TET_HPP

// END