/* -*- c++ -*- */
/*
 * Copyright (c) 2019-2021 Igor Freire
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2RX_PLSC_H
#define INCLUDED_DVBS2RX_PLSC_H

#include "reed_muller.h"
#include <gnuradio/gr_complex.h>
#include <dvbs2rx/api.h>
#include <volk/volk_alloc.hh>

namespace gr {
namespace dvbs2rx {

// PLSC scrambler sequence (see Section 5.5.2.4 of the standard)
const uint64_t plsc_scrambler = 0x719d83c953422dfa;

/**
 * \brief PLSC Encoder
 *
 * Encodes a 7-bit physical layer signalling (PLS) code into a sequence of 64
 * pi/2 BPSK symbols. Implements the PLSC scrambling and pi/2 BPSK mapping.
 */
class DVBS2RX_API plsc_encoder
{
private:
    reed_muller d_reed_muller_encoder;

public:
    /**
     * \brief Encode the PLSC info into the corresponding pi/2 BPSK symbols.
     * \param bpsk_out (gr_complex *) Pointer to output pi/2 BPSK symbols.
     * \param plsc 7-bit PLSC to be mapped into pi/2 BPSK symbols.
     */
    void encode(gr_complex* bpsk_out, const uint8_t plsc);

    /**
     * \brief Encode the PLSC info into the corresponding pi/2 BPSK symbols.
     * \param bpsk_out (gr_complex *) Pointer to output pi/2 BPSK symbols.
     * \param modcod 5-bit modulation and coding scheme.
     * \param short_fecframe False for normal FECFRAME (64800 bits), true for
     *                       short FECFRAME (16200 bits).
     * \param has_pilots Whether the FECFRAME has pilots.
     */
    void encode(gr_complex* bpsk_out,
                const uint8_t modcod,
                bool short_fecframe,
                bool has_pilots);
};


/**
 * \brief PLSC Decoder
 *
 * Decodes a sequence of 64 noisy pi/2 BPSK symbols into the corresponding 7-bit
 * PLS code. Implements the pi/2 BPSK demapping, the PLSC descrambling, and the
 * parsing of the PLSC information.
 */
class DVBS2RX_API plsc_decoder
{
private:
    int d_debug_level; /** debug level */
    reed_muller d_reed_muller_decoder;
    volk::vector<float> d_soft_dec_buf; // Buffer to store the soft decisions

public:
    /* State - made public to speed up access */
    uint8_t dec_plsc;     /** Last decoded PLSC */
    uint8_t modcod;       /** MODCOD of the decoded PLSC */
    bool short_fecframe;  /** Wether FECFRAME size is short */
    bool has_pilots;      /** Wether PLFRAME has pilot blocks */
    bool dummy_frame;     /** Whether PLFRAME is a dummy frame */
    uint8_t n_mod;        /** bits per const symbol */
    uint16_t S;           /** number of slots */
    uint16_t plframe_len; /** PLFRAME length */
    uint8_t n_pilots;     /* number of pilot blocks */

    explicit plsc_decoder(int debug_level = 0);
    ~plsc_decoder(){};

    /**
     * \brief Decode the incoming pi/2 BPSK symbols of the PLSC.
     * \param bpsk_in (const gr_complex *) Input pi/2 BPSK symbols, starting
     *                from the last SOF symbol and followed by the PLSC symbols
     *                (see note 1).
     * \param coherent (bool) Whether to use coherent BPSK demapping (the
     *                 default). When set to false, the decoding uses hard
     *                 decisions produced through differential demapping of the
     *                 pi/2 BPSK symbols, even if soft=true (see note 2).
     * \param soft (bool) Whether to decode the PLSC dataword using soft pi/2
     *             BPSK decisions instead of hard decisions.
     * \return Void.
     *
     * \note 1 - The last SOF symbol is required when coherent=false. In
     * contrast, when coherent=true, the implementation simply skips this
     * symbol. However, note "bpsk_in" must start at the last SOF symbol
     * regardless.
     *
     * \note 2 - The non-coherent (differential) demapping is only supported
     * with hard decisions because there is negligible performance difference
     * when differential demapping is used to produce soft decisions. On the
     * contrary, based on some experiments, it seems that differential demapping
     * with soft decisions would only be slower, and it would produce a similar
     * (if not worse) performance than differential demapping with hard
     * decisions. Ultimately, the supported parameter combinations are:
     * (coherent=true, soft=false), (coherent=true, soft=true), and
     * (coherent=false, soft=false). With (coherent=false, soft=true), the
     * implementation will silently fall back to differential demapping with
     * hard decisions (coherent=false, soft=false).
     */
    void decode(const gr_complex* bpsk_in, bool coherent = true, bool soft = true);
};

} // namespace dvbs2rx
} // namespace gr

#endif /* INCLUDED_DVBS2RX_PLSC_H */
