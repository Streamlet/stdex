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
    // shadow_string
    //

    struct Null;
    template<class _Elem, class _Traits = Null, class _Alloc = Null>
    class shadow_string
    {
    public:
        shadow_string() : data(0), len(0) { }
        shadow_string(const _Elem *s) : data(s), len(str_length(s)) { }
        shadow_string(const _Elem *begin, const _Elem *end) : data(begin), len(end - begin) { }
        shadow_string(const _Elem *data, size_t len) : data(data), len(len) { }

        template <class _Traits, class _Alloc>
        shadow_string(const std::basic_string<_Elem, _Traits, _Alloc> &s) : data(s.c_str()), len(s.length()) { }

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


    //
    // str_split
    //

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, size_t str_len,
        const _Elem *splitter, size_t splitter_len,
        size_t max = 0
    ) {
        std::vector<_StrType<_Elem, _Traits, _Alloc>> r;
        if (splitter_len == 0)
            return r;
        const _Elem *p = str;
        for (size_t count = 0; p <= str + str_len && (max == 0 || count < max); ++count) {
            const _Elem *f = (max > 0 && count == max - 1) ? str + str_len : std::search(p, str + str_len, splitter, splitter + splitter_len);
            r.push_back(_StrType<_Elem, _Traits, _Alloc>(p, f));
            p = f + splitter_len;
        }
        return r;
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, size_t str_len, const _Elem splitter, size_t max = 0
    ) {
        return str_split(str, str_len, &splitter, 1, max);
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, const _Elem *splitter, size_t max = 0
    ) {
        return str_split(str, str_length(str), splitter, str_length(splitter), max);
    }

    template<class _Elem, class _Traits = Null, class _Alloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _Traits, _Alloc>> str_split(
        const _Elem *str, const _Elem splitter, size_t max = 0
    ) {
        return str_split(str, str_length(str), &splitter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *splitter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), splitter, str_length(splitter), max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem splitter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), &splitter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc, class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> str_split(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &splitter,
        size_t max = 0
    ) {
        return str_split(str.c_str(), str.length(), splitter.c_str(), splitter.length(), max);
    }


    //
    // str_split_copy
    //

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, size_t str_len, const _Elem *splitter, size_t splitter_len, size_t max = 0
    ) {
        return str_split<_Elem, _Traits, _Alloc, std::basic_string>(str, str_len, splitter, splitter_len, max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, size_t str_len, const _Elem splitter, size_t max = 0
    ) {
        return str_split_copy(str, str_len, &splitter, 1, max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, const _Elem *splitter, size_t max = 0
    ) {
        return str_split_copy(str, str_length(str), splitter, str_length(splitter), max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const _Elem *str, const _Elem splitter, size_t max = 0
    ) {
        return str_split_copy(str, str_length(str), &splitter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem *splitter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), splitter, str_length(splitter), max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const _Elem splitter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), &splitter, 1, max);
    }

    template<class _Elem, class _Traits, class _Alloc>
    inline std::vector<std::basic_string<_Elem, _Traits, _Alloc>> str_split_copy(
        const std::basic_string<_Elem, _Traits, _Alloc> &str,
        const std::basic_string<_Elem, _Traits, _Alloc> &splitter,
        size_t max = 0
    ) {
        return str_split_copy(str.c_str(), str.length(), splitter.c_str(), splitter.length(), max);
    }


    //
    // str_combine
    //

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem *splitter, size_t splitter_len
    ) {
        std::basic_string<_Elem, _Traits, _Alloc> ret;
        size_t total_len = 0;
        for (std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>>::const_iterator it = str_list.begin(); it != str_list.end(); ++it) {
            if (it != str_list.begin())
                total_len += splitter_len;
            total_len += it->length();
        }
        ret.reserve(total_len);
        for (std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>>::const_iterator it = str_list.begin(); it != str_list.end(); ++it) {
            if (it != str_list.begin())
                ret.append(splitter, splitter_len);
            ret.append(it->c_str(), it->c_str() + it->length());
        }
        return ret;
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem *splitter
    ) {
        return str_combine(str_list, splitter, str_length(splitter));
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const _Elem splitter
    ) {
        return str_combine(str_list, &splitter, 1);
    }

    template<class _Elem, class _Traits, class _Alloc,
        class _SSTraits = Null, class _SSAlloc = Null,
        template <class _Elem, class _Traits, class _Alloc> class _StrType = shadow_string>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_combine(
        const std::vector<_StrType<_Elem, _SSTraits, _SSAlloc>> &str_list,
        const std::basic_string<_Elem, _Traits, _Alloc> &splitter
    ) {
        return str_combine(str_list, splitter.c_str(), splitter.length());
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

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
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

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, size_t str_len, const _Elem *find, const _Elem *replace, size_t max = 0
    ) {
        return str_replace(str, str_len, find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, size_t str_len, const _Elem find, const _Elem replace, size_t max = 0
    ) {
        return str_replace(str, str_len, &find, 1, &replace, 1, max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
    inline std::basic_string<_Elem, _Traits, _Alloc> str_replace(
        const _Elem *str, const _Elem *find, const _Elem *replace, size_t max = 0
    ) {
        return str_replace(str, str_length(str), find, str_length(find), replace, str_length(replace), max);
    }

    template<class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
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
