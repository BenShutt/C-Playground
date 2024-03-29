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

This is needed if connecting from a device that is not hosting the server (e.g. mobile to laptop) but is on the same WIFI.

## Uploads

As documented in Mongoose's [File Uploads](https://mongoose.ws/documentation/tutorials/file-uploads/#binary-upload-single-post) tutorial, single POST uploads are handled in chunks.
These are delivered as separate `MG_EV_HTTP_CHUNK` events opposed to the usual `MG_EV_HTTP_MSG`.
This enables us to break up large request bodies into smaller parts.

Consequentially, the client must use, say, [upload](https://github.com/Alamofire/Alamofire/blob/master/Documentation/Usage.md#uploading-data-to-a-server) for this to work.

## Bytes

To print the bytes of a file:

```bash
xxd /path/to/file
```

## Dependencies

* [Mongoose](https://github.com/cesanta/mongoose)

## Further References

* [Socket](https://github.com/BenShutt/C-Playground/tree/develop/Socket)
* [Building a Static Library](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch01s04.html)