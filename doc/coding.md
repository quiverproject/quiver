#Coding

Please be consistent with the existing coding style.

##Block style for .cpp

- ANSI/Allman block style
- 2 space indenting, no tabs
- No extra spaces inside parenthesis; please don't do `( this )`
- No space after function names, one space after `if`, `for` and `while`
- No space after last character of a line
- One empty line at end of file


```cpp
  bool method(char* psz, int n)
  {
    // Comment summarising what this section of code does
    for (int i = 0; i < n; i++)
    {
      // When something fails, throw error and return early.
      if (!Something())
      {
        MyException.raise();
        return;
      }
      ...
    }
    // Success return is usually at the end
    return true;
  }
```

## Block style for .qml

- 1TBS block style
- 2 space indenting, no tabs
- Top level object in a file should always be named "root" `id: root`
- id immediately after opening brace.
- 1 parameter per line for single value parameters.
- Prefer bracket syntax over dot syntax when setting multi-component parameters.
- Protect 'private' parameters and methods in a QtObject block called `p`

```qml
// anchors on second line and inlined if it fits in 80col.
// followed next by layout parameters.
Rectangle { id: root
  anchors {left:parent.left}
  width: 20
  height: 20
  // Next Other parameters
  color: "#ffffff"
  // Next custom parameters
  property var meaningOfLifeTheUniverseAndEverything: 42
  // Next Signal decelerations
  signal foo
  // Next child objects
  Rectangle { id: box2
    anchors {fill:parent;}
  }
  // Then in this order:
  // States
  // State transitions
  // Animations
  // Signal definitions
  // Public method definitions
  
  // Than a private section
  QtObject { id: p
    property var privateProperty
    function privateMethod() {
      // ...
    }
  }
  // Last Component.onCompleted
  Component.onCompleted: {
  }
}
```
