# Coding Style and Guidelines

- All data members must be private.
- Prefer class over struct unless it is truly a data collection without methods.
- No Get or Set prefix in method names. E.g. prefer 2 overoads of owner() instead of getOwner() and setOwner().
- Mostly one class per file.
- No Raw pointer. In general try to use modern C++ types, styles and idioms.
- No full copyright message in each file, rather a 2 line stuf.
- Do not return const reference of unique_ptr, prefer OptionalReference instead.