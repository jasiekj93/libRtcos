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
Default build type is `debug`.

The default destination architecture is `ARM M7`, but you can change it in
Makefile or during build by changing `PLATFORM` flag.

Supported architectures are:
* ArmM7 (ARM Cortex-M7)
* ArmM4 (ARM Cortex-M4)
* Pc32 (depends on your host OS)
* Pc64 (depends on your host OS)


## Using library in your project

* Add the include path to the Makefile. Something like:
    * `CXXFLAGS += -I$(LIBRTCOS_HOME)/librtcos`
* Add the library linking to your Makefile. Something like:
    * `LDFLAGS += -L$(LIBRTCOS_HOME)/lib/$(PLATFORM)/$(BUILD_TYPE)`
    * `LDLIBS += -lrtcos`

## How to use it

* `Scheduler` - override `disableInterrupts()` and `enableInterrupts()` methods and provide reference for `PriorityQueue<Task*>` template interface (e.g. using `utils::PriorityLinkedList<T>` class provided by library). Overridden methods should disable and enable all hardware interrupts in device.
* `Clock` - registers observers (`TimerTask` objects) and the delay after which they are to be notified. For proper operation, the `update()` method must be called with a specific time interval (e.g. via the ISR of the system timer)
* `Task` - override `execute()` method.
* `ContinousTask` - decorator of the `Task` class, which, after execution, adds itself to the `Scheduler`.
* `MessageTask` - override `disableQueueInterrupt()` and `enableQueueInterrupt()` methods and provide reference for `Queue<T>` template interface (e.g. using `utils::CircullarBuffer<T>` class provided by library). Overridden methods should disable and enable interrupts on the hardware peripheral from which data is added to the queue. The ISR should also add the task to the `Scheduler` once the queue is filled with data.
* `BufferTask`- override `disableBufferInterrupt()` and `enableBufferInterrupt()` methods and provide reference for `ShadowBuffer<T>` template interface (e.g. using `utils::ArrayShadowBuffer<T>` class provided by library). Overridden methods should disable and enable interrupts on the hardware peripheral from which data is added to the buffer. The ISR should also add the task to the `Scheduler` once the buffer is filled with data.
* `TimerTask` - decorator of the `Task` class, which, after execution, adds new alarm to the `Clock` with reference to itself. When the `Clock` calls `notify()` method, the task adds itself to the `Scheduler`.

## Examples

Please check `librtcos/tests` directory.