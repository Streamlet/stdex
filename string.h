//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   string.h
//    Author:      Streamlet
//    Create Time: 2016-09-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __STRING_H_9A5ECE42_2072_4E4C_9AF2_A91B1E2E1AD4_INCLUDED__
#define __STRING_H_9A5ECE42_2072_4E4C_9AF2_A91B1E2E1AD4_INCLUDED__


#include <string>
#include <vector>
#include <algorithm>

namespace stdex
{
    //
    // str_length
    //

    template<class _Elem>
    inline size_t str_length(const _Elem *str)
    {
        const _Elem *p = str;
        while (*p != _Elem(0))
            ++p;
        return p - str;
    }


    //
    // basic_shadow_string
    //

    struct Null;
    template<class _Elem, class _SSTraits = Null, class _SSAlloc = Null>
    class basic_shadow_string
    {
    public:
        basic_shadow_string() : data(0), len(0) { }
        basic_shadow_string(const _Elem *s) : data(s), len(str_length(s)) { }
        basic_shadow_string(const _Elem *begin, const _Elem *end) : data(begin), len(end - begin) { }
        basic_shadow_string(const _Elem *data, size_t len) : data(data), len(len) { }

        template <class _Traits, class _Alloc>
        basic_shadow_string(const std::basic_string<_Elem, _Traits, _Alloc> &s) : data(s.c_str()), len(s.length()) { }

        const _Elem *c_str() const { return data; }
        size_t length() const { return len; }

        template <class _Traits, class _Alloc>
        operator std::basic_string<_Elem, _Traits, _Alloc>() const {
            return std::basic_string<_Elem, _Traits, _Alloc>(data, len);
        }

    private:
        const _Elem *data;
        size_t len;
    };

    typedef basic_shadow_string<char> shadow_string;
    typedef basic_shadow_string<wchar_t> shadow_wstring;


    //
    // str_split
    //

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, size_t str_len,
        const _Elem *delimiter, size_t delimiter_len,
        size_t max = 0
    ) {
        std::vector<_StrType<_Elem, _Traits, _Alloc>> r;
        if (delimiter_len == 0)
            return r;
        const _Elem *p = str;
        for (size_t count = 0; p <= str + str_len && (max == 0 || count < max); ++count) {
            const _Elem *f = (max > 0 && count == max - 1) ? str + str_len : std::search(p, str + str_len, delimiter, delimiter + delimiter_len);
            r.push_back(_StrType<_Elem, _Traits, _Alloc>(p, f));
            p = f + delimiter_len;
        }
        return r;
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, size_t str_len, const _Elem delimiter, size_t max = 0
    ) {
        return str_split(str, str_len, &delimiter, 1, max);
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, const _Elem *delimiter, size_t max = 0
    ) {
        return str_split(str, str_length(str), delimiter, str_length(delimiter), max);
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, const _Elem delimiter, size_t max = 0
    ) {
        return str_split(str, str_length(str), &delimiter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *delimiter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), delimiter, str_length(delimiter), max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem delimiter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), &delimiter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &delimiter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), delimiter.c_str(), delimiter.length(), max);
    }


    //
    // str_split_copy
    //

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, size_t str_len, const _Elem *delimiter, size_t delimiter_len, size_t max = 0
    ) {
        return str_split<_Elem, _Traits, _Alloc, std::basic_string>(str, str_len, delimiter, delimiter_len, max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, size_t str_len, const _Elem delimiter, size_t max = 0
    ) {
        return str_split_copy(str, str_len, &delimiter, 1, max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, const _Elem *delimiter, size_t max = 0
    ) {
        return str_split_copy(str, str_length(str), delimiter, str_length(delimiter), max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, const _Elem delimiter, size_t max = 0
    ) {
        return str_split_copy(str, str_length(str), &delimiter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *delimiter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), delimiter, str_length(delimiter), max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem delimiter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), &delimiter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &delimiter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), delimiter.c_str(), delimiter.length(), max);
    }


    //
    // str_combine
    //

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem *delimiter, size_t delimiter_len
    ) {
        std::basic_string<_Elem, _Traits, _Alloc> ret;
        size_t total_len = 0;
        for (typename std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>>::const_iterator it = str_list.begin(); it != str_list.end(); ++it) {
            if (it != str_list.begin())
                total_len += delimiter_len;
            total_len += it->length();
        }
        ret.reserve(total_len);
        for (typename std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>>::const_iterator it = str_list.begin(); it != str_list.end(); ++it) {
            if (it != str_list.begin())
                ret.append(delimiter, delimiter_len);
            ret.append(it->c_str(), it->c_str() + it->length());
        }
        return ret;
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem *delimiter
    ) {
        return str_combine(str_list, delimiter, str_length(delimiter));
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem delimiter
    ) {
        return str_combine(str_list, &delimiter, 1);
    }

    template<class _Elem, class _Traits, class _Alloc,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = basic_shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const std::basic_string<_Elem, _Traits, _Alloc> &delimiter
    ) {
        return str_combine(str_list, delimiter.c_str(), delimiter.length());
    }

    //
    // str_replace_inplace
    //

    template<class _Elem>
    inline _Elem *str_replace_inplace(
        _Elem *str, size_t str_len,
        const _Elem *find, size_t find_len,
        const _Elem *replace, size_t replace_len,
        size_t max = 0
    ) {
        assert(find_len >= replace_len);
        if (find_len == 0)
            return str;
        _Elem *dest = str;
        const _Elem *src = str;
        for (size_t count = 0; src < str + str_len && (max == 0 || count < max); ++count) {
            const _Elem *f = std::search(src, (const _Elem *)str + str_len, find, find + find_len);
            if (find_len != replace_len)
                memcpy(dest, src, sizeof(_Elem) * (f - src));
            dest += (f - src);
            src = f;
            if (f < str + str_len) {
                memcpy(dest, replace, sizeof(_Elem) * replace_len);
                dest += replace_len;
                src += find_len;
            }
        }
        if (src < str + str_len) {
            if (find_len != replace_len)
                memcpy(dest, src, sizeof(_Elem) * (str + str_len - src));
            dest += (str + str_len - src);
        }
        *dest = _Elem(0);
        return str;
    }

    template<class _Elem>
    inline _Elem *str_replace_inplace(
        _Elem *str, size_t str_len,
        const _Elem *find, const _Elem *replace,
        size_t max = 0
    ) {
        return str_replace_inplace(str, str_len, find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem>
    inline _Elem *str_replace_inplace(
        _Elem *str, size_t str_len,
        const _Elem find, const _Elem replace,
        size_t max = 0
    ) {
        return str_replace_inplace(str, str_len, &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> &str_replace_inplace(
        std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *find, size_t find_len,
        const _Elem *replace, size_t replace_len,
        size_t max = 0
    ) {
        if (find_len <= replace_len) {
            str_replace_inplace(&str[0], str.length(), find, find_len, replace, replace_len, max);
            str.resize(str_length(str.c_str()));
        }
        else {
            str = str_combine(str_split(str.c_str(), str.length(), find, find_len, max), replace, replace_len);
        }
        return str;
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace_inplace(
        std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *find, const _Elem *replace,
        size_t max = 0
    ) {
        return str_replace_inplace(str, find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace_inplace(
        std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem find, const _Elem replace,
        size_t max = 0
    ) {
        return str_replace_inplace(str, &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace_inplace(
        std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &find,
        const std::basic_string<_Elem, _Traits, _Alloc> &replace,
        size_t max = 0
    ) {
        return str_replace_inplace(str, find.c_str(), find.length(), replace.c_str(), replace.length(), max);
    }

    //
    // str_replace
    //

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, size_t str_len,
        const _Elem *find, size_t find_len,
        const _Elem *replace, size_t replace_len,
        size_t max = 0
    ) {
        std::basic_string<_Elem, _Traits, _Alloc> ret;
        if (find_len <= replace_len) {
            ret.assign(str, str_len);
            str_replace_inplace(&ret[0], str_len, find, find_len, replace, replace_len, max);
            ret.resize(str_length(ret.c_str()));
            return ret;
        }
        else {
            ret = str_combine(str_split(str, str_len, find, find_len, max), replace, replace_len);
        }
        return ret;
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, size_t str_len, const _Elem *find, const _Elem *replace, size_t max = 0
    ) {
        return str_replace(str, str_len, find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, size_t str_len, const _Elem find, const _Elem replace, size_t max = 0
    ) {
        return str_replace(str, str_len, &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, const _Elem *find, const _Elem *replace, size_t max = 0
    ) {
        return str_replace(str, str_length(str), find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits = std::char_traits<_Elem>, class _Alloc = std::allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, const _Elem find, const _Elem replace, size_t max = 0
    ) {
        return str_replace(str, str_length(str), &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *find, size_t find_len,
        const _Elem *replace, size_t replace_len,
        size_t max = 0
    ) {
        return str_replace(str.c_str(), str.length(), find, find_len, replace, replace_len, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *find, const _Elem *replace,
        size_t max = 0
    ) {
        return str_replace(str, find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem find, const _Elem replace,
        size_t max = 0
    ) {
        return str_replace(str, &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &find,
        const std::basic_string<_Elem, _Traits, _Alloc> &replace,
        size_t max = 0
    ) {
        return str_replace(str, find.c_str(), find.length(), replace.c_str(), replace.length(), max);
    }
}

#endif // #ifndef __STRING_H_9A5ECE42_2072_4E4C_9AF2_A91B1E2E1AD4_INCLUDED__
