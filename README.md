<div align="center">
    <h1>Abstract</h1>
    <h3>The Answer to the Great Cross-Platform Shader Conundrum!!!</h3>
    <p>Written in fairly memory-leaky C written by <a href="https://github.com/libdev-hacker/">an amateur</a></p><br>
</div>

## About Abstract
This is a complimentary project to my main one, [Rogue](https://github.com/libdev-hacker/rogue), that allows for GLSL code to be compiled down into either SPIR-V, MSL (Metal Shading Language) or HLSL (Used by DirectX) as well as WGSL to GLSL, HLSL, MSL & SPIR-V.

### TL;DR
This is a very thin wrapper around the [simple_wgsl](https://github.com/manuel5975p/simple_wgsl) project, all the credit to them :)

## Getting Started
To start your adventure into web browser development / general WWW-related shenanigans, clone a local copy on to your machine:
```sh
git clone https://github.com/libdev-hacker/abstract.git
```
### Building
To build Rogue, first enter the project's root directory via the command: 
```sh
cd abstract (or whichever directory you cloned into)
```
Then, to build the project run:
```sh
cmake -B build (or whatever directory name you want)
cmake --build [Chosen build dir]
```

## Usage

There should be a shared library now within the ```build``` directory. This exposes multiple functions that allow for any code in either GLSL or WGSL to be compiled / translated into the appropriate language.

_For specifics, see source code above_

## License

This project is licensed under the [MIT License](LICENSE). This allows for Rogue or any of its constituent projects to be used, modified & re-distributed by anyone within the community. (Patches are still very much welcome though)

### Dependencies

- [simple_wgsl](https://github.com/manuel5975p/simple_wgsl)

### Disclaimer

The repository for this projects _only_ dependency, [simple_wgsl](https://github.com/manuel5975p/simple_wgsl), does list Claude as a contributor but at the time of this library first being published, it (as far as I can tell) is not attributed to any commits. That being said, should there be any hard evidence of the repo being vibe-coded in any major capacity (> 80%) then, in accordance with Rogue's policy on vibe-coded work ([see here](https://github.com/libdev-hacker/rogue/blob/main/CONTRIBUTING.md#views-on-vibe-coded-contributions)) then I will consider taking steps to overcome this dilemma.
