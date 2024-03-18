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

#include <algorithm>
#include <cstddef>
#include <vector>

#include "linsystem.hpp"
#include "util/checkpointing.hpp"

namespace steps::solver::efield {

class LapackBandedMatrix: public AMatrix {
  public:
    LapackBandedMatrix(size_t n, size_t halfbw)
        : pN(n)
        , pData(n * (3 * halfbw + 1))
        , p00(&pData[2 * halfbw])
        , pCStride(3 * halfbw) {}

    void checkpoint(std::fstream& cp_file) {
        util::checkpoint(cp_file, pN);
        util::checkpoint(cp_file, pData);
        util::checkpoint(cp_file, pCStride);
    }

    void restore(std::fstream& cp_file) {
        util::compare(cp_file, pN);
        util::restore(cp_file, pData);
        util::compare(cp_file, pCStride);
    }
    size_t nRow() const override final {
        return pN;
    }
    size_t nCol() const override final {
        return pN;
    }

    double get(size_t row, size_t col) const override final {
        return p00[col * pCStride + row];
    }

    void set(size_t row, size_t col, double value) override final {
        p00[col * pCStride + row] = value;
    }

    void zero() override final {
        std::fill(pData.begin(), pData.end(), 0.0);
    }

    inline double* data() noexcept {
        return pData.data();
    }

  private:
    size_t pN;
    std::vector<double> pData;
    double* p00;
    size_t pCStride;
};

class BDSystemLapack {
  public:
    typedef LapackBandedMatrix matrix_type;
    typedef VVector vector_type;

    BDSystemLapack(size_t n, size_t halfbw)
        : pN(n)
        , pHalfBW(halfbw)
        , pA(n, halfbw)
        , pb(n, 0.0)
        , px(n, 0.0)
        , pwork(n)
        , pb_view(n, pb.data())
        , px_view(n, px.data()) {}

    void checkpoint(std::fstream& cp_file) {
        util::checkpoint(cp_file, pN);
        util::checkpoint(cp_file, pHalfBW);
        pA.checkpoint(cp_file);
        util::checkpoint(cp_file, pb);
        util::checkpoint(cp_file, px);
        util::checkpoint(cp_file, pwork);
    }

    void restore(std::fstream& cp_file) {
        util::compare(cp_file, pN);
        util::compare(cp_file, pHalfBW);
        pA.restore(cp_file);
        util::restore(cp_file, pb);
        util::restore(cp_file, px);
        util::restore(cp_file, pwork);
    }

    const matrix_type& A() const noexcept {
        return pA;
    }
    matrix_type& A() noexcept {
        return pA;
    }

    const vector_type& b() const noexcept {
        return pb_view;
    }
    vector_type& b() noexcept {
        return pb_view;
    }

    const vector_type& x() const noexcept {
        return px_view;
    }

    void solve();  // destructive: overwrites pA

  private:
    size_t pN, pHalfBW;

    LapackBandedMatrix pA;  // will contain L and U after LU-decomposition
    std::vector<double> pb;
    std::vector<double> px;
    std::vector<int> pwork;

    vector_type pb_view;
    vector_type px_view;
};

}  // namespace steps::solver::efield
