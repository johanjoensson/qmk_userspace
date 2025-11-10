#include QMK_KEYBOARD_H
#include "johanjoensson.h"

const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("aalpha", 0x0391),               // Α
    UCIS_SYM("bbeta", 0x0392),                // Β
    UCIS_SYM("ggamma", 0x0393),               // Γ
    UCIS_SYM("ddelta", 0x0394),               // Δ
    UCIS_SYM("eepsilon", 0x0395),             // Ε
    UCIS_SYM("zzeta", 0x0396),                // Ζ
    UCIS_SYM("eeta", 0x0397),                 // Η
    UCIS_SYM("ttheta", 0x0398),               // Θ
    UCIS_SYM("iiota", 0x0399),                // Ι
    UCIS_SYM("kkappa", 0x039A),               // Κ
    UCIS_SYM("llambda", 0x039B),              // Λ
    UCIS_SYM("mmu", 0x039C),                  // Μ
    UCIS_SYM("nnu", 0x039D),                  // Ν
    UCIS_SYM("xxi", 0x039E),                  // Ξ
    UCIS_SYM("oomicron", 0x039F),             // Ο
    UCIS_SYM("ppi", 0x03A0),                  // Π
    UCIS_SYM("rrho", 0x03A1),                 // Ρ
    UCIS_SYM("ssigma", 0x03A3),               // Σ
    UCIS_SYM("ttau", 0x03A4),                 // Τ
    UCIS_SYM("uupsilon", 0x03A5),             // Υ
    UCIS_SYM("ppsi", 0x03A6),                 // Φ
    UCIS_SYM("cchi", 0x03A7),                 // Χ
    UCIS_SYM("pphi", 0x03A8),                 // Ψ
    UCIS_SYM("oomega", 0x03A9),               // Ω
    UCIS_SYM("alpha", 0x03B1),                // α
    UCIS_SYM("beta", 0x03B2),                 // β
    UCIS_SYM("gamma", 0x03B3),                // γ
    UCIS_SYM("delta", 0x03B4),                // δ
    UCIS_SYM("epsilon", 0x03B5),              // ε
    UCIS_SYM("zeta", 0x03B6),                 // ζ
    UCIS_SYM("eta", 0x03B7),                  // η
    UCIS_SYM("theta", 0x03B8),                // θ
    UCIS_SYM("iota", 0x03B9),                 // ι
    UCIS_SYM("kappa", 0x03BA),                // κ
    UCIS_SYM("lambda", 0x03BB),               // λ
    UCIS_SYM("mu", 0x03BC),                   // μ
    UCIS_SYM("nu", 0x03BD),                   // ν
    UCIS_SYM("xi", 0x03BE),                   // ξ
    UCIS_SYM("omicron", 0x03BF),              // ο
    UCIS_SYM("pi", 0x03C0),                   // π
    UCIS_SYM("rho", 0x03C1),                  // ρ
    UCIS_SYM("sigma", 0x03C3),                // σ
    UCIS_SYM("sigmap", 0x03C2),               // ς
    UCIS_SYM("tau", 0x03C4),                  // τ
    UCIS_SYM("upsilon", 0x03C5),              // υ
    UCIS_SYM("phi", 0x03C6),                  // φ
    UCIS_SYM("chi", 0x03C7),                  // χ
    UCIS_SYM("psi", 0x03C8),                  // ψ
    UCIS_SYM("omega", 0x03C9),                // ω
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("rofl", 0x1F923),                // 🤣
    UCIS_SYM("cuba", 0x1F1E8, 0x1F1FA),       // 🇨🇺
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0), // ಠ_ಠ
    UCIS_SYM("snek", 0x1F40D),                // 🐍
    UCIS_SYM("badger", 0x1F9A1)               // 🦡
);

void ucis_start_user(void)
{ 
}
