# DOS Project

A C++ console application that simulates a DOS-like command-line environment on Windows. The program maintains an in-memory virtual directory tree (folders and files) and provides a set of commands that resemble classic DOS utilities (for example: DIR, CD, MKDIR, RMDIR, TREE, CREATE, DEL, RENAME, FORMAT, and HELP).

## Key Features

- DOS-style prompt and interactive REPL loop
- In-memory virtual file system
  - Folder and file objects with parent relationships
  - Create, delete, rename, and list files
  - Create, remove, and traverse directories
  - Print the full directory tree
- Built-in HELP command listing supported commands
- Windows console integration (uses Windows headers for console handling)

## Project Structure

- `bscs22115  DOS_project.cpp`: Main source code (virtual file system structures, command loop, and command implementations)
- `bscs22115  DOS_project.sln`: Visual Studio solution file
- `bscs22115  DOS_project.vcxproj`: Visual Studio C++ project file
- `tree.txt`: Sample tree input file referenced by the HELP menu (used by the LOADTREE command in the intended design)

## Requirements

- Windows OS (uses `windows.h`)
- A C++ compiler with C++11 support or later
- Visual Studio (recommended) or another Windows-capable C++ build environment

## Build and Run (Visual Studio)

1. Open `bscs22115  DOS_project.sln` in Visual Studio.
2. Select the desired configuration (Debug/Release) and platform (x64).
3. Build the solution.
4. Run the project. The application starts with a DOS-style prompt.

## Usage

When the program starts, it displays a prompt similar to:

```
V:\>
```

Type commands and press Enter.

### Example Session

```
V:\> mkdir docs
V:\> cd docs
V:\docs> create notes.txt
V:\docs> dir
V:\docs> tree
```

## Supported Commands

The program is designed to support commands listed by the built-in `HELP` output, including (not exhaustive):

- `ATTRIB`, `CD`, `CD.`, `CD..`, `CD\`, `COPY`, `CREATE`, `DEL`, `DIR`, `EDIT`, `EXIT`, `FIND`, `FINDF`, `FINDSTR`, `FORMAT`, `HELP`, `LOADTREE`, `MKDIR`, `MOVE`, `PPRINT`, `PROMPT`, `PRINT`, `PQUEUE`, `PWD`, `QUEUE`, `RENAME`, `RMDIR`, `SAVE`, `TREE`, `VER`

Note: The current implementation may include only a subset of these commands. The HELP text reflects the intended command set.

## Notes and Limitations

- The virtual file system exists in memory for the lifetime of the process. Unless persistence is implemented, data will not be retained after exit.
- Some commands referenced in HELP may be planned but not fully implemented in the current code.

## Authors

- Haseeb-Ur-Rehman (bscs22115)
- Ibrahim Nadeem (bscs22071)

## License

This repository does not currently specify a license. If you intend others to use, modify, or distribute this code, consider adding a LICENSE file (for example, MIT, Apache-2.0, or GPL-3.0).