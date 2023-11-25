# cronet-binaries ![build workflow](https://github.com/sleeyax/cronet-binaries/actions/workflows/build.yml/badge.svg)

> :warning: This project is still under construction. Changes may be force pushed so use at your own risk.

Pre-built, cross-platform binaries for [cronet](https://chromium.googlesource.com/chromium/src/+/master/components/cronet/README.md) (Chromium's networking stack). New cronet binaries will be published to [releases](https://github.com/sleeyax/cronet-binaries/releases) as soon as new stable versions of Chromium are released.

This repository is based on [NaiveProxy](https://github.com/klzgrad/naiveproxy)'s excellent build system, but doesn't include any Naive binaries, tests or go files. The last release of Naive that came with standalone cronet binaries was [v106.0.5249.91-3](https://github.com/klzgrad/naiveproxy/releases/tag/v106.0.5249.91-3) (Nov 2, 2022). Since then, new builds have been [discontinued](https://github.com/klzgrad/naiveproxy/issues/471#issuecomment-1457323770) so this project aims to fill that gap.

## Applied patches
Patches are applied to the Chromium source code to make it compile on all supported platforms and support additional features. The following noteworthy patches are applied:

- Minimize source code and build size
- Disable exceptions and RTTI, except on Mac and Android.
- Support [OpenWrt](https://openwrt.org/) builds
- Use the builtin verifier instead of the system verifier (drop dependency of NSS on Linux) and read the system trust store (following Go's behavior in `crypto/x509/root_unix.go` and `crypto/x509/root_linux.go`):
- Handle AIA response in PKCS#7 format
- Allow higher socket limits for proxies
- Force tunneling for all sockets
- Support HTTP/2 and HTTP/3 CONNECT tunnel Fast Open using the fastopen header
- Pad RST_STREAM frames
- Disable Android JNI
- Use fixed proxy resolution from experimental option proxy_server

Generally, we try to apply [changes from Naive](https://github.com/klzgrad/naiveproxy#changes-from-upstream) that are still relevant and don't break the build. If you have any suggestions, please open an issue.

## Related projects
- [klzgrad/NaiveProxy](https://github.com/klzgrad/naiveproxy) Proxy that uses cronet to camouflage traffic.
- [sleeyax/cronet-go](https://github.com/sleeyax/cronet-go) Go bindings for cronet. This is a fork and continuation of Naive's [sagernet/cronet-go](https://github.com/sagernet/cronet-go).
- [sleeyax/cronet-rs](https://github.com/sleeyax/cronet-rs) Rust bindings for cronet.
- [sleeyax/CronetSharp](https://github.com/sleeyax/CronetSharp) C# bindings for cronet.

## Developers
### Local development
To build cronet locally using [docker](https://www.docker.com/), you can use a combination of [act](https://github.com/nektos/act) and [act-cache-server](https://github.com/sp-ricard-valverde/github-act-cache-server).

```bash
$ act --env ACTIONS_CACHE_URL=http://localhost:<PORT>/ --env ACTIONS_RUNTIME_URL=http://localhost:<PORT>/ --env ACTIONS_RUNTIME_TOKEN=<TOKEN> --job linux
```

Replace `<PORT>` and `<TOKEN>` with the port and token you configured for your local `act-cache-server` instance. Using a cache server is optional, but will speed up the build process significantly.
