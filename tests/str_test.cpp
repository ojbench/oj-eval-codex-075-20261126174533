#include "str.hpp"
#include <cassert>

static void check(const str &value, const char *expected) {
    assert(value.len() == std::strlen(expected));
    for (std::size_t i = 0; i < value.len(); ++i)
        assert(value[i] == expected[i]);
}

int main() {
    check(str(), "");
    check(str('x'), "x");
    str original("hello");
    str copy(original);
    copy[0] = 'j';
    check(original, "hello");
    check(copy, "jello");
    copy = copy;
    check(copy, "jello");
    copy = original;
    original[0] = 'H';
    check(copy, "hello");
    copy = &copy[2];
    check(copy, "llo");
    copy = "";
    check(copy, "");

    check(str(", ").join({'1', '2', '3'}), "1, 2, 3");
    check(str(",").join({}), "");
    check(str(",").join({"one"}), "one");
    check(str(",").join({"", "", ""}), ",,");
    check(str("").join({"ab", "", "cd"}), "abcd");
    check(original.slice(0, 5), "Hello");
    check(original.slice(1, 4), "ell");
    check(original.slice(5, 5), "");
    check(str().slice(0, 0), "");

    str binary('\0');
    assert(binary.len() == 1 && binary[0] == '\0');
    str joined = binary.join({"a", "b"});
    assert(joined.len() == 3 && joined[1] == '\0');
    str part = joined.slice(1, 3);
    assert(part.len() == 2 && part[0] == '\0' && part[1] == 'b');
    for (int i = 0; i < 10000; ++i) {
        str a("repeated allocations");
        str b(a);
        b = a.slice(2, 10);
        a = b;
    }
}
