# Server

A simple HTTP server written in C.
The project uses [Mongoose](https://mongoose.ws) for the foundational server implementation.
Files are uploaded via a HTTP request and written to a local directory.

There is a companion [MediaExport](https://github.com/BenShutt/MediaExport) iOS app. The client syncs the media (images, videos, etc) on the device with the server over the WIFI.

While this server successfully syncs files with a client, it was built for learning purposes and there are better ways to do it - i.e. do not use in production!

## Usage

To run the program, install dependencies (only needs to be done once) then run:

```bash
./scripts/install-mongoose.sh
./scripts/run.sh
```

Update the `run.sh` script to point at a different directory.

## IP Address

To get the wireless IP:

```bash
ipconfig getifaddr en0
```

Then the server will connect to port `8000`.

You will need this if connecting from a device that is not hosting the server (e.g. mobile to laptop).

## Bytes

To print the bytes of a file:

```bash
xxd /path/to/file
```

## Dependencies

* [Mongoose](https://github.com/cesanta/mongoose)

## References

* [IBM C socket TCP server](https://www.ibm.com/docs/en/zos/2.5.0?topic=programs-c-socket-tcp-server)
* [Makefile SO Post](https://stackoverflow.com/questions/30573481)
* [LCTHW](https://github.com/zedshaw/learn-c-the-hard-way-lectures)
* [Building a Static Library](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch01s04.html)