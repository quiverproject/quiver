# QMLKit - The fastest way to design Qt apps with QML

## Live reload QML & design for multiple platforms simultaneously

The Qt Creator design environment is very limited, and separates interface
design implementation from integration.  QMLKit allows you to interactively
design QML GUI applications live in the running application.  This makes design
implementation and integration a single step and greatly speeds up development.

QMLKit also allows you to use Qt Creator or any other IDE or text editor you
prefer to build your application. 

Also Qt Creator doesn't include a deployment process and deploying to different
platforms is challenging and poorly documented.

### Instructions

Only tested on OSX at the moment.

    git clone https://github.com/ggamel/QMLKit.git
    cd QMLKit
    make design

Edit `src/qml/Main.qml` to design your QML interface interactively.

### More to come

- TDD - Test Driven Development
- Graphical QtObject Creator and Connection editor

### TODO

- [ ] Create configuration and deployment system.
- [ ] Create TDD system.

