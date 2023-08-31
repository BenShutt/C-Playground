# Server

A simple TCP web-server written in C.

## Usage

To run the program, install dependencies (only needs to be done once) and run:

```bash
./scripts/install-c-json.sh
./scripts/run.sh
```

## IP Address

To get the wireless IP:

```bash
ipconfig getifaddr en0
```

Then the server will connect to port `666`.

## Dependencies

* [cJSON](https://github.com/DaveGamble/cJSON)

## References

* [IBM C socket TCP server](https://www.ibm.com/docs/en/zos/2.5.0?topic=programs-c-socket-tcp-server)
* [Makefile SO Post](https://stackoverflow.com/questions/30573481)
* [LCTHW](https://github.com/zedshaw/learn-c-the-hard-way-lectures)