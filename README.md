Code demonstrating the incorrect behavior of G4DecayWithSpin
================================

This code simulates a box of vacuum with a uniform, 1.5T magnetic field in the z-direction and a torus slice to enable turn counting (the counting is not currently implemented). The only physics other than transportation is G4DecayWithSpin. A 3.1 GeV muon is allowed to circle in the magnetic field until it decays.

The contents of debuggingOutput.txt demonstrate an error in G4DecayWithSpin. When a breakpoint is placed at line 122 of G4DecayWithSpin.cc, right before the call to Spin_Precession, the variable fRemainderLifeTime is observed to be nonzero. The track status indicates that this is an in flight decay; according to the discussion at http://hypernews.slac.stanford.edu:5090/HyperNews/geant4/get/emfields/156.html, fRemainderLifeTime is intended to be zero for in flight decays. Additionally, it can be seen that fRemainderLifeTime is exactly equal to the muon lifetime multiplied by the ratio of the previous step length to the interaction length. In other words, fRemainderLifeTime is one step behind.

Aaron Fienberg

fienberg@uw.edu