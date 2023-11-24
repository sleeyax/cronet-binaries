# cronet-binaries ![build workflow](https://github.com/sleeyax/cronet-binaries/actions/workflows/build.yml/badge.svg)

> :warning: This project is still under construction. Changes may be force pushed so use at your own risk.

Pre-built, cross-platform binaries for [cronet](https://chromium.googlesource.com/chromium/src/+/master/components/cronet/README.md) (Chromium's networking stack). New cronet binaries will be published to [releases](https://github.com/sleeyax/cronet-binaries/releases) as soon as new versions of Chromium are released.

This repository is based on [NaiveProxy](https://github.com/klzgrad/naiveproxy)'s excellent build system, but doesn't include any naive proxy binaries, tests or go files. The last release of Naive that came with standalone cronet binaries was [v106.0.5249.91-3](https://github.com/klzgrad/naiveproxy/releases/tag/v106.0.5249.91-3) (Nov 2, 2022). 

## Developers
### Local development
To build cronet locally using [docker](https://www.docker.com/), you can use a combination of [act](https://github.com/nektos/act) and [act-cache-server](https://github.com/sp-ricard-valverde/github-act-cache-server).

```bash
$ act --env ACTIONS_CACHE_URL=http://localhost:<PORT>/ --env ACTIONS_RUNTIME_URL=http://localhost:<PORT>/ --env ACTIONS_RUNTIME_TOKEN=<TOKEN> --job linux
```

Replace `<PORT>` and `<TOKEN>` with the port and token you configured for your local `act-cache-server` instance. Using a cache server is optional, but will speed up the build process significantly.
