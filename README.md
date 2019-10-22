# What Is This?
This is an Enigma simulator.  In C.  So you can throw it into Ghidra and run PCode Emulation on it.

# Building
Have GCC.  Run make.  Defaults to thinking you're on x86 64 bit, but just runs GCC.

If you want to build for a different architecture, `make ARCH=aarch64` for instance.  Supported architectures are aarch64, x86, armel, and powerpc.  The default tools that get used are from Debian's "crossbuild-essential" series, so on Deb/Ubuntu install those with `apt install crossbuild-essential-ARCHITECTURE`.

# Usage
```
Usage: ./enigma.x64 key rotor\_order swaps enc/dec\_text

	key          - 3 characters, the initial settings on the rotors
	rotor_order  - 3 digits, the rotors to use.  1, 2, 3,
	               and 5 implemented.
	swaps        - An even number of characters, where each
	               pair is swapped on the plugboard.
	enc/dec_text - The text to encode or decode.
```

# Credits
This is based on the work of Emily Willson and the NSA, https://github.com/NationalSecurityAgency/enigma-simulator.git
