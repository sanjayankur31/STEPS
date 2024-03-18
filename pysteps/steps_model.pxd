# -*- coding: utf-8 -*-
# =====================================================================================================================
# These bindings were automatically generated by cyWrap. Please do dot modify.
# Additional functionality shall be implemented in sub-classes.
#
__copyright__ = "Copyright 2016 EPFL BBP-project"
# =====================================================================================================================
from cython.operator cimport dereference as deref
from libcpp cimport bool
cimport std
from steps_common cimport *

ctypedef Spec* SpecP

# ======================================================================================================================
cdef extern from "model/fwd.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    cdef enum Immobilization:
        IMMOBILIZING "steps::model::Immobilization::IMMOBILIZING",
        MOBILIZING "steps::model::Immobilization::MOBILIZING",
        NO_EFFECT "steps::model::Immobilization::NO_EFFECT",

# ======================================================================================================================
cdef extern from "model/volsys.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef Volsys* VolsysP
    # ctypedef std.map[std.string, Volsys*] VolsysPMap
    # ctypedef std.map[std.string, Volsys*].iterator VolsysPMapI
    # ctypedef std.map[std.string, Volsys*].const_iterator VolsysPMapCI

    ###### Cybinding for Volsys ######
    cdef cppclass Volsys:
        Volsys(std.string, Model) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Reac& getReac(std.string) except +
        void delReac(std.string) except +
        flat_set[Reac*] getAllReacs()
        flat_set[ComplexReac*] getAllComplexReacs()
        Diff& getDiff(std.string) except +
        void delDiff(std.string) except +
        flat_set[Diff*] getAllDiffs()
        flat_set[Spec*] getAllSpecs()
        VesBind& getVesBind(std.string) except +
        void delVesBind(std.string) except +
        flat_set[VesBind*] getAllVesBinds()
        VesUnbind& getVesUnbind(std.string) except +
        void delVesUnbind(std.string) except +
        flat_set[VesUnbind*] getAllVesUnbinds()

# ======================================================================================================================
cdef extern from "model/chanstate.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef ChanState* ChanStateP
    # ctypedef std.map[std.string,ChanState*] ChanStatePMap
    # ctypedef std.map[std.string,ChanState*].iterator ChanStatePMapI
    # ctypedef std.map[std.string,ChanState*].const_iterator ChanStatePMapCI
    # ctypedef std.vector[ChanState*] ChanStatePVec
    # ctypedef std.vector[ChanState*].iterator ChanStatePVecI
    # ctypedef std.vector[ChanState*].const_iterator ChanStatePVecCI

    ###### Cybinding for ChanState ######
    cdef cppclass ChanState:
        ChanState(std.string, Model, Chan) except +
        Chan& getChan()
        void setID(std.string) except +

# ======================================================================================================================
cdef extern from "model/ghkcurr.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef GHKcurr* GHKcurrP
    # ctypedef std.map[std.string,GHKcurr*] GHKcurrPMap
    # ctypedef std.map[std.string,GHKcurr*].iterator GHKcurrPMapI
    # ctypedef std.map[std.string,GHKcurr*].const_iterator GHKcurrPMapCI
    # ctypedef std.vector[GHKcurr*] GHKcurrPVec
    # ctypedef std.vector[GHKcurr*].iterator GHKcurrPVecI
    # ctypedef std.vector[GHKcurr*].const_iterator GHKcurrPVecCI
    # ctypedef std.map[std.string,double] MyMap

    ###### Cybinding for GHKcurr ######
    cdef cppclass GHKcurr:
        GHKcurr(std.string, Surfsys, ChanState, Spec, bool, double, double) except +
        std.string getID()
        void setID(std.string) except +
        Surfsys& getSurfsys()
        Model& getModel()
        ChanState& getChanState()
        void setChanState(ChanState) except +
        Spec& getIon()
        # Below modified/added by Iain
        void setIon(Spec ion) except +
        double getP() except +
        void setP(double p) except +
        void setPInfo(double g, double V, double T, double oconc, double iconc) except +


# ======================================================================================================================
cdef extern from "model/diff.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef Diff* DiffP
    # ctypedef std.map[std.string,Diff*] DiffPMap
    # ctypedef std.map[std.string,Diff*].iterator DiffPMapI
    # ctypedef std.map[std.string,Diff*].const_iterator DiffPMapCI
    # ctypedef std.vector[Diff*] DiffPVec
    # ctypedef std.vector[Diff*].iterator DiffPVecI
    # ctypedef std.vector[Diff*].const_iterator DiffPVecCI

    ###### Cybinding for Diff ######
    cdef cppclass Diff:
        Diff(std.string, Volsys, Spec, double) except +
        Diff(std.string, Surfsys, Spec, double) except +
        std.string getID()
        void setID(std.string) except +
        Volsys* getVolsys()
        Surfsys* getSurfsys()
        Model& getModel()
        Spec& getLig()
        void setLig(Spec) except +
        double getDcst()
        std.vector[Spec*] getAllSpecs()
        void setDcst(double) except +


# ======================================================================================================================
cdef extern from "model/vdepsreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef VDepSReac* VDepSReacP
    # ctypedef std.map[std.string,VDepSReac*] VDepSReacPMap
    # ctypedef std.map[std.string,VDepSReac*].iterator VDepSReacPMapI
    # ctypedef std.map[std.string,VDepSReac*].const_iterator VDepSReacPMapCI
    # ctypedef std.vector[VDepSReac*] VDepSReacPVec
    # ctypedef std.vector[VDepSReac*].iterator VDepSReacPVecI
    # ctypedef std.vector[VDepSReac*].const_iterator VDepSReacPVecCI

    ###### Cybinding for VDepSReac ######
    cdef cppclass VDepSReac:
        VDepSReac(std.string, Surfsys, std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[double], double, double, double, uint) except +
        std.string getID()
        void setID(std.string) except +
        Surfsys& getSurfsys()
        Model& getModel()
        bool getInner()
        bool getOuter()
        std.vector[Spec*] getOLHS()
        void setOLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getILHS()
        void setILHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSLHS()
        void setSLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getIRHS()
        void setIRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSRHS()
        void setSRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getORHS()
        void setORHS(std.vector[Spec*]) except +
        uint getOrder()
        std.vector[double] getK()
        flat_set[Spec*] getAllSpecs()

# ======================================================================================================================
cdef extern from "model/reac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef Reac* ReacP
    # ctypedef std.map[std.string,Reac*] ReacPMap
    # ctypedef std.map[std.string,Reac*].iterator ReacPMapI
    # ctypedef std.map[std.string,Reac*].const_iterator ReacPMapCI
    # ctypedef std.vector[Reac*] ReacPVec
    # ctypedef std.vector[Reac*].iterator ReacPVecI
    # ctypedef std.vector[Reac*].const_iterator ReacPVecCI

    ###### Cybinding for Reac ######
    cdef cppclass Reac:
        Reac(std.string, Volsys&, std.vector[Spec*], std.vector[Spec*], double) except +
        std.string getID()
        void setID(std.string) except +
        Volsys& getVolsys()
        Model& getModel()
        std.vector[Spec*] getLHS()
        void setLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getRHS()
        void setRHS(std.vector[Spec*]) except +
        flat_set[Spec*] getAllSpecs()
        uint getOrder()
        double getKcst()
        void setKcst(double) except +


# ======================================================================================================================
cdef extern from "model/sreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef SReac* SReacP
    # ctypedef std.map[std.string,SReac*] SReacPMap
    # ctypedef std.map[std.string,SReac*].iterator SReacPMapI
    # ctypedef std.map[std.string,SReac*].const_iterator SReacPMapCI
    # ctypedef std.vector[SReac*] SReacPVec
    # ctypedef std.vector[SReac*].iterator SReacPVecI
    # ctypedef std.vector[SReac*].const_iterator SReacPVecCI

    ###### Cybinding for SReac ######
    cdef cppclass SReac:
        SReac(std.string, Surfsys, std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], double) except +
        std.string getID()
        void setID(std.string) except +
        Surfsys& getSurfsys()
        Model& getModel()
        bool getInner()
        bool getOuter()
        std.vector[Spec*] getOLHS()
        void setOLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getILHS()
        void setILHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSLHS()
        void setSLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getIRHS()
        void setIRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSRHS()
        void setSRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getORHS()
        void setORHS(std.vector[Spec*]) except +
        uint getOrder()
        double getKcst()
        flat_set[Spec*] getAllSpecs()
        void setKcst(double kcst) except +

# ======================================================================================================================
cdef extern from "model/complexevents.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    cdef enum ComplexLocation:
        COMP
        PATCH_IN
        PATCH_SURF
        PATCH_OUT

    cdef struct SubunitStateFilter:
        uint min
        uint max

    cdef cppclass ComplexUpdate:
        ComplexUpdate(std.vector[uint], std.vector[int])

    cdef cppclass ComplexEvent:
        ComplexEvent(std.string)

    cdef cppclass ComplexUpdateEvent:
        ComplexUpdateEvent(std.string, std.vector[std.vector[SubunitStateFilter]], std.vector[uint], std.vector[ComplexUpdate], ComplexLocation) except +

    cdef cppclass ComplexDeleteEvent:
        ComplexDeleteEvent(std.string, std.vector[std.vector[SubunitStateFilter]]) except +

    cdef cppclass ComplexCreateEvent:
        ComplexCreateEvent(std.string, std.vector[uint]) except +

    uint COMPLEX_FILTER_MAX_VALUE

# ======================================================================================================================
cdef extern from "model/complexreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for ComplexReac ######
    cdef cppclass ComplexReac:
        ComplexReac(std.string, Volsys, std.vector[Spec*], std.vector[Spec*], std.vector[ComplexEvent*], double) except +
        std.string getID()
        Volsys& getVolsys()
        Model& getModel()
        std.vector[Spec*] getLHS()
        std.vector[Spec*] getRHS()
        flat_set[Spec*] getAllSpecs()
        uint getOrder()
        double getKcst()
        void setKcst(double) except +

# ======================================================================================================================
cdef extern from "model/complexsreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for ComplexSReac ######
    cdef cppclass ComplexSReac:
        ComplexSReac(std.string, Surfsys, std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[ComplexEvent*], std.vector[ComplexEvent*], std.vector[ComplexEvent*], double) except +
        std.string getID()
        Surfsys& getSurfsys()
        Model& getModel()
        bool getInner()
        bool getOuter()
        std.vector[Spec*] getOLHS()
        std.vector[Spec*] getILHS()
        std.vector[Spec*] getSLHS()
        std.vector[Spec*] getIRHS()
        std.vector[Spec*] getSRHS()
        std.vector[Spec*] getORHS()
        flat_set[Spec*] getAllSpecs()
        uint getOrder()
        double getKcst()
        void setKcst(double) except +

# ======================================================================================================================
cdef extern from "model/chan.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    # ctypedef Chan* ChanP
    # ctypedef std.map[std.string,Chan*] ChanPMap
    # ctypedef std.map[std.string,Chan*].iterator ChanPMapI
    # ctypedef std.map[std.string,Chan*].const_iterator ChanPMapCI
    # ctypedef std.vector[Chan*] ChanPVec
    # ctypedef std.vector[Chan*].iterator ChanPVecI
    # ctypedef std.vector[Chan*].const_iterator ChanPVecCI

    ###### Cybinding for Chan ######
    cdef cppclass Chan:
        Chan(std.string, Model) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        ChanState& getChanState(std.string) except +
        std.vector[ChanState*] getAllChanStates()

# ======================================================================================================================
cdef extern from "model/ohmiccurr.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    ###### Cybinding for OhmicCurr ######
    cdef cppclass OhmicCurr:
        OhmicCurr(std.string, Surfsys, ChanState, double, double) except +
        std.string getID()
        void setID(std.string) except +
        Surfsys& getSurfsys()
        Model& getModel()
        ChanState& getChanState()
        void setChanState(ChanState) except +
        double getERev()
        void setERev(double) except +
        double getG()
        void setG(double g) except +

# ======================================================================================================================
cdef extern from "model/spec.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    ###### Cybinding for Spec ######
    cdef cppclass Spec:
        Spec(std.string, Model, int) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        void setValence(int) except +
        int getValence()


# ======================================================================================================================
cdef extern from "model/complex.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Complex ######
    cdef cppclass Complex:
        Complex(std.string, Model, uint, uint) except +
        std.string getID()
        Model& getModel()


# ======================================================================================================================
cdef extern from "model/surfsys.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    ###### Cybinding for Surfsys ######
    cdef cppclass Surfsys:
        Surfsys(std.string, Model) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        SReac& getSReac(std.string) except +
        void delSReac(std.string) except +
        std.vector[SReac*] getAllSReacs()
        std.vector[ComplexSReac*] getAllComplexSReacs()
        Diff& getDiff(std.string) except +
        void delDiff(std.string) except +
        std.vector[Diff*] getAllDiffs()
        VDepSReac& getVDepSReac(std.string) except +
        void delVDepSReac(std.string) except +
        std.vector[VDepSReac*] getAllVDepSReacs()
        OhmicCurr& getOhmicCurr(std.string) except +
        void delOhmicCurr(std.string) except +
        std.vector[OhmicCurr*] getAllOhmicCurrs()
        GHKcurr& getGHKcurr(std.string) except +
        void delGHKcurr(std.string) except +
        std.vector[GHKcurr*] getAllGHKcurrs()
        RaftGen& getRaftGen(std.string) except +
        void delRaftGen(std.string) except +
        std.vector[RaftGen *] getAllRaftGens()
        Endocytosis& getEndocytosis(std.string) except +
        void delEndocytosis(std.string) except +
        std.vector[Endocytosis *] getAllEndocytosis()
        std.vector[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/model.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    ###### Cybinding for Model ######
    cdef cppclass Model:
        Model()
        Spec& getSpec(std.string) except +
        void delSpec(std.string) except +
        std.vector[Spec*] getAllSpecs()
        LinkSpec& getLinkSpec(std.string) except +
        void delLinkSpec(std.string) except +
        std.vector[LinkSpec *] getAllLinkSpecs()
        Chan& getChan(std.string) except +
        std.vector[Chan*] getAllChans()
        Volsys& getVolsys(std.string) except +
        void delVolsys(std.string) except +
        std.vector[Volsys*] getAllVolsyss()
        Surfsys& getSurfsys(std.string) except +
        void delSurfsys(std.string) except +
        std.vector[Surfsys*] getAllSurfsyss()

        VesSurfsys& getVesSurfsys(std.string) except +
        void delVesSurfsys(std.string) except +
        std.vector[VesSurfsys *] getAllVesSurfsyss()
        Raftsys& getRaftsys(std.string) except +
        void delRaftsys(std.string) except +
        std.vector[Raftsys *] getAllRaftsyss()
        Vesicle& getVesicle(std.string) except +
        std.vector[Vesicle *] getAllVesicles()
        Raft& getRaft(std.string) except +
        std.vector[Raft *] getAllRafts()


# ======================================================================================================================
cdef extern from "model/linkspec.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for LinkSpec ######
    cdef cppclass LinkSpec:
        LinkSpec(std.string, Model, double) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        double getDcst()


# ======================================================================================================================
cdef extern from "model/endocytosis.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Endocytosis ######
    cdef cppclass Endocytosis:
        Endocytosis(std.string, Surfsys, Vesicle*, Vesicle*, std.vector[Spec*], double) except +
        std.string getID()
        void setID(std.string) except +
        Surfsys& getSurfsys()
        Model& getModel()
        bool getInner()
        std.vector[Spec*] getSpecDeps()
        Vesicle& getIRHS()
        double getKcst()
        void setKcst(double) except +
        flat_set[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/exocytosis.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Exocytosis ######
    cdef cppclass Exocytosis:
        Exocytosis(std.string, VesSurfsys, std.vector[Spec*], Raft*, double, bool, std.map[SpecP, SpecP], double) except +
        std.string getID()
        void setID(std.string) except +
        VesSurfsys& getVesSurfsys()
        Model& getModel()
        Raft* getRaft()
        bool getKissAndRun()
        std.map[SpecP, SpecP] getKissAndRunSpecChanges()
        double getKissAndRunPartRelease()
        std.vector[Spec*] getSpecDeps()
        double getKcst()
        void setKcst(double) except +


# ======================================================================================================================
cdef extern from "model/raft.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Raft ######
    cdef cppclass Raft:
        Raft(std.string, Model, double, double) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        double getDiameter()
        double getDcst()
        void setDcst(double) except +
        void addRaftsys(std.string)
        flat_set[std.string] getRaftsys()


# ======================================================================================================================
cdef extern from "model/raftdis.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for RaftDis ######
    cdef cppclass RaftDis:
        RaftDis(std.string, Raftsys, std.vector[Spec*], double) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Raftsys& getRaftsys()
        Raft * getRaft()
        std.vector[Spec*] getSpecSignature()
        flat_set[Spec*] getAllSpecs()
        double getKcst()
        void setKcst(double) except +


# ======================================================================================================================
cdef extern from "model/raftendocytosis.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for RaftEndocytosis ######
    cdef cppclass RaftEndocytosis:
        RaftEndocytosis(std.string, Raftsys, Vesicle*, Vesicle*, std.vector[Spec*], double) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Raftsys& getRaftsys()
        bool getInner()
        std.vector[Spec*] getSpecDeps()
        Vesicle& getRHS()
        double getKcst()
        void setKcst(double) except +
        flat_set[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/raftgen.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for RaftGen ######
    cdef cppclass RaftGen:
        RaftGen(std.string, Surfsys , std.vector[Spec*], Raft, double) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Surfsys& getSurfsys()
        Raft& getRaft()
        std.vector[Spec*] getSpecSignature()
        flat_set[Spec*] getAllSpecs()
        double getKcst()
        void setKcst(double) except +


# ======================================================================================================================
cdef extern from "model/raftsreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for RaftSReac ######
    cdef cppclass RaftSReac:
        RaftSReac(std.string, Raftsys, std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], double, Immobilization) except +
        std.string getID()
        void setID(std.string) except +
        Raftsys& getRaftsys()
        Model& getModel()
        bool getInner()
        bool getOuter()
        std.vector[Spec*] getOLHS()
        void setOLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getILHS()
        void setILHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSLHS()
        void setSLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getRsLHS()
        void setRsLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getIRHS()
        void setIRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSRHS()
        void setSRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getORHS()
        void setORHS(std.vector[Spec*]) except +
        std.vector[Spec*] getRsRHS()
        void setRsRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getRsDeps()
        void setRsDeps(std.vector[Spec*]) except +
        std.vector[Spec*] getAntiRsDeps()
        void setAntiRsDeps(std.vector[Spec*]) except +
        uint getOrder()
        double getKcst()
        void setKcst(double) except +
        flat_set[Spec*] getAllSpecs()
        Immobilization getImmobilization()


# ======================================================================================================================
cdef extern from "model/raftsys.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Raftsys ######
    cdef cppclass Raftsys:
        Raftsys(std.string, Model&) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        RaftSReac& getRaftSReac(std.string) except +
        void delRaftSReac(std.string) except +
        std.vector[RaftSReac*] getAllRaftSReacs()
        RaftEndocytosis& getRaftEndocytosis(std.string) except +
        void delRaftEndocytosis(std.string) except +
        std.vector[RaftEndocytosis*] getAllRaftEndocytosiss()
        RaftDis& getRaftDis(std.string) except +
        void delRaftDis(std.string) except +
        std.vector[RaftDis*] getAllRaftDiss()
        flat_set[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/vesbind.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    ctypedef Vesicle* Vesicle_pointer

    ###### Cybinding for VesBind ######
    cdef cppclass VesBind:
        VesBind(std.string, Volsys, Vesicle, Spec, Vesicle, Spec, LinkSpec, LinkSpec, double, double, std.vector[Spec*], std.vector[Spec*], std.vector[LinkSpec*], std.vector[LinkSpec*], double, Immobilization) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Volsys& getVolsys()
        double getLengthMin()
        double getLengthMax()
        Immobilization getImmobilization()
        std.pair[Vesicle_pointer, Spec*] getReactants1()
        std.pair[Vesicle_pointer, Spec*] getReactants2()
        std.pair[Vesicle_pointer, LinkSpec*] getProducts1()
        std.pair[Vesicle_pointer, LinkSpec*] getProducts2()
        std.vector[Spec*] getAllSpecs()
        double getKcst()
        void setKcst(double) except +
        std.vector[Spec*] getVDeps1()
        std.vector[Spec*] getVDeps2()
        void setVDeps1(std.vector[Spec*])
        void setVDeps2(std.vector[Spec*])
        std.vector[LinkSpec*] getLDeps1()
        std.vector[LinkSpec*] getLDeps2()
        void setLDeps1(std.vector[LinkSpec*])
        void setLDeps2(std.vector[LinkSpec*])


# ======================================================================================================================
cdef extern from "model/vesicle.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for Vesicle ######
    cdef cppclass Vesicle:
        Vesicle(std.string, Model, double, double)
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        double getDiameter()
        double getDcst()
        void setDcst(double) except +
        void addVesSurfsys(std.string)
        flat_set[std.string] getVesSurfsys()


# ======================================================================================================================
cdef extern from "model/vessdiff.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for VesSDiff ######
    cdef cppclass VesSDiff:
        VesSDiff(std.string, VesSurfsys, Spec, double)
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        VesSurfsys& getVesSurfsys()
        Spec& getLig()
        void setLig(Spec)
        double getDcst()
        void setDcst(double) except +
        std.vector[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/vessreac.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for VesSReac ######
    cdef cppclass VesSReac:
        VesSReac(std.string, VesSurfsys, std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[LinkSpec*], std.vector[LinkSpec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], std.vector[Spec*], double, Immobilization, double) except +
        std.string getID()
        void setID(std.string) except +
        VesSurfsys& getVesSurfsys()
        Model& getModel()
        std.vector[Spec*] getOLHS()
        void setOLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSLHS()
        void setSLHS(std.vector[Spec*]) except +
        std.vector[Spec*] getVLHS()
        void setVLHS(std.vector[Spec*]) except +
        std.vector[LinkSpec*] getLLHS()
        void setLLHS(std.vector[LinkSpec*]) except +
        std.vector[Spec*] getIRHS()
        void setIRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getSRHS()
        void setSRHS(std.vector[Spec*]) except +
        std.vector[Spec*] getORHS()
        void setORHS(std.vector[Spec*]) except +
        std.vector[Spec*] getVRHS()
        void setVRHS(std.vector[Spec*]) except +
        std.vector[LinkSpec*] getLRHS()
        void setLRHS(std.vector[LinkSpec*]) except +
        std.vector[Spec*] getVDeps()
        void setVDeps(std.vector[Spec*]) except +
        uint getOrder()
        double getKcst()
        void setKcst(double) except +
        Immobilization getImmobilization()
        double getMaxDistance()
        flat_set[Spec*] getAllSpecs()
        flat_set[LinkSpec*] getAllLinkSpecs()


# ======================================================================================================================
cdef extern from "model/vessurfsys.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------

    ###### Cybinding for VesSurfsys ######
    cdef cppclass VesSurfsys:
        VesSurfsys(std.string, Model&) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        VesSReac& getVesSReac(std.string) except +
        void delVesSReac(std.string) except +
        std.vector[VesSReac*] getAllVesSReacs()
        VesSDiff& getVesSDiff(std.string) except +
        void delVesSDiff(std.string) except +
        std.vector[VesSDiff*] getAllVesSDiffs()
        Exocytosis& getExocytosis(std.string) except +
        void delExocytosis(std.string) except +
        std.vector[Exocytosis*] getAllExocytosis()
        flat_set[Spec*] getAllSpecs()


# ======================================================================================================================
cdef extern from "model/vesunbind.hpp" namespace "steps::model":
# ----------------------------------------------------------------------------------------------------------------------
    #ctypedef Vesicle* Vesicle_pointer

    ###### Cybinding for VesUnbind ######
    cdef cppclass VesUnbind:
        VesUnbind(std.string, Volsys, LinkSpec, LinkSpec, Vesicle, Spec, Vesicle, Spec, double, Immobilization) except +
        std.string getID()
        void setID(std.string) except +
        Model& getModel()
        Volsys& getVolsys()
        Immobilization getImmobilization()
        std.pair[Vesicle_pointer, LinkSpec*]  getLinks1()
        std.pair[Vesicle_pointer, LinkSpec*]  getLinks2()
        std.pair[Vesicle_pointer, Spec*]  getProducts1()
        std.pair[Vesicle_pointer, Spec*]  getProducts2()
        std.vector[Spec*] getAllSpecs()
        double getKcst()
        void setKcst(double) except +
