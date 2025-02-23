/*
 * Copyright 2021 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(plsync_cc.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(62c873b492855358cd028bc849bb069d)                     */
/***********************************************************************************/

#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/dvbs2rx/plsync_cc.h>
// pydoc.h is automatically generated in the build directory
#include <plsync_cc_pydoc.h>

void bind_plsync_cc(py::module& m)
{

    using plsync_cc = gr::dvbs2rx::plsync_cc;


    py::class_<plsync_cc, gr::block, gr::basic_block, std::shared_ptr<plsync_cc>>(
        m, "plsync_cc", D(plsync_cc))

        .def(py::init(&plsync_cc::make),
             py::arg("gold_code"),
             py::arg("freq_est_period"),
             py::arg("sps"),
             py::arg("debug_level"),
             py::arg("acm_vcm"),
             py::arg("multistream"),
             py::arg("pls_filter_lo"),
             py::arg("pls_filter_hi"),
             D(plsync_cc, make))

        .def(
            "get_freq_offset", &plsync_cc::get_freq_offset, D(plsync_cc, get_freq_offset))

        .def("get_coarse_freq_corr_state",
             &plsync_cc::get_coarse_freq_corr_state,
             D(plsync_cc, get_coarse_freq_corr_state))

        .def("get_locked", &plsync_cc::get_locked, D(plsync_cc, get_locked))

        .def(
            "get_frame_count", &plsync_cc::get_frame_count, D(plsync_cc, get_frame_count))

        .def("get_rejected_count",
             &plsync_cc::get_rejected_count,
             D(plsync_cc, get_rejected_count))

        .def(
            "get_dummy_count", &plsync_cc::get_dummy_count, D(plsync_cc, get_dummy_count))

        .def("get_lock_time", &plsync_cc::get_lock_time, D(plsync_cc, get_lock_time))

        ;
}
