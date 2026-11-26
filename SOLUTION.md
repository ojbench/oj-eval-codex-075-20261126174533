# String implementation

`str.hpp` owns a null-terminated character array and tracks its length separately,
so embedded zero characters are preserved by copying, joining, and slicing.
Copies own independent storage. Assignment allocates before releasing the old
buffer, supporting self-assignment and source pointers into the current buffer.

Construction and assignment take linear time in the copied length. Joining
precomputes the output size and allocates once, taking O(number of strings +
output length) time. Slicing takes O(r - l) time. Indexing and length queries
take constant time. Slice bounds must satisfy 0 <= l <= r <= len().

Run `make test` for tests with address and undefined-behavior sanitizers.

## Submission protocol

Submission 879522 received Compile Error because this problem's custom judge
included the Git URL itself as C++ header source. It consumes the submitted
code field directly despite the generic Git instructions in README.md.
Use the client's `submit --problem-id 1059 --source-file str.hpp` option for
this header problem, after sourcing `.env` and providing the token as usual.
