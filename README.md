# [Quiver](https://github.com/quiverproject/quiver)

Quiver is the fastest way to design Qt apps in real-time with QML, JavaScript, and CoffeeScript.

The Qt Creator design environment is very limited, separating interface
design implementation from integration.  Quiver allows you to interactively
design QML GUI applications live in the running application.  This makes design
implementation and integration a single step and greatly speeds up development.

Quiver also allows you to use Qt Creator or any other IDE or text editor you
prefer to build your application.

Finally, Qt Creator doesn't include a deployment process, making deploying to different
platforms a challenge. Quiver will also provide a configuration and deployment system (on roadmap).


## Features

*  Live reload QML
*  Design for multiple platforms simulataneously
*  Design GUI live in the running application
*  Single-step design implementation and integration


## Quick Start (OS X only at present)

Clone repo, enter directory, run Makefile:

```sh
git clone https://github.com/quiverproject/quiver.git
cd quiver
make design
```


Edit `src/qml/Main.qml` to design your QML interface interactively.


## Roadmap

* TDD - Test Driven Development system
* Graphical QtObject Creator and Connection editor
* Configuration and deployement system


## License

Quiver is provided under the [MIT license](https://github.com/quiverproject/quiver/blob/master/LICENSE.md).

