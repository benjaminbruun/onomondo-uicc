# Changelog

## [3.0.0](https://github.com/benjaminbruun/onomondo-uicc/compare/v2.0.1...v3.0.0) (2025-12-02)


### ⚠ BREAKING CHANGES

* Initial commit

### Features

* add option to link against custom crypto implementations ([70d714c](https://github.com/benjaminbruun/onomondo-uicc/commit/70d714cac3ee7689c25695ff9edf679a4a3a244f))
* add optional external heap allocator ([69fcc7e](https://github.com/benjaminbruun/onomondo-uicc/commit/69fcc7e386751beaef2066cd0b91180709753dff))
* add pseudo support for uicc suspend ([90be703](https://github.com/benjaminbruun/onomondo-uicc/commit/90be7034ccb65bc582af8127769384441917a8c8))
* add support for application layer APDU ([cd2738f](https://github.com/benjaminbruun/onomondo-uicc/commit/cd2738fdba340bd61b8d5ef2c17279f450a6729e))
* bump softsim version to 2.0.0 ([a0e786c](https://github.com/benjaminbruun/onomondo-uicc/commit/a0e786c0ef9dc8c41fd56c201d525953cc644491))
* cmake build tests with address sanitizer ([0d2faf3](https://github.com/benjaminbruun/onomondo-uicc/commit/0d2faf343abace9bb23ab21ee9d72f3183a11af3))
* export files to c-arrays and validate ([b5bf5dc](https://github.com/benjaminbruun/onomondo-uicc/commit/b5bf5dc76e181428ac950cbae9532f646703a10f))
* Initial commit ([1e956d0](https://github.com/benjaminbruun/onomondo-uicc/commit/1e956d053c3f5dab9be367d8407ed8caf75ea871))
* make the utils part of the installed targets if enabled ([92023fb](https://github.com/benjaminbruun/onomondo-uicc/commit/92023fbf185a6fb97a9d26472fea9da657e55b41))
* move filesystem create to utils folder ([1cdfaed](https://github.com/benjaminbruun/onomondo-uicc/commit/1cdfaed0a842a6b1473181b5ce567a833b7b269e))
* onomondo profile decoding functionality ([6b72f8e](https://github.com/benjaminbruun/onomondo-uicc/commit/6b72f8e294eb9a1b8b64e784f4c39cfecbf01e76))
* optional default impl, option to build lib only, remove ctype ([ef8f485](https://github.com/benjaminbruun/onomondo-uicc/commit/ef8f48581a4c8ef38ecfd92af3bba056c5c7bdfd))
* use a file for each seq and delta value ([85efa6c](https://github.com/benjaminbruun/onomondo-uicc/commit/85efa6cfb2f957cc7334b0ff037357de7989f790))


### Bug Fixes

* bad python version breaks unit testing ([46e100c](https://github.com/benjaminbruun/onomondo-uicc/commit/46e100ca0637a1087ff8b4a0ad181a604724ee1d))
* check for bad lc in apdu handler ([80f7029](https://github.com/benjaminbruun/onomondo-uicc/commit/80f702993954e65f85aec25631c0740ba28a5481))
* cmake preprocessor define syntax ([bd06b44](https://github.com/benjaminbruun/onomondo-uicc/commit/bd06b44f421e298740cd8f5aee6071cc552164f9))
* make uicc suspend an optional build flag ([0404fa0](https://github.com/benjaminbruun/onomondo-uicc/commit/0404fa0e685b4dc5197296ca2b9f911dc9a0d09b))
* parsed EF.SMSP length of tlv hex profile ([#28](https://github.com/benjaminbruun/onomondo-uicc/issues/28)) ([d326ad9](https://github.com/benjaminbruun/onomondo-uicc/commit/d326ad9164b86e3eb32e2b51ed1ffdcb397a9460))
* prevent double tag skipping in case of unknown tag ([#25](https://github.com/benjaminbruun/onomondo-uicc/issues/25)) ([cba9823](https://github.com/benjaminbruun/onomondo-uicc/commit/cba9823c6121dc23bdfcbd31f8d51d40c647fe9a))
* properly initialize argument 'fdset' of select() ([#16](https://github.com/benjaminbruun/onomondo-uicc/issues/16)) ([adf43b2](https://github.com/benjaminbruun/onomondo-uicc/commit/adf43b26de65ed59371e3b4af9bee680791a5b96))
* use c89 style for loops to keep older compilers happy ([a7d070f](https://github.com/benjaminbruun/onomondo-uicc/commit/a7d070fdbf42dc95aad5cdff6785735022e2739b))
* use max proposed suspend duration ([#24](https://github.com/benjaminbruun/onomondo-uicc/issues/24)) ([c694458](https://github.com/benjaminbruun/onomondo-uicc/commit/c6944589acb83ce075c691ee6585233627410c27))
* use proper variable to retrieve SFI ([#14](https://github.com/benjaminbruun/onomondo-uicc/issues/14)) ([55c0385](https://github.com/benjaminbruun/onomondo-uicc/commit/55c0385a6c64feded928b952497a137e2d9c846e))

## [2.0.1](https://github.com/onomondo/onomondo-uicc/compare/v2.0.0...v2.0.1) (2025-12-01)


### Bug Fixes

* parsed EF.SMSP length of tlv hex profile ([#28](https://github.com/onomondo/onomondo-uicc/issues/28)) ([d326ad9](https://github.com/onomondo/onomondo-uicc/commit/d326ad9164b86e3eb32e2b51ed1ffdcb397a9460))
* prevent double tag skipping in case of unknown tag ([#25](https://github.com/onomondo/onomondo-uicc/issues/25)) ([cba9823](https://github.com/onomondo/onomondo-uicc/commit/cba9823c6121dc23bdfcbd31f8d51d40c647fe9a))
* properly initialize argument 'fdset' of select() ([#16](https://github.com/onomondo/onomondo-uicc/issues/16)) ([adf43b2](https://github.com/onomondo/onomondo-uicc/commit/adf43b26de65ed59371e3b4af9bee680791a5b96))
* use max proposed suspend duration ([#24](https://github.com/onomondo/onomondo-uicc/issues/24)) ([c694458](https://github.com/onomondo/onomondo-uicc/commit/c6944589acb83ce075c691ee6585233627410c27))
* use proper variable to retrieve SFI ([#14](https://github.com/onomondo/onomondo-uicc/issues/14)) ([55c0385](https://github.com/onomondo/onomondo-uicc/commit/55c0385a6c64feded928b952497a137e2d9c846e))

## [2.0.0](https://github.com/onomondo/onomondo-uicc/compare/v1.0.0...v2.0.0) (2024-07-30)


### Features

* CMake build system for softsim UICC, new `utils` library and test targets ([#7](https://github.com/onomondo/onomondo-uicc/pull/7))
* add optional external heap allocator ([e323c51](https://github.com/onomondo/onomondo-uicc/commit/e323c5189911434e30d3014cf2954bed880934b9))
* add pseudo support for uicc suspend ([d0195b5](https://github.com/onomondo/onomondo-uicc/commit/d0195b57b5a24995f745eabcd8ddb08c9f385716))
* cmake build tests with address sanitizer ([593de0c](https://github.com/onomondo/onomondo-uicc/commit/593de0c4a613766501d9b3f417b06c4f607fe42e))
* use a file for each seq and delta value ([de1408a](https://github.com/onomondo/onomondo-uicc/commit/de1408a55a5e131273489d1fb58f0924891b4d5f))
* add support for application layer APDU ([51ef10a](https://github.com/onomondo/onomondo-uicc/commit/51ef10ae21af9a19e98e73e02a75c8f6451a67a6))
* onomondo profile decoding functionality ([ccfb88d](https://github.com/onomondo/onomondo-uicc/commit/ccfb88d17cbd8afe3058d5c560dc758cd18139ad))
* add option to link against custom crypto implementations ([c8608df](https://github.com/onomondo/onomondo-uicc/commit/c8608dfe422a60a08e2a51849a61b12faa0e8438))
* optional default impl, option to build lib only, remove ctype ([473f88b](https://github.com/onomondo/onomondo-uicc/commit/473f88ba8e23867d4cc12d1930b4de56462d317d))
* export files to c-arrays and validate ([71bbfa4](https://github.com/onomondo/onomondo-uicc/commit/71bbfa40a00ea7f8c65b5721bbe3bcb9d314ce6f))
* make the utils part of the installed targets if enabled ([8fe7797](https://github.com/onomondo/onomondo-uicc/commit/8fe7797d7acca400a134e8a5f1489ce20846d05d))
* move filesystem create to utils folder ([236b186](https://github.com/onomondo/onomondo-uicc/commit/236b18623c5573ecb6ba7a82f8d5f05cec0c18a4))

### Bug Fixes

* make uicc suspend an optional build flag ([d8a8d29](https://github.com/onomondo/onomondo-uicc/commit/d8a8d2994b94dd451efec8492ba7d9425c0dc477))
* bad python version breaks unit testing ([de08053](https://github.com/onomondo/onomondo-uicc/commit/de080538c6092c5dc079101066aed959d9f120d8))
* use c89 style for loops to keep older compilers happy ([1df09ab](https://github.com/onomondo/onomondo-uicc/commit/1df09abf4284c50b28f76cdda5435ad8674953c0))
* check for bad lc in apdu handler ([27fabb3](https://github.com/onomondo/onomondo-uicc/commit/27fabb3b8f0479d71ce115253d57804b0a4a9193))
* cmake preprocessor define syntax ([b0969b7](https://github.com/onomondo/onomondo-uicc/commit/b0969b78af1089a1e93a8128613d07c50d1a8fa6))

## [1.0.0](https://github.com/onomondo/onomondo-uicc/releases/tag/v1.0.0) (2024-02-14)


### Initial Version

* Initial project commit, adding the core UICC softsim source tree, include headers, initial tests, and examples. ([1e956d0](https://github.com/onomondo/onomondo-uicc/commit/1e956d053c3f5dab9be367d8407ed8caf75ea871))

### Features

* Basic UICC softsim implementation, test-suite scaffolding, and README.
