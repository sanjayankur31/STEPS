####################################################################################
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
###

########################################################################

# Stochastic second-order irreversible reaction on a surface.
# RESTORE

# AIMS: to verify checkpointing and restoring of the well-mixed stochastic 
# solver 'Wmdirect' in the context of the Second-Order Irreversible 
# Surface Reaction model (see validation/second_order_irev_2D.py)
  
########################################################################

import unittest

import steps.interface

from steps.model import *
from steps.geom import *
from steps.rng import *
from steps.sim import *
from steps.saving import *

import math
import numpy
import os
import random
import time 

from scipy.constants import Avogadro
from . import tol_funcs

########################################################################
VOL = 1.0e-18

COUNTA = 100.0
n=2.0
COUNTB = COUNTA/n 


KCST = 10.0e10			# The reaction constant

AREA = 10.0e-12

CCST = KCST/(Avogadro*AREA)


NITER = 1000			# The number of iterations
DT = 0.05			# Sampling time-step
INT = 1.00			# Sim endtime

# In tests fewer than 0.1% fail with tolerance of 2%
tolerance = 2.0/100

########################################################################

class TestSecondOrderIrev2D(unittest.TestCase):

    def setUp(self):
        mdl = Model()
        r = ReactionManager()
        with mdl:
            SA, SB, SC = Species.Create()
            surfsys = SurfaceSystem.Create()
            with surfsys:
                SA.s + SB.s >r['SR1']> SC.s
                r['SR1'].K = KCST

        geom = Geometry()
        with geom:
            comp1 = Compartment.Create(None, VOL)
            patch1 = Patch.Create(comp1, None, surfsys, AREA)

        rng = RNG('mt19937', 1000, int(random.random()*4294967295))

        sim = Simulation('Wmdirect', mdl, geom, rng)

        sim.newRun()
        sim.patch1.SA.Count = COUNTA
        sim.patch1.SB.Count = COUNTB

        new_dir = './validation_cp/cp/'
        os.makedirs(new_dir, exist_ok=True)

        sim.checkpoint('./validation_cp/cp/second_order_irev_2D')

    def test_soirev2d(self):

        mdl = Model()
        r = ReactionManager()
        with mdl:
            SA, SB, SC = Species.Create()
            surfsys = SurfaceSystem.Create()
            with surfsys:
                SA.s + SB.s >r['SR1']> SC.s
                r['SR1'].K = KCST

        geom = Geometry()
        with geom:
            comp1 = Compartment.Create(None, VOL)
            patch1 = Patch.Create(comp1, None, surfsys, AREA)

        rng = RNG('mt19937', 1000, int(random.random()*4294967295))

        sim = Simulation('Wmdirect', mdl, geom, rng)

        rs = ResultSelector(sim)

        res = rs.patch1.LIST(SA, SB).Count

        sim.toSave(res, dt=DT)

        seed = time.time()%4294967295
        for i in range (0, NITER):
            sim.newRun()
            sim.restore('./validation_cp/cp/second_order_irev_2D')
            rng.initialize(seed)
            seed += 1
            sim.run(INT)

        mean_res = numpy.mean(res.data, 0)

        SC = COUNTA-COUNTB
        for t, (SA, SB) in zip(res.time[0], mean_res):
            lnBA = math.log(SB/SA)
            lineAB = math.log(COUNTB/COUNTA) - SC*CCST*t
            self.assertTrue(tol_funcs.tolerable(lnBA, lineAB, tolerance))


def suite():
    all_tests = []
    all_tests.append(unittest.makeSuite(TestSecondOrderIrev2D, "test"))
    return unittest.TestSuite(all_tests)

if __name__ == "__main__":
    unittest.TextTestRunner(verbosity=2).run(suite())
