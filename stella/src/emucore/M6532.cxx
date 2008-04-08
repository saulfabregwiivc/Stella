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
// Copyright (c) 1995-2008 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: M6532.cxx,v 1.17 2008-04-08 19:17:26 stephena Exp $
//============================================================================

#include <assert.h>
#include "Console.hxx"
#include "M6532.hxx"
#include "Random.hxx"
#include "Switches.hxx"
#include "System.hxx"
#include "Serializer.hxx"
#include "Deserializer.hxx"
#include <iostream>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
M6532::M6532(const Console& console)
  : myConsole(console)
{
  // Randomize the 128 bytes of memory
  class Random random;

  for(uInt32 t = 0; t < 128; ++t)
  {
    myRAM[t] = random.next();
  }

  // Initialize other data members
  reset();
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
M6532::~M6532()
{
}
 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void M6532::reset()
{
  class Random random;

  myTimer = 25 + (random.next() % 75);
  myIntervalShift = 6;
  myCyclesWhenTimerSet = 0;
  myCyclesWhenInterruptReset = 0;
  myTimerReadAfterInterrupt = false;

  // Zero the I/O registers
  myDDRA = 0x00;
  myDDRB = 0x00;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void M6532::systemCyclesReset()
{
  // System cycles are being reset to zero so we need to adjust
  // the cycle count we remembered when the timer was last set
  myCyclesWhenTimerSet -= mySystem->cycles();
  myCyclesWhenInterruptReset -= mySystem->cycles();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void M6532::install(System& system)
{
  install(system, *this);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void M6532::install(System& system, Device& device)
{
  // Remember which system I'm installed in
  mySystem = &system;

  uInt16 shift = mySystem->pageShift();
  uInt16 mask = mySystem->pageMask();

  // Make sure the system we're being installed in has a page size that'll work
  assert((0x1080 & mask) == 0);
  
  // All accesses are to the given device
  System::PageAccess access;
  access.device = &device;

  // We're installing in a 2600 system
  for(int address = 0; address < 8192; address += (1 << shift))
  {
    if((address & 0x1080) == 0x0080)
    {
      access.directPeekBase = 0; 
      access.directPokeBase = 0;
      mySystem->setPageAccess(address >> shift, access);
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 M6532::peek(uInt16 addr)
{
  // Access RAM directly.  Originally, accesses to RAM could bypass
  // this method and its pages could be installed directly into the
  // system.  However, certain cartridges (notably 4A50) can mirror
  // the RAM address space, making it necessary to chain accesses.
  if((addr & 0x1080) == 0x0080 && (addr & 0x0200) == 0x0000)
  {
    return myRAM[addr & 0x007f];
  }

  switch(addr & 0x07)
  {
    case 0x00:    // Port A I/O Register (Joystick)
    {
      uInt8 value = 0x00;

      if(myConsole.controller(Controller::Left).read(Controller::One))
        value |= 0x10;
      if(myConsole.controller(Controller::Left).read(Controller::Two))
        value |= 0x20;
      if(myConsole.controller(Controller::Left).read(Controller::Three))
        value |= 0x40;
      if(myConsole.controller(Controller::Left).read(Controller::Four))
        value |= 0x80;

      if(myConsole.controller(Controller::Right).read(Controller::One))
        value |= 0x01;
      if(myConsole.controller(Controller::Right).read(Controller::Two))
        value |= 0x02;
      if(myConsole.controller(Controller::Right).read(Controller::Three))
        value |= 0x04;
      if(myConsole.controller(Controller::Right).read(Controller::Four))
        value |= 0x08;

      return value;
    }

    case 0x01:    // Port A Data Direction Register 
    {
      return myDDRA;
    }

    case 0x02:    // Port B I/O Register (Console switches)
    {
      return myConsole.switches().read();
    }

    case 0x03:    // Port B Data Direction Register
    {
      return myDDRB;
    }

    case 0x04:    // Timer Output
    case 0x06:
    {
      uInt32 timer = myTimer - (mySystem->cycles() - myCyclesWhenTimerSet);

      // See if the timer has expired yet?
      // Note that this constant comes from z26, and corresponds to
      // 256 intervals of T1024T (ie, the maximum that the timer
      // should hold)
      if(!(timer & 0x40000))
      {
        return (timer >> myIntervalShift) & 0xff;
      }
      else
      {
        myTimerReadAfterInterrupt = true;
        myCyclesWhenInterruptReset = mySystem->cycles();
        return timer & 0xff;
      }
    }

    case 0x05:    // Interrupt Flag
    case 0x07:
    {
      Int32 timer = myTimer - (mySystem->cycles() - myCyclesWhenTimerSet);

      if((timer >= 0) || myTimerReadAfterInterrupt)
        return 0x00;
      else
        return 0x80;
    }

    default:
    {    
#ifdef DEBUG_ACCESSES
      cerr << "BAD M6532 Peek: " << hex << addr << endl;
#endif
      return 0;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void M6532::poke(uInt16 addr, uInt8 value)
{
  // Access RAM directly.  Originally, accesses to RAM could bypass
  // this method and its pages could be installed directly into the
  // system.  However, certain cartridges (notably 4A50) can mirror
  // the RAM address space, making it necessary to chain accesses.
  if((addr & 0x1080) == 0x0080 && (addr & 0x0200) == 0x0000)
  {
    myRAM[addr & 0x007f] = value;
  }
  else if((addr & 0x07) == 0x00)         // Port A I/O Register (Joystick)
  {
    uInt8 a = value & myDDRA;

    myConsole.controller(Controller::Left).write(Controller::One, a & 0x10);
    myConsole.controller(Controller::Left).write(Controller::Two, a & 0x20);
    myConsole.controller(Controller::Left).write(Controller::Three, a & 0x40);
    myConsole.controller(Controller::Left).write(Controller::Four, a & 0x80);
    
    myConsole.controller(Controller::Right).write(Controller::One, a & 0x01);
    myConsole.controller(Controller::Right).write(Controller::Two, a & 0x02);
    myConsole.controller(Controller::Right).write(Controller::Three, a & 0x04);
    myConsole.controller(Controller::Right).write(Controller::Four, a & 0x08);
  }
  else if((addr & 0x07) == 0x01)    // Port A Data Direction Register 
  {
    myDDRA = value;

    // TODO - Fix this properly in the core
    //        Any time the core code needs to know what type of controller
    //        is connected, it's by definition a bug
    //        A real Atari doesn't 'know' that an AVox is connected, so we
    //        shouldn't either
    /*
      20060608 bkw: Not the most elegant thing in the world...
      When a bit in the DDR is set as input, +5V is placed on its output
      pin. When it's set as output, either +5V or 0V (depending on the
      contents of SWCHA) will be placed on the output pin.
      The standard macros for the AtariVox use this fact to send data
      to the port.

      This code isn't 100% correct: it assumes the SWCHA bits are all 0.
      This is good enough to emulate the AtariVox, if the programmer is
      using SWACNT to do output (e.g. the SPKOUT macro from speakjet.inc)
      and if he's leaving SWCHA alone.

      The inaccuracy here means that wrongly-written code will still
      be able to drive the emulated AtariVox, even though it wouldn't
      work on real hardware.
    */
    Controller& c = myConsole.controller(Controller::Right);
    if(c.type() == Controller::AtariVox)
    {
      c.write(Controller::One, !(value & 0x01));
      c.write(Controller::Two, !(value & 0x02));
      c.write(Controller::Three, !(value & 0x04));
      c.write(Controller::Four, !(value & 0x08));
    }
  }
  else if((addr & 0x07) == 0x02)    // Port B I/O Register (Console switches)
  {
    return;
  }
  else if((addr & 0x07) == 0x03)    // Port B Data Direction Register
  {
//        myDDRB = value;
    return;
  }
  else if((addr & 0x17) == 0x14)    // Write timer divide by 1 
  {
    myIntervalShift = 0;
    myTimer = value << myIntervalShift;
    myCyclesWhenTimerSet = mySystem->cycles();
    myTimerReadAfterInterrupt = false;
  }
  else if((addr & 0x17) == 0x15)    // Write timer divide by 8
  {
    myIntervalShift = 3;
    myTimer = value << myIntervalShift;
    myCyclesWhenTimerSet = mySystem->cycles();
    myTimerReadAfterInterrupt = false;
  }
  else if((addr & 0x17) == 0x16)    // Write timer divide by 64
  {
    myIntervalShift = 6;
    myTimer = value << myIntervalShift;
    myCyclesWhenTimerSet = mySystem->cycles();
    myTimerReadAfterInterrupt = false;
  }
  else if((addr & 0x17) == 0x17)    // Write timer divide by 1024
  {
    myIntervalShift = 10;
    myTimer = value << myIntervalShift;
    myCyclesWhenTimerSet = mySystem->cycles();
    myTimerReadAfterInterrupt = false;
  }
  else if((addr & 0x14) == 0x04)    // Write Edge Detect Control
  {
#ifdef DEBUG_ACCESSES
    cerr << "M6532 Poke (Write Edge Detect): "
        << ((addr & 0x02) ? "PA7 enabled" : "PA7 disabled")
        << ", "
        << ((addr & 0x01) ? "Positive edge" : "Negative edge")
        << endl;
#endif
  }
  else
  {
#ifdef DEBUG_ACCESSES
    cerr << "BAD M6532 Poke: " << hex << addr << endl;
#endif
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool M6532::save(Serializer& out) const
{
  string device = name();

  try
  {
    out.putString(device);

    // Output the RAM
    out.putInt(128);
    for(uInt32 t = 0; t < 128; ++t)
      out.putByte((char)myRAM[t]);

    out.putInt(myTimer);
    out.putInt(myIntervalShift);
    out.putInt(myCyclesWhenTimerSet);
    out.putInt(myCyclesWhenInterruptReset);
    out.putBool(myTimerReadAfterInterrupt);
    out.putByte((char)myDDRA);
    out.putByte((char)myDDRB);
  }
  catch(char *msg)
  {
    cerr << msg << endl;
    return false;
  }
  catch(...)
  {
    cerr << "Unknown error in save state for " << device << endl;
    return false;
  }

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool M6532::load(Deserializer& in)
{
  string device = name();

  try
  {
    if(in.getString() != device)
      return false;

    // Input the RAM
    uInt32 limit = (uInt32) in.getInt();
    for(uInt32 t = 0; t < limit; ++t)
      myRAM[t] = (uInt8) in.getByte();

    myTimer = (uInt32) in.getInt();
    myIntervalShift = (uInt32) in.getInt();
    myCyclesWhenTimerSet = (uInt32) in.getInt();
    myCyclesWhenInterruptReset = (uInt32) in.getInt();
    myTimerReadAfterInterrupt = in.getBool();

    myDDRA = (uInt8) in.getByte();
    myDDRB = (uInt8) in.getByte();
  }
  catch(char *msg)
  {
    cerr << msg << endl;
    return false;
  }
  catch(...)
  {
    cerr << "Unknown error in load state for " << device << endl;
    return false;
  }

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
M6532::M6532(const M6532& c)
  : myConsole(c.myConsole)
{
  assert(false);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
M6532& M6532::operator = (const M6532&)
{
  assert(false);
  return *this;
}
