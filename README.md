# libRTCOS

RTCOS (Run To Completion Operating System) - Non preemptive task scheduling library.

## Building

You'll need to do the following to get started:

```bash
git clone https://github.com/jasiekj93/librtcos.git
cd librtcos
git submodule init
git submodule update
make
```

You can use `make release` if you want to build without debug symbols.

The default destination architecture is `ARM M7`, but you can change it in
Makefile or during build by changing `PLATFORM` flag.

Supported architectures are:
* Arm M7
* Arm M4
* Pc32 (depends on your host OS)
* Pc64 (depends on your host OS)