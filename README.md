stdex
=====
Extending features for C++ standard library and runtime

### string.h

###### string splitting

CRT and STL does not provide any functions or classes for string splitting and replacement. We do it.

*   str_split

    split string and return std::vector of "shadow_string". A shadow_string is defined with two members, a pointer pointed to the first character of the substring, and an integer specified the length of the substring.

*   str_split_copy

    split string and return std::vector of std::string or std::wstring (exactly std::basic_string).


###### string replacement

*   str_replace_inplace

    replace string inplace, the given string will be modifed.

*   str_replace

    replace string and return a copy of the replaced string.


### scope_exit.h

It is something like Loki::ScopeGuard.

*   STDEX_ON_BLOCK_EXIT

    Sample code:

    ``` C++
    {
        FILE *p = fopen(...);
        STDEX_ON_BLOCK_EXIT(fclose, p);

        fread(p, ...);
        fwrite(p, ...);

        // when block exits, fclose(p) will be called automaticly.
    }
    ```

* stdex::make_guard

    Sample code:

    ``` C++
    {
        std::scope_guard sg = stdex::make_guard(remove, "foo.bar");
        FILE *p = fopen("foo.bar", ...);

        fwrite(p, ...);

        if (...) {
        	return;	// return if error occurs, remove("foo.bar") will be called automatically by scope_guard.
        }

        sg.dismiss(); // scoped_guard is dismissed and will do nothing.
    }
    ```
