# Sleep, Wakeup and Measure
This is a minimal example on how to utilize the RTT to wakeup from sleep mode, and do a measurement.

Sleep mode maps to EM2 energy mode, in which the core is stopped and only a few peripherals (including RTT/RTCC) will continue. With a SLSTK3401A, an energy consumption of approximately 15µA is measured. It does not disable the Si7021 sensor between sleeps.
