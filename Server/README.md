# Server

A simple HTTP server written in C.
The project is built using [Mongoose](https://mongoose.ws) which provides the foundational server implementation.
It 

## Usage

To run the program, install dependencies (only needs to be done once) and run:

```bash
./scripts/install-mongoose.sh
./scripts/run.sh
```

## IP Address

To get the wireless IP:

```bash
ipconfig getifaddr en0
```

Then the server will connect to port `8000`.

## Bytes

To print the bytes of a file:

```bash
xxd </path/to/file>
```

## Dependencies

* [Mongoose](https://github.com/cesanta/mongoose)

## References

* [IBM C socket TCP server](https://www.ibm.com/docs/en/zos/2.5.0?topic=programs-c-socket-tcp-server)
* [Makefile SO Post](https://stackoverflow.com/questions/30573481)
* [LCTHW](https://github.com/zedshaw/learn-c-the-hard-way-lectures)
* [Building a Static Library](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch01s04.html)