////////////////////////////////////////////////////////////////////////////////
// STEPS - STochastic Engine for Pathway Simulation
// Copyright (C) 2005-2007 Stefan Wils. All rights reserved.
//
// $Id$
////////////////////////////////////////////////////////////////////////////////

// Autotools definitions.
#ifdef HAVE_CONFIG_H
#include <steps/config.h>
#endif

// STL headers.
#include <cassert>
#include <string>

// STEPS headers.
#include <steps/common.h>
#include <steps/sim/shared/diffdef.hpp>
#include <steps/sim/shared/statedef.hpp>

USING(std, string);

////////////////////////////////////////////////////////////////////////////////

DiffDef::DiffDef(StateDef * sdef, uint gidx, string const & name)
: pStateDef(sdef)
, pFinalSetupFinished(false)
, pGIDX(gidx)
, pName(name)
, pDcst(0.0)
, pLig(0xFFFF)
{
}

////////////////////////////////////////////////////////////////////////////////

void DiffDef::setupFinal(void)
{
    assert(pFinalSetupFinished == false);
    pFinalSetupFinished = true;
}

////////////////////////////////////////////////////////////////////////////////

void DiffDef::setDcst(double const & d)
{
    assert(pFinalSetupFinished == false);
    pDcst = d;
}

////////////////////////////////////////////////////////////////////////////////

void DiffDef::setLig(uint gidx)
{
    assert(pFinalSetupFinished == false);
    pLig = gidx;
}

////////////////////////////////////////////////////////////////////////////////

// END
