//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2023 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef ICONS_HXX
#define ICONS_HXX

#include "Icon.hxx"

namespace GUI {

/* Exported structure definition. */
static constexpr IconDesc iconSmallDesc(14, 14);
static constexpr IconDesc iconLargeDesc(19, 20);

// Settings icon
static const Icon icon_settings_small(
  iconSmallDesc,
  {
    0b00000000000000,
    0b00011000110000,
    0b00111111111000,
    0b00111111111000,
    0b00111111111000,
    0b01111000111100,
    0b11110000011110,
    0b11110000011110,
    0b11110000011110,
    0b01111000111100,
    0b00111111111000,
    0b00111111111000,
    0b00111111111000,
    0b00011000110000
  });

// Up icon
static const Icon icon_up_small(
  iconSmallDesc,
  {
    0b00000001000000,
    0b00000011100000,
    0b00000111110000,
    0b00001111111000,
    0b00011111111100,
    0b00111111111110,
    0b01111111111111,
    0b00000011100000,
    0b00000011100000,
    0b00000011100000,
    0b00000011100000,
    0b00000011100000,
    0b00000011100000,
    0b00000011100000
  });

// Previous icon
static const Icon icon_prev_small(
  iconSmallDesc,
  {
    0b00000000000000,
    0b00000010000000,
    0b00000110000000,
    0b00001110000000,
    0b00011110000000,
    0b00111110000000,
    0b01111111111111,
    0b11111111111111,
    0b01111111111111,
    0b00111110000000,
    0b00011110000000,
    0b00001110000000,
    0b00000110000000,
    0b00000010000000
  });

// Next icon
static const Icon icon_next_small(
  iconSmallDesc,
  {
    0b00000000000000,
    0b00000001000000,
    0b00000001100000,
    0b00000001110000,
    0b00000001111000,
    0b00000001111100,
    0b11111111111110,
    0b11111111111111,
    0b11111111111110,
    0b00000001111100,
    0b00000001111000,
    0b00000001110000,
    0b00000001100000,
    0b00000001000000
  });

// Home icon
static const Icon icon_home_small(
  iconSmallDesc,
  {
    0b00000001000000,
    0b00000011100000,
    0b00000110110000,
    0b00001101011000,
    0b00011011101100,
    0b00110111110110,
    0b01101111111011,
    0b01011111111101,
    0b00011110111100,
    0b00011100011100,
    0b00011100011100,
    0b00011100011100,
    0b00011100011100,
    0b00011100011100
  });

// Reload icon
static const Icon icon_reload_small(
  iconSmallDesc,
  {
    0b00000000000000,
    0b00000111110001,
    0b00011111111111,
    0b00111000001111,
    0b00110000001111,
    0b01100000011111,
    0b01100000000000,
    0b01100000000000,
    0b01100000000000,
    0b01100000000011,
    0b00110000000110,
    0b00111000001110,
    0b00011111111100,
    0b00000111110000
  });

// Allfiles icons
static const Icon icon_onlyroms_small_on (
  iconSmallDesc,
  {
    0b00000000000000,
    0b00000111100000,
    0b00000111100000,
    0b00000111100000,
    0b00000111100000,
    0b00000111100000,
    0b00000111100000,
    0b00001111110000,
    0b00001111110000,
    0b00011111111000,
    0b00011011011000,
    0b00110011001100,
    0b11110011001111,
    0b11100011000111
  });
static const Icon icon_onlyroms_small_off (
  iconSmallDesc,
  {
    0b01111111111000,
    0b01000000001100,
    0b01000000000110,
    0b01000000000010,
    0b01001000010010,
    0b01001100110010,
    0b01000111100010,
    0b01011111111010,
    0b01000111100010,
    0b01001100110010,
    0b01001000010010,
    0b01000000000010,
    0b01000000000010,
    0b01111111111110
  });

// Subdirs icons
static const Icon icon_subdirs_small_off(
  iconSmallDesc,
  {
    0b11110000000000,
    0b11111000000000,
    0b11111111111111,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b10000000000001,
    0b11111111111111
  });
static const Icon icon_subdirs_small_on(
  iconSmallDesc,
  {
    0b11100000000000,
    0b11110000000000,
    0b11111111110000,
    0b10000000010000,
    0b10000000011100,
    0b10000000010100,
    0b10000000010111,
    0b10000000010101,
    0b10000000010101,
    0b11111111110101,
    0b00100000000101,
    0b00111111111101,
    0b00001000000001,
    0b00001111111111
  });
// Help icon
static const Icon icon_help_small(
  iconSmallDesc,
  {
    0b0000011100000,
    0b0001111111000,
    0b0011100011100,
    0b0111000001110,
    0b0111000001110,
    0b0000000011100,
    0b0000001111000,
    0b0000011100000,
    0b0000011100000,
    0b0000011100000,
    0b0000000000000,
    0b0000000000000,
    0b0000011100000,
    0b0000011100000
  });


// Settings icon
static const Icon icon_settings_large(
  iconLargeDesc,
  {
    0b0000000000000000000,
    0b0000111000001110000,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0011111111111111100,
    0b1111111000001111111,
    0b1111110000000111111,
    0b1111110000000111111,
    0b1111110000000111111,
    0b1111110000000111111,
    0b1111110000000111111,
    0b1111111000001111111,
    0b0011111111111111100,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0001111111111111000,
    0b0000111000001110000
  });

// Up icon
static const Icon icon_up_large(
  iconLargeDesc,
  {
    0b0000000001000000000,
    0b0000000011100000000,
    0b0000000111110000000,
    0b0000001111111000000,
    0b0000011111111100000,
    0b0000111111111110000,
    0b0001111111111111000,
    0b0011111111111111100,
    0b0111111111111111110,
    0b1111111111111111111,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000,
    0b0000000111110000000
  });

// Previous icon
static const Icon icon_prev_large(
  iconLargeDesc,
  {
    0b0000000000000000000,
    0b0000000001000000000,
    0b0000000011000000000,
    0b0000000111000000000,
    0b0000001111000000000,
    0b0000011111000000000,
    0b0000111111000000000,
    0b0001111111000000000,
    0b0011111111111111111,
    0b0111111111111111111,
    0b1111111111111111111,
    0b0111111111111111111,
    0b0011111111111111111,
    0b0001111111000000000,
    0b0000111111000000000,
    0b0000011111000000000,
    0b0000001111000000000,
    0b0000000111000000000,
    0b0000000011000000000,
    0b0000000001000000000
  });

// Next icon
static const Icon icon_next_large(
  iconLargeDesc,
  {
    0b0000000000000000000,
    0b0000000001000000000,
    0b0000000001100000000,
    0b0000000001110000000,
    0b0000000001111000000,
    0b0000000001111100000,
    0b0000000001111110000,
    0b0000000001111111000,
    0b1111111111111111100,
    0b1111111111111111110,
    0b1111111111111111111,
    0b1111111111111111110,
    0b1111111111111111100,
    0b0000000001111111000,
    0b0000000001111110000,
    0b0000000001111100000,
    0b0000000001111000000,
    0b0000000001110000000,
    0b0000000001100000000,
    0b0000000001000000000
  });

// Home icon
static const Icon icon_home_large(
  iconLargeDesc,
  {
    0b0000000001000000000,
    0b0000000011100000000,
    0b0000000110110000000,
    0b0000001101011000000,
    0b0000011011101100000,
    0b0000110111110110000,
    0b0001101111111011000,
    0b0011011111111101100,
    0b0110111111111110110,
    0b1101111111111111011,
    0b1001111111111111001,
    0b0001111100011111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000,
    0b0001111000001111000
  });

// Reload icon
static const Icon icon_reload_large(
  iconLargeDesc,
  {
    0b0000000000000000000,
    0b0000001111111000001,
    0b0000111111111110011,
    0b0001111111111111111,
    0b0011110000000111111,
    0b0111000000000011111,
    0b0111000000000111111,
    0b1110000000001111111,
    0b1110000000000000000,
    0b1110000000000000000,
    0b1110000000000000000,
    0b1110000000000000000,
    0b1110000000000000000,
    0b1110000000000000111,
    0b0111000000000000110,
    0b0111000000000001110,
    0b0011110000000111100,
    0b0001111111111111000,
    0b0000111111111110000,
    0b0000001111111000000
  });

// Allfiles icons
static const Icon icon_onlyroms_large_on(
  iconLargeDesc,
  {
    0b00000000000000000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000001011010000000,
    0b00000011011011000000,
    0b00000011011011000000,
    0b00000111011011100000,
    0b00000110011001100000,
    0b00001110011001110000,
    0b00011100011000111000,
    0b01111100011000011110,
    0b11111000011000001111,
    0b11100000011000000111
  });
static const Icon icon_onlyroms_large_off(
  iconLargeDesc,
  {
    0b0111111111111100000,
    0b0100000000000110000,
    0b0100000000000011000,
    0b0100000000000001100,
    0b0100011000011000100,
    0b0100011100111000100,
    0b0100001100110000100,
    0b0100001111110000100,
    0b0100000111100000100,
    0b0101111111111110100,
    0b0101111111111110100,
    0b0100000111100000100,
    0b0100001111110000100,
    0b0100001100110000100,
    0b0100011100111000100,
    0b0100011000011000100,
    0b0100000000000000100,
    0b0100000000000000100,
    0b0100000000000000100,
    0b0111111111111111100
  });

// Subdirs icons
static const Icon icon_subdirs_large_off(
  iconLargeDesc,
  {
    0b1111110000000000000,
    0b1111111000000000000,
    0b1111111100000000000,
    0b1111111111111111111,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1000000000000000001,
    0b1111111111111111111
  });
static const Icon icon_subdirs_large_on(
  iconLargeDesc,
  {
    0b1111100000000000000,
    0b1111110000000000000,
    0b1111111000000000000,
    0b1111111111111110000,
    0b1000000000000010000,
    0b1000000000000011100,
    0b1000000000000010100,
    0b1000000000000010111,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1000000000000010101,
    0b1111111111111110101,
    0b0010000000000000101,
    0b0011111111111111101,
    0b0000100000000000001,
    0b0000111111111111111
  });

static const Icon icon_help_large(
  iconLargeDesc,
  {
    0b0000000111110000000,
    0b0000011111111100000,
    0b0001111111111111000,
    0b0001111000001111000,
    0b0011110000000111100,
    0b0011100000000011100,
    0b0011100000000011100,
    0b0011100000000111100,
    0b0000000000011111000,
    0b0000000000111110000,
    0b0000000001111000000,
    0b0000000011110000000,
    0b0000000011100000000,
    0b0000000011100000000,
    0b0000000011100000000,
    0b0000000000000000000,
    0b0000000000000000000,
    0b0000000011100000000,
    0b0000000011100000000,
    0b0000000011100000000
  });

} // namespace GUI

#endif
