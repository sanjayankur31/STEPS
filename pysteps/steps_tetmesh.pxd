# -*- coding: utf-8 -*-
# =====================================================================================================================
# These bindings were automatically generated by cyWrap. Please do dot modify.
# Additional functionality shall be implemented in sub-classes.
#
__copyright__ = "Copyright 2016 EPFL BBP-project"
# =====================================================================================================================
from cython.operator cimport dereference as deref
from libcpp cimport bool
from steps_common cimport *
cimport std
cimport steps_wm
cimport steps
from steps_common cimport *


# ======================================================================================================================
cdef extern from "math/point.hpp" namespace "steps::math":
# ----------------------------------------------------------------------------------------------------------------------
    cdef cppclass point3d:
        point3d()
        point3d(double, double, double)

    double distance(const point3d&, const point3d&)


# ======================================================================================================================
cdef extern from "geom/tmpatch.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for TmPatch ######
    cdef cppclass TmPatch:
        TmPatch(std.string, Tetmesh&, std.vector[steps.index_t], steps_wm.Comp&, steps_wm.Comp*) except +
        std.vector[bool] isTriInside(std.vector[steps.index_t]) except +
        std.vector[steps.index_t] getAllTriIndices()
        std.vector[double] getBoundMin()
        std.vector[double] getBoundMax()
        std.vector[EndocyticZone*] getAllEndocyticZones()


# ======================================================================================================================
cdef extern from "geom/memb.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef Memb* MembP
    # ctypedef std.map[std.string,Memb*] MembPMap
    # ctypedef std.map[std.string,Memb*].iterator MembPMapI
    # ctypedef std.map[std.string,Memb*].const_iterator MembPMapCI
    # ctypedef std.vector[Memb*] MembPVec
    # ctypedef std.vector[Memb*].iterator MembPVecI
    # ctypedef std.vector[Memb*].const_iterator MembPVecCI

    ###### Cybinding for Memb ######
    cdef cppclass Memb:
        Memb(std.string, Tetmesh&, std.vector[TmPatch*], std.vector[TmComp*], bool, uint, double, std.string) except +
        Tetmesh& getContainer()
        std.string getID()
        std.vector[bool] isTriInside(std.vector[steps.index_t]) except +
        std.vector[steps.index_t] getAllTriIndices()
        uint countTris()
        std.vector[steps.index_t] getAllVolTetIndices()
        uint countVolTets()
        std.vector[steps.index_t] getAllVirtTriIndices()
        uint countVirtTris()
        std.vector[steps.index_t] getAllVertIndices()
        uint countVerts()
        bool open()


# ======================================================================================================================
cdef extern from "geom/tmcomp.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for TmComp ######
    cdef cppclass TmComp:
        TmComp(std.string, Tetmesh&, std.vector[steps.index_t]) except +
        void setVol(double vol) except +
        std.vector[steps.index_t] getAllTetIndices()
        uint countTets()
        std.vector[bool] isTetInside(std.vector[steps.index_t]) except +
        std.vector[double] getBoundMin()
        std.vector[double] getBoundMax()


# ======================================================================================================================
cdef extern from "geom/endocyticzone.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for EndocyticZone ######
    cdef cppclass EndocyticZone:
        EndocyticZone(std.string, TmPatch&, std.vector[steps.index_t]) except +
        std.string getID() except +
        TmPatch& getPatch() except +
        std.vector[steps.triangle_global_id] getAllTriIndices() except +


# ======================================================================================================================
cdef extern from "geom/diffboundary.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef DiffBoundary* DiffBoundaryP
    # ctypedef std.map[std.string,DiffBoundary*] DiffBoundaryPMap
    # ctypedef std.map[std.string,DiffBoundary*].iterator DiffBoundaryPMapI
    # ctypedef std.map[std.string,DiffBoundary*].const_iterator DiffBoundaryPMapCI
    # ctypedef std.vector[DiffBoundary*] DiffBoundaryPVec
    # ctypedef std.vector[DiffBoundary*].iterator DiffBoundaryPVecI
    # ctypedef std.vector[DiffBoundary*].const_iterator DiffBoundaryPVecCI

    ###### Cybinding for DiffBoundary ######
    cdef cppclass DiffBoundary:
        DiffBoundary(std.string, Tetmesh&, std.vector[steps.index_t]) except +
        std.string getID()
        void setID(std.string) except +
        Tetmesh& getContainer()
        std.vector[bool] isTriInside(std.vector[steps.index_t]) except +
        std.vector[steps.index_t] getAllTriIndices()
        std.vector[steps_wm.Comp*] getComps()

# ======================================================================================================================
cdef extern from "geom/sdiffboundary.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for SDiffBoundary ######
    cdef cppclass SDiffBoundary:
        SDiffBoundary(std.string, Tetmesh&, std.vector[steps.index_t], std.vector[TmPatch*]) except +
        std.string getID()
        void setID(std.string) except +
        Tetmesh& getContainer()
        std.vector[bool] isBarInside(std.vector[steps.index_t]) except +
        std.vector[steps.index_t] getAllBarIndices()
        std.vector[steps_wm.Patch*] getPatches()

# ======================================================================================================================
cdef extern from "geom/tetmesh.hpp" namespace "steps::tetmesh":
# ----------------------------------------------------------------------------------------------------------------------
    cdef enum ElementType:
        ELEM_VERTEX
        ELEM_TRI
        ELEM_TET
        ELEM_UNDEFINED

    ###### Cybinding for ROISet ######
    cdef cppclass ROISet:
        ElementType type
        std.vector[steps.index_t] indices
        ROISet()
        ROISet(ElementType, std.set[steps.index_t])

    ###### Cybinding for Tetmesh ######
    cdef cppclass Tetmesh:
        # All but a few functions can throw excepts- implement for all but the countXXXs functions
        Tetmesh(std.vector[double], std.vector[steps.index_t], std.vector[steps.index_t]) except +
        std.vector[double] getVertex(steps.vertex_id_t) except +
        steps.index_t countVertices()
        std.vector[steps.index_t] getBar(steps.bar_id_t) except +
        steps.index_t countBars()
        std.vector[steps.index_t] getTri(steps.triangle_global_id) except +
        steps.index_t countTris()
        double getTriArea(steps.triangle_global_id) except +
        std.vector[steps.index_t] getTriBars(steps.triangle_global_id) except +
        std.vector[double] getTriBarycenter(steps.triangle_global_id) except +
        std.vector[double] getTriNorm(steps.triangle_global_id) except +
        TmPatch* getTriPatch(steps.triangle_global_id) except +
        void setTriPatch(steps.triangle_global_id, TmPatch*) except +
        void setTriDiffBoundary(steps.triangle_global_id, DiffBoundary*) except +
        DiffBoundary* getTriDiffBoundary(steps.triangle_global_id) except +
        SDiffBoundary * getBarSDiffBoundary(steps.index_t bidx) except +
        std.vector[steps.index_t] getTriTetNeighb(steps.triangle_global_id) except +
        std.vector[steps.index_t] getTriTriNeighb(steps.triangle_global_id, TmPatch*) except +
        std.vector[steps.index_t] getTriTriNeighbs(steps.triangle_global_id) except +
        std.vector[steps.index_t] getTet(steps.tetrahedron_global_id) except +
        steps.index_t countTets()
        double getTetVol(steps.tetrahedron_global_id) except +
        double getTetQualityRER(steps.tetrahedron_global_id) except +
        std.vector[double] getTetBarycenter(steps.tetrahedron_global_id) except +
        TmComp* getTetComp(steps.tetrahedron_global_id) except +
        void setTetComp(steps.tetrahedron_global_id, TmComp*) except +
        std.vector[steps.index_t] getTetTriNeighb(steps.tetrahedron_global_id) except +
        std.vector[steps.index_t] getTetTetNeighb(steps.tetrahedron_global_id) except +
        steps.tetrahedron_global_id findTetByPoint(std.vector[double]) except +
        bool isPointInTet(std.vector[double], steps.tetrahedron_global_id) except +
        std.vector[double] getBoundMin() except +
        std.vector[double] getBoundMax() except +
        double getMeshVolume() except +
        std.vector[steps.index_t] getSurfTris() except +
        std.vector[double] getBatchTetBarycenters(std.vector[steps.tetrahedron_global_id]) except +
        void getBatchTetBarycentersNP(steps.tetrahedron_global_id*, int, double*, int) except +
        std.vector[double] getBatchTriBarycenters(std.vector[steps.tetrahedron_global_id]) except +
        void getBatchTriBarycentersNP(steps.tetrahedron_global_id*, int, double*, int) except +
        std.vector[double] getBatchVertices(std.vector[steps.index_t]) except +
        void getBatchVerticesNP(steps.index_t*, int, double*, int) except +
        std.vector[steps.index_t] getBatchTris(std.vector[steps.index_t]) except +
        void getBatchTrisNP(steps.index_t*, int, steps.index_t*, int) except +
        std.vector[steps.index_t] getBatchTets(std.vector[steps.index_t]) except +
        void getBatchTetsNP(steps.index_t*, int, steps.index_t*, int) except +
        steps.index_t getTriVerticesSetSizeNP(steps.index_t*, int) except +
        steps.index_t getTetVerticesSetSizeNP(steps.index_t*, int) except +
        void getTriVerticesMappingSetNP(steps.index_t*, int, steps.index_t*, int, steps.index_t*, int) except +
        void getTetVerticesMappingSetNP(steps.index_t*, int, steps.index_t*, int, steps.index_t*, int) except +
        void genPointsInTet(steps.tetrahedron_global_id, steps.index_t, double*, unsigned) except +
        void genPointsInTri(steps.triangle_global_id, steps.index_t, double*, int) except +
        void genTetVisualPointsNP(steps.index_t*, int, uint*, int, double*, int) except +
        void genTriVisualPointsNP(steps.index_t*, int, uint*, int, double*, int) except +
        void getBatchTetVolsNP(steps.index_t*, int, double*, int) except +
        void getBatchTriAreasNP(steps.index_t*, int, double*, int) except +
        void reduceBatchTetPointCountsNP(steps.index_t*, int, uint*, int, double) except +
        void reduceBatchTriPointCountsNP(steps.index_t*, int, uint*, int, double) except +
        void addROI(std.string, ElementType, std.set[steps.index_t]) except +
        void removeROI(std.string) except +
        void replaceROI(std.string, ElementType, std.set[steps.index_t]) except +
        ElementType getROIType(std.string) except +
        std.vector[steps.index_t] getROIData(std.string) except +
        steps.index_t getROIDataSize(std.string) except +
        steps.index_t getNROIs() except +
        ROISet getROI(std.string) except +
        std.vector[std.string] getAllROINames() except +
        bool checkROI(std.string, ElementType, steps.index_t, bool) except +
        std.vector[double] getROITetBarycenters(std.string) except +
        void getROITetBarycentersNP(std.string, double*, int) except +
        std.vector[double] getROITriBarycenters(std.string) except +
        void getROITriBarycentersNP(std.string, double*, int) except +
        std.vector[double] getROIVertices(std.string) except +
        void getROIVerticesNP(std.string, double*, int) except +
        std.vector[steps.index_t] getROITris(std.string) except +
        void getROITrisNP(std.string, steps.index_t*, int) except +
        std.vector[steps.index_t] getROITets(std.string) except +
        void getROITetsNP(std.string, steps.index_t*, int) except +
        steps.index_t getROITriVerticesSetSizeNP(std.string) except +
        steps.index_t getROITetVerticesSetSizeNP(std.string) except +
        void getROITriVerticesMappingSetNP(std.string, steps.index_t*, int, steps.index_t*, int) except +
        void getROITetVerticesMappingSetNP(std.string, steps.index_t*, int, steps.index_t*, int) except +
        void genROITetVisualPointsNP(std.string, uint*, int, double*, int) except +
        void genROITriVisualPointsNP(std.string, uint*, int, double*, int) except +
        void getROITetVolsNP(std.string, double*, int) except +
        void getROITriAreasNP(std.string, double*, int) except +
        double getROIVol(std.string) except +
        double getROIArea(std.string) except +
        void reduceROITetPointCountsNP(std.string, uint*, int, double) except +
        void reduceROITriPointCountsNP(std.string, uint*, int, double) except +
        void setBarSDiffBoundary(steps.index_t bidx, SDiffBoundary sdiffb) except +
        std.set[steps.index_t] getBarTriNeighbs(steps.index_t bidx) except +
        void setBarTris(steps.index_t bidx, steps.index_t itriidx, steps.index_t otriidx) except +
        std.vector[std.vector[std.pair[steps.index_t, double]]] intersect(const double*, int) except+
        std.vector[std.vector[std.pair[steps.index_t, double]]] intersect(const double*, int, int) except+
        std.vector[std.vector[std.pair[steps.index_t, double]]] intersectIndependentSegments(const double*, int) except+
        std.vector[std.vector[std.pair[steps.index_t, double]]] intersectIndependentSegments(const double*, int, int) except+
