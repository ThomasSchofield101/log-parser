# Log Parser 
Read a log file, filter by severity and/or keyword, and print or append matching entries.

## Synopsis:
**Usage:** `logparser [OPTIONS] <logfile>` <br/>
**Positional:** `<logfile>`: path to the input logfile

## Project structure
- `src/`            source files
- `include/`        headers
- `tests/`            unit tests (Unity)
- `tests/unity/`      Unity framework
- `build/`            CMake build output
- `CMakeLists.txt`  CMake build config`
- `Makefile`        legacy build system

## Build:
**prereqs:** GCC or CLANG, make <br/>

**Build:** 
### CMake (recommended):
**Minimum version:** CMake 3.1 <br/>

`cmake -S . -B build`, <br/>
`cmake --build build`

CMake builds output to `build/` (or `build/Debug` depending on generator).

### Make (legacy fallback):
`make` builds the main application (`log-parser`)

`make test` builds unit tests (`test_runner`)

## Options / CLI:
**--level:** Filter by level; Valid values: INFO, WARN, ERROR. Case-insensitive. <br/>

**--keyword:** Filter by lines containing given text (substring search). <br/>

**--output:** Append matching entries to the specified file instead of stdout. <br/>

**Behaviour:** Flags may be combined; --level is parsed once and applies to all entries

## Input format:
**Line pattern:** `<timestamp> <LEVEL> <message>` (timestamp is EPOCH seconds, LEVEL is a token like INFO). <br/>

**Example:** `1749801015 WARN Configuration file missing optional setting` <br/>

**Assumptions:** Levels in log lines are uppercase; code normalizes CLI level input. <br/>

## Examples:
**Print all entries:** `./logparser sys.log` <br/>


**Filter by level:** `./logparser --level INFO sys.log` <br/>

**Filter by keyword:** `./logparser --keyword sensor sys.log` <br/>

**Combine & write to file:** `./logparser --level ERROR --keyword crash --output report.txt sys.log` <br/>

**Expected short output:** for input `1623912345 ERROR Disk crash on /dev/sda` the tool prints `1623912345 ERROR Disk crash on /dev/sda`. <br/>

## Output / Behaviour:
**Default:** print matching entries to stdout using the same compact format.
**--output:** opens file in append mode; if open fails the program exits with an error.
**Formatting:** timestamp, level, message seperated by spaces on one line.

## Exit codes:
**0:** success. <br/>
**>0:** runtime failure (invalid arguments, I/O error, memory allocation etc).

## Performance / limitations:
**Memory:** current implementation loads entries into memory. For very large logs, prefer streaming and filtering on-the-fly. <br/>

**Scalability:** recommended for files up to a few hundred MB; large files may require rework. <br/>

## Error handling:
**Reporting:** errors printed to stderr with a short message; print_usage() is shown for bad arguments. <br/>

**Validation:** --level is validated at parse time; invalid values cause immediate exit. <br/>

## Testing

Unit tests are written using the Unity framework and test the core parsing logic.

### CMake
Build:
`cmake --build build`

Run tests:
`./build/test_runner`

### Make
Build:
`make test`

Run tests:
`./test_runner`

## Contributing / License:
**Contributing:** open issues or PRs; include a reproducible example and expected output. <br/>

**License:** MIT

